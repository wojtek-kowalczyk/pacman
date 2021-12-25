#include "headers/game.h"

#include <QGraphicsRectItem>
#include <QTimer>
#include <iostream>
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
    // this sets player's topleft to center of the correct cell.
    player->setPos(Board::cellToPx(1, 1).x + PIXELS_PER_UNIT * SCALE_FACTOR / 2,
                   Board::cellToPx(1, 1).y + PIXELS_PER_UNIT * SCALE_FACTOR / 2);
    // this sets palyer's center to be in the cell's center
    player->setPos(player->x() - player->pixmap().rect().width() / 2,
                   player->y() - player->pixmap().rect().height() / 2);

    // debug:  add a white rect for active cell where players center is:
    QGraphicsRectItem* debugRect = new QGraphicsRectItem();
    Position playerCell = player->getOccupiedCell();
    std::cout << "player's cell: " << playerCell.x << ", " << playerCell.y << '\n';
    Position rectPos = Board::cellToPx(playerCell.x, playerCell.y);
    std::cout << "rect pos top left: " << rectPos.x << ", " << rectPos.y << '\n';
    debugRect->setRect(rectPos.x, rectPos.y, 8 * SCALE_FACTOR, 8 * SCALE_FACTOR);
    debugRect->setBrush(Qt::white);
    scene->addItem(debugRect);
}