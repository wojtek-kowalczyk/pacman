#include "headers/game.h"
#include "headers/collectible.h"
#include <vector>

Game* game = nullptr; // this has to be here so that the linker sees it.

Game::Game(QWidget* parent) : QGraphicsView(parent)
{
    // "singleton" (kinda)
    if (!game)
        game = this;
    else
        abort();

    // initialize members
    m_isOver = false;
    pointsCounter = 0;
    scene = new QGraphicsScene();
    player = new Player();
    scoreText = new QGraphicsTextItem();
    endScoreText = new QGraphicsTextItem();
    gameOverPanel = new QGraphicsRectItem();
    mainTimer = new QTimer();
    ghosts.push_back(ghostRed = new EnemyRed(QPixmap("resources/ghost-red.png")));
    ghosts.push_back(ghostBlue = new EnemyBlue(QPixmap("resources/ghost-blue.png")));
    ghosts.push_back(ghostWhite = new EnemyWhite(QPixmap("resources/ghost-white.png")));
    ghosts.push_back(ghostOrange = new EnemyOrange(QPixmap("resources/ghost-orange.png")));

    // scene configuration
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBackgroundBrush(QBrush(QImage("resources/board-padded.png").scaled(SCREEN_WIDTH, SCREEN_HEIGHT)));

    // configure player and ghosts
    setEntities();

    // configure score text
    setScoreText();

    // configure game over screen
    setGameOverPanel();

    // main event loop timer
    setMainTimer();

    // add Items to scene
    scene->addItem(player);
    for (Enemy* ghost : ghosts)
        scene->addItem(ghost);
    scene->addItem(scoreText);

    // additional connections
    QObject::connect(player, SIGNAL(scoreChanged(int)), this, SLOT(updateScoreText()));

    // mind-when-restarting type set-up

    // Add points
    addPoints();

    // assign positions
    setInitialPositions();

#ifdef GAME_DEBUG
    QObject::connect(mainTimer, SIGNAL(timeout()), player, SLOT(DEBUG_drawCell()));
    // draw cells to represent the board
    for (int row = 0; row < Board::rows; row++)
    {
        for (int col = 0; col < Board::cols; col++)
        {
            QGraphicsRectItem* cell = new QGraphicsRectItem();
            cell->setRect(Board::cellToPx(row, col).x, Board::cellToPx(row, col).y, 8 * SCALE_FACTOR, 8 * SCALE_FACTOR);
            cell->setBrush((Board::query(row, col) == 0) ? Qt::white
                                                         : ((Board::query(row, col) == 1)   ? Qt::yellow
                                                            : (Board::query(row, col) == 2) ? Qt::red
                                                                                            : Qt::black));

            cell->setOpacity(0.25);
            scene->addItem(cell);
        }
    }
#endif
}

void Game::setEntities()
{
    player->setFlag(QGraphicsItem::ItemIsFocusable); // it's able to be focused
    player->setFocus();
    player->setZValue(ZVAL_ALMOST_TOP);
    for (Enemy* ghost : ghosts)
        ghost->setZValue(ZVAL_ALMOST_TOP);
}

void Game::setScoreText()
{
    scoreText->setFont(QFont("times", 24));
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setVisible(true);
    scoreText->setPlainText(QString("Score: ") + QString::number(player->getScore()));
}
void Game::updateScoreText()
{
    scoreText->setPlainText(QString("Score: ") + QString::number(player->getScore()));
}

void Game::addPoints()
{
    for (int row = 0; row < Board::rows; row++)
    {
        for (int col = 0; col < Board::cols; col++)
        {
            Collectible* point;
            switch (Board::query(row, col))
            {
            case 1: // small point
                point = new Collectible(POINTS_SMALL, QPixmap("resources/point1.png"));
                break;
            case 3: // big point
                point = new Collectible(POINTS_BIG, QPixmap("resources/point2.png"));
                break;
            default:
                continue;
            }
            point->setPos(Board::cellToPx(row, col).x, Board::cellToPx(row, col).y);
            scene->addItem(point);
            ++pointsCounter;
            QObject::connect(point, SIGNAL(collected(int)), player, SLOT(addScore(int)));
            QObject::connect(this, SIGNAL(pointsDestructionOrdered()), point, SLOT(destroy()));
            QObject::connect(point, SIGNAL(collected(int)), this, SLOT(onPointCollected()));

            if (point->points == POINTS_BIG)
            {
                for (Enemy* ghost : ghosts)
                {
                    QObject::connect(point, SIGNAL(collected(int)), ghost, SLOT(scare()));
                }
            }
        }
    }
}

void Game::removePoints()
{
    emit pointsDestructionOrdered();
}

void Game::onPointCollected()
{
    if (--pointsCounter == 0)
    {
        gameOver(true);
    }
}

bool Game::isOver()
{
    return m_isOver;
}

#include <QCoreApplication>
#include <iostream>
void Game::gameOver(bool win)
{
    m_isOver = true;
    mainTimer->stop();
    updateEndScoreText(win);
    gameOverPanel->setVisible(true);
}

void Game::restart()
{
    // reverse game over
    m_isOver = false;
    mainTimer->start();
    gameOverPanel->setVisible(false);

    // additional resets
    setInitialPositions();
    removePoints();
    addPoints();
    player->setMoveDirection(LEFT);
    player->setRequestedDirection(LEFT);
    player->resetScore();
}

void Game::setGameOverPanel()
{
    gameOverPanel->setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gameOverPanel->setBrush(Qt::black);

    endScoreText->setParentItem(gameOverPanel);
    endScoreText->setDefaultTextColor(Qt::white);
    endScoreText->setFont(QFont("times", 32));

    scene->addItem(gameOverPanel);
    gameOverPanel->setVisible(false);
    gameOverPanel->setZValue(ZVAL_TOP);
}

void Game::updateEndScoreText(bool win)
{
    if (!win) // todo - change
    {
        endScoreText->setPlainText(QString("GAME OVER !\nyour score is: ") + QString::number(player->getScore()) +
                                   QString("\npress [SPACE] to restart"));
    }
    else
    {
        endScoreText->setPlainText(QString("YOU WIN !\nyour score is: ") + QString::number(player->getScore()) +
                                   QString("\npress [SPACE] to restart"));
    }
}

void Game::setMainTimer()
{
    QObject::connect(mainTimer, SIGNAL(timeout()), player, SLOT(move()));
    for (Enemy* ghost : ghosts)
        QObject::connect(mainTimer, SIGNAL(timeout()), ghost, SLOT(move()));
    mainTimer->start(1000 / FPS);
    // mainTimer->start(1000 * 20 / FPS); // 20 times slower
}

void Game::setInitialPositions()
{
    player->putCenterInCell(PLAYER_ENTRY_ROW, PLAYER_ENTRY_COLUMN);
    for (int i = 0; i < (int)ghosts.size(); i++)
    {
        if (i == 0)
        {
            ghosts[i]->deploy();
        }
        else
        {
            Vector2 targetPos = Board::cellToPx(GHOST_HOUSE_ROW, GHOST_HOUSE_COLUMN + (2 * (i - 1)));
            ghosts[i]->setPos(targetPos.x, targetPos.y);
            ghosts[i]->allowMovement = false;

            // Ghost deployment
            // ghost's timer is single shot, so this start basically says timeout after
            // this time and then do nothing. then, on restart this whole function is
            // called again, and calling start again sets the timer to fire again after said time.
            ghosts[i]->deployTimer->start(i * GHOST_DEPLOY_INTERVAL);
            QObject::connect(ghosts[i]->deployTimer, SIGNAL(timeout()), ghosts[i], SLOT(deploy()));
        }
    }
}