#ifndef PLAYER_H
#define PLAYER_H

#include "headers/board.h"
#include "headers/config.h"
#include "headers/entity.h"
#include <QKeyEvent>

class Player : public Entity
{
    Q_OBJECT
  private:
    int score; // score is here not in game class since I don't want game to have slots
    // jokes on me, I added slots to game anyway, but this stays here
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
    void resetScore();

    // additional slots
  public slots:
    void addScore(int value);
  signals:
    void scoreChanged(int currScore);
};

#endif