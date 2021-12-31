#ifndef GAME_H
#define GAME_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "headers/board.h"
#include "headers/config.h"
#include "headers/enemies.h"
#include "headers/player.h"

// #define GAME_DEBUG

class Game : public QGraphicsView
{
  private:
    bool m_isOver;

  public:
    QGraphicsScene* scene;
    Player* player;
    EnemyRed* ghostRed;
    EnemyBlue* ghostBlue;
    EnemyWhite* ghostWhite;
    EnemyOrange* ghostOrange;
    Game(QWidget* parent = nullptr);
    bool isOver();
    void gameOver();
};
extern Game* game;
#endif