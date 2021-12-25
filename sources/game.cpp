#include "headers/game.h"

#include <QGraphicsRectItem>
#include <QTimer>

Game::Game(QWidget* parent) : QGraphicsView(parent)
{
    // initialize members
    scene = new QGraphicsScene();
    player = new Player();

    // configuration
    setScene(scene);
    // show(); // I call this in main.cpp
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBackgroundBrush(QBrush(QImage("resources/board.png").scaled(SCREEN_WIDTH, SCREEN_HEIGHT)));

    player->setFlag(QGraphicsItem::ItemIsFocusable); // it's able to be focused
    player->setFocus();

    // main event loop timer
    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(move()));
    // timer->start(1000 / FPS);

    // add Items to scene
    scene->addItem(player);
    player->setPos(Board::cellToPx(1, 1).x + PIXELS_PER_UNIT / 2, Board::cellToPx(1, 1).y + PIXELS_PER_UNIT);

    // debug:  add a white rect for active cell where players center is:
    QGraphicsRectItem* debugRect = new QGraphicsRectItem();
    Position playerCell = player->getOccupiedCell();
    playerCell = Board::cellToPx(playerCell.x, playerCell.y); // reuse for
    debugRect->setRect(playerCell.x, playerCell.y, 8 * SCALE_FACTOR, 8 * SCALE_FACTOR);
    debugRect->setBrush(Qt::white);
    scene->addItem(debugRect);
}