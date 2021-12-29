#pragma once
#include "headers/enemy.h"

class EnemyRed : public Enemy
{
  private:
    Vector2 chooseTarget() override;

  public:
    EnemyRed(QPixmap sprite) : Enemy{sprite} {};
};

class EnemyWhite : public Enemy
{
  private:
    Vector2 chooseTarget() override;

  public:
    EnemyWhite(QPixmap sprite) : Enemy{sprite} {};
};

class EnemyBlue : public Enemy
{
  private:
    Vector2 chooseTarget() override;

  public:
    EnemyBlue(QPixmap sprite) : Enemy{sprite} {};
};

class EnemyOrange : public Enemy
{
  private:
    Vector2 chooseTarget() override;

  public:
    EnemyOrange(QPixmap sprite) : Enemy{sprite} {};
};