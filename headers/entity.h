#pragma once
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

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
  protected:
    Direction moveDirection = LEFT;      // actual direction the player is facing and moving
    Direction requestedDirection = LEFT; // the direcion we want the palyer to move when it's possible
    QGraphicsRectItem* DEBUG_cell;
    QGraphicsRectItem* hitbox;
    bool canMove();                     // returns true if the next cell in movedirection is not a wall
    virtual void checkCollisions() = 0; // pure virtual means there's no "default implementation"

  public:
    Vector2 getOccupiedCell(); // get the cell that player's CENTER is in
    virtual void setMoveDirection(Direction);
    void setRequestedDirection(Direction);
  public slots:
    virtual void move() = 0;
};