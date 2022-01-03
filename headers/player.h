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
    int score; // score is here not in game class since I don't want game to have slots
    QPixmap sprites[4];
    void setSprite(Direction dir); // sets and correctly resizes sprite for given direction. updates display.
    void checkCollisions() override;

  public:
    Player();
    void keyPressEvent(QKeyEvent* event);
    void setMoveDirection(Direction) override;
    void move() override;
    void getCaught() override;
    Direction getMoveDirection();
    int getScore();

    // additional slots
  public slots:
    void addScore(int value);
};

#endif