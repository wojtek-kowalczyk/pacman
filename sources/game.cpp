#include "headers/game.h"
#include "headers/collectible.h"
#include "headers/text.h"
#include <QTimer>
#include <vector>

Game* game = nullptr; // this has to be here so that the linker sees it.

Game::Game(QWidget* parent) : QGraphicsView(parent)
{
    // todo - clean this mess up
    if (!game)
        game = this;
    else
        abort();

    // initialize members
    m_isOver = false;
    scene = new QGraphicsScene();
    player = new Player();
    scoreText = new CustomText();
    std::vector<Enemy*> ghosts;
    ghosts.push_back(ghostOrange = new EnemyOrange(QPixmap("resources/ghost-orange.png")));
    ghosts.push_back(ghostWhite = new EnemyWhite(QPixmap("resources/ghost-white.png")));
    ghosts.push_back(ghostBlue = new EnemyBlue(QPixmap("resources/ghost-blue.png")));
    ghosts.push_back(ghostRed = new EnemyRed(QPixmap("resources/ghost-red.png")));

    // configuration
    setScene(scene);
    // show(); // I call this in main.cpp
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBackgroundBrush(QBrush(QImage("resources/board-padded.png").scaled(SCREEN_WIDTH, SCREEN_HEIGHT)));

    player->setFlag(QGraphicsItem::ItemIsFocusable); // it's able to be focused
    player->setFocus();

    // main event loop timer
    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(move()));
    for (Enemy* ghost : ghosts)
        QObject::connect(timer, SIGNAL(timeout()), ghost, SLOT(move()));
    timer->start(1000 / FPS);
    // timer->start(1000 * 20 / FPS); // 20 times slower

    // Add points
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
        }
    }

#ifdef GAME_DEBUG
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(DEBUG_drawCell()));
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

    // additional connections
    for (Enemy* ghost : ghosts)
    {
        QObject::connect(ghost, SIGNAL(playerCaught()), player, SLOT(getCaught()));
    }

    // add text
    scene->addItem(scoreText);

    // add Items to scene
    scene->addItem(player);
    for (Enemy* ghost : ghosts)
        scene->addItem(ghost);
    // this sets player's topleft to center of the correct cell.
    player->setPos(Board::cellToPx(PLAYER_ENTRY_ROW, PLAYER_ENTRY_COLUMN).x + PIXELS_PER_UNIT * SCALE_FACTOR / 2,
                   Board::cellToPx(PLAYER_ENTRY_ROW, PLAYER_ENTRY_COLUMN).y + PIXELS_PER_UNIT * SCALE_FACTOR / 2);
    // this sets palyer's center to be in the cell's center
    player->setPos(player->x() - player->pixmap().rect().width() / 2,
                   player->y() - player->pixmap().rect().height() / 2);
    for (Enemy* ghost : ghosts)
    {
        // todo - this could call ghost.reseptPosition, alternatively. consider implementing this to entity
        ghost->setPos(Board::cellToPx(GHOST_ENTRY_ROW, GHOST_ENTRY_COLUMN).x + PIXELS_PER_UNIT * SCALE_FACTOR / 2,
                      Board::cellToPx(GHOST_ENTRY_ROW, GHOST_ENTRY_COLUMN).y + PIXELS_PER_UNIT * SCALE_FACTOR / 2);
        ghost->setPos(ghost->x() - ghost->pixmap().rect().width() / 2,
                      ghost->y() - ghost->pixmap().rect().height() / 2);
    }
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
}