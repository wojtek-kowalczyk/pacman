#ifndef PLAYER_H
#define PLAYER_H

#include "headers/board.h"
#include "headers/config.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>

enum MoveDirection
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
    MoveDirection moveDirection;
    MoveDirection facingDirection;
    bool canMove();

  public:
    Player();
    Position getOccupiedCell();
    void setMoveDirection(MoveDirection);
    void setFacingDirection(MoveDirection);
    void keyPressEvent(QKeyEvent* event);
  public slots:
    void move();
    // signals:
};

#endif