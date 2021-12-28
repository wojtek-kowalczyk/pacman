#ifndef PLAYER_H
#define PLAYER_H

#include "headers/board.h"
#include "headers/config.h"
#include "headers/entity.h"
#include <QKeyEvent>

class Player : public Entity
{
    // this macro has to be in derived class as well. Re-run qmake after adding it.
    // I mean only if it has additional signals the base class doesn't have
    Q_OBJECT
  private:
    int score;
    QPixmap sprites[4];
    void setSprite(Direction dir); // sets and correctly resizes sprite for given direction. updates display.
    void checkCollisions() override;

  public:
    Player();
    void keyPressEvent(QKeyEvent* event);
    void setMoveDirection(Direction) override;
    void move() override;
  public slots:
    void DEBUG_drawCell(); // draw a square representing the current cell player is in.
    void addScore(int value);
    // signals:
};

#endif