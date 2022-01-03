#include "headers/game.h"
#include "headers/collectible.h"
#include "headers/text.h"
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
    scene = new QGraphicsScene();
    player = new Player();
    scoreText = new CustomText();
    ghosts.push_back(ghostRed = new EnemyRed(QPixmap("resources/ghost-red.png")));
    ghosts.push_back(ghostBlue = new EnemyBlue(QPixmap("resources/ghost-blue.png")));
    ghosts.push_back(ghostWhite = new EnemyWhite(QPixmap("resources/ghost-white.png")));
    ghosts.push_back(ghostOrange = new EnemyOrange(QPixmap("resources/ghost-orange.png")));
    // ghosts are connected to player in Enemy's constructor

    // configuration
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBackgroundBrush(QBrush(QImage("resources/board-padded.png").scaled(SCREEN_WIDTH, SCREEN_HEIGHT)));
    player->setFlag(QGraphicsItem::ItemIsFocusable); // it's able to be focused
    player->setFocus();

    // main event loop timer
    setMainTimer();

    // Add points
    addPoints();

    // add Items to scene
    scene->addItem(player);
    for (Enemy* ghost : ghosts)
        scene->addItem(ghost);
    scene->addItem(scoreText);

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
            QObject::connect(point, SIGNAL(collected(int)), player, SLOT(addScore(int)));
            if (point->points == POINTS_BIG)
            {
                for (Enemy* ghost : ghosts)
                {
                    QObject::connect(point, SIGNAL(collected(int)), ghost, SLOT(scare()));
                }
            }
            points.push_back(point); // tracker
        }
    }
}

void Game::removePoints()
{
    for (Collectible* point : points)
    {
        delete point;
    }
    points.clear();
}

bool Game::isOver()
{
    return m_isOver;
}

#include <QCoreApplication>
#include <iostream>
void Game::gameOver()
{
    std::cout << "GAME OVER !\n";
    // QCoreApplication::exit(0);
    removePoints();
    // display black screen with text
    // focus it so that it receives keyboard inputs
    // enter to restart, and reload the game then

    // QGraphicsRectItem* panel = new QGraphicsRectItem();
    // panel->setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    // panel->setBrush(Qt::black);

    // QGraphicsTextItem* text = new QGraphicsTextItem;
    // text->setParentItem(panel);
    // text->setPlainText(QString("GAME OVER !\nyour score is: ") + QString::number(player->getScore()) +
    //                    QString("\npress [ENTER] to restart"));
    // text->setDefaultTextColor(Qt::white);
    // text->setFont(QFont("times", 32));

    // scene->addItem(panel);
}

void Game::restart()
{
    // reset player
    // reset ghosts
    // reset points
    // reset score counter
}
void Game::setMainTimer()
{
    mainTimer = new QTimer();
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
            QTimer::singleShot(i * 7500, ghosts[i], SLOT(deploy()));
        }
    }
}