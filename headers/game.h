#ifndef GAME_H
#define GAME_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "headers/board.h"
#include "headers/collectible.h"
#include "headers/config.h"
#include "headers/enemies.h"
#include "headers/player.h"
#include "headers/text.h"
#include <QTimer>
#include <vector>

// #define GAME_DEBUG

class Game : public QGraphicsView
{
  private:
    bool m_isOver;
    void restart();
    void addPoints();
    void removePoints();
    void setMainTimer();
    void setInitialPositions();

  public:
    QGraphicsScene* scene;
    Player* player;
    EnemyRed* ghostRed;
    EnemyBlue* ghostBlue;
    EnemyWhite* ghostWhite;
    EnemyOrange* ghostOrange;
    CustomText* scoreText;
    QTimer* mainTimer;
    std::vector<Collectible*> points;
    std::vector<Enemy*> ghosts;

    Game(QWidget* parent = nullptr);
    bool isOver();
    void gameOver();
};
extern Game* game;
#endif