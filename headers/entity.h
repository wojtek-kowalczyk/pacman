#pragma once
#include "headers/board.h"
#include "headers/config.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QObject>

// clockwise order - important for ghost AI
// dir + 1 is next clockwise, -1 anti-clockwise
// dir + 2 is opposite dir
enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
};
constexpr Vector2 v_directions[4] = {
    Vector2{0, -1},
    Vector2{1, 0},
    Vector2{0, 1},
    Vector2{-1, 0},
};

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
  protected:
    Direction moveDirection = LEFT;      // actual direction the player is facing and moving
    Direction requestedDirection = LEFT; // the direcion we want the palyer to move when it's possible
    QGraphicsRectItem* DEBUG_cell = nullptr;
    QGraphicsRectItem* hitbox = nullptr;
    bool canMove();                     // returns true if the next cell in movedirection is not a wall
    virtual void checkCollisions() = 0; // pure virtual means there's no "default implementation"

  public:
    Vector2 getOccupiedCell(); // get the cell that player's CENTER is in
    virtual void setMoveDirection(Direction);
    void setRequestedDirection(Direction);
  public slots:
    virtual void move() = 0;
    void DEBUG_drawCell(); // draw a square representing the current cell entity is in.
};