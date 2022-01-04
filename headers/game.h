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
#include <QGraphicsTextItem>
#include <QObject>
#include <QTimer>
#include <vector>

// #define GAME_DEBUG

class Game : public QGraphicsView
{
    Q_OBJECT
  private:
    bool m_isOver;
    int pointsCounter;
    void addPoints();
    void removePoints();
    void setMainTimer();
    void setInitialPositions();
    void setGameOverPanel();
    void setEntities();
    void setScoreText();

  public:
    const bool godMode = true;
    QGraphicsScene* scene;
    QGraphicsRectItem* gameOverPanel;
    Player* player;
    EnemyRed* ghostRed;
    EnemyBlue* ghostBlue;
    EnemyWhite* ghostWhite;
    EnemyOrange* ghostOrange;
    QGraphicsTextItem* scoreText;
    QGraphicsTextItem* endScoreText;
    QTimer* mainTimer;
    std::vector<Enemy*> ghosts;

    Game(QWidget* parent = nullptr);
    bool isOver();
    void restart();
    void gameOver(bool win);
    void updateEndScoreText(bool win);
  public slots:
    void updateScoreText();
    void onPointCollected();
  signals:
    void pointsDestructionOrdered();
};
extern Game* game;
#endif