#ifndef GAME_H
#define GAME_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "headers/board.h"
#include "headers/config.h"
#include "headers/enemies.h"
#include "headers/player.h"

class Game : public QGraphicsView
{
  public:
    Game(QWidget* parent = nullptr);
    QGraphicsScene* scene;
    Player* player;
    EnemyRed* ghostRed;
    EnemyBlue* ghostBlue;
    EnemyWhite* ghostWhite;
    EnemyOrange* ghostOrange;
};
extern Game* game;
#endif