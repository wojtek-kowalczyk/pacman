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
    Direction moveDirection;      // actual direction the player is facing and moving
    Direction requestedDirection; // the direcion we want the palyer to move when it's possible
    QGraphicsRectItem* DEBUG_cell;
    bool canMove();

  public:
    Player();
    Vector2 getOccupiedCell(); // get the cell that player's CENTER is in
    void setMoveDirection(Direction);
    void setRequestedDirection(Direction);
    void keyPressEvent(QKeyEvent* event);
  public slots:
    void DEBUG_drawCell(); // draw a square representing the current cell player is in.
    void move();
    // signals:
};

#endif