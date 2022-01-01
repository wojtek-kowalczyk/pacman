#pragma once
#include "headers/entity.h"

enum Mode
{
    CHASE,
    SCARED,
};

class Enemy : public Entity
{
    // this macro has to be here if if I have some additional slots (wrt base class)
    Q_OBJECT
  protected:
    Mode mode = CHASE;
    QPixmap regularSprite;
    QPixmap scaredSprite;
    Vector2 prevCell{-1, -1};
    QGraphicsRectItem* DEBUG_targetCell = nullptr;
    void DEBUG_drawTarget(Vector2 target, Qt::GlobalColor color);
    void checkCollisions() override;
    void chooseAndSetDirection();
    virtual Vector2 chooseTarget() = 0;
    void respawn();

  public slots:
    void scare();   // makes the ghost be scared for some time and calls unscare
    void unscare(); // returns the ghost to normal state
  signals:
    void playerCaught();

  public:
    Enemy(QPixmap sprite);
    // doesn't have to be declared as slot. already declared as slot in
    // base class. There's only such need for additional function base class doesn't have
    // (and for such addition Q_OBJECT macro is needed in derived class as well)
    void move() override;
};