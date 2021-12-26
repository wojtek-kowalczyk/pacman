#ifndef PLAYER_H
#define PLAYER_H

#include "headers/board.h"
#include "headers/config.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
  private:
    Direction moveDirection;
    Direction requestedDirection;
    QGraphicsRectItem* DEBUG_cell;
    bool canMove();

  public:
    Player();
    Position getOccupiedCell(); // get the cell that player's CENTER is in
    void setMoveDirection(Direction);
    void setRequestedDirection(Direction);
    void keyPressEvent(QKeyEvent* event);
  public slots:
    void DEBUG_drawCell();
    void move();
    // signals:
};

#endif