#pragma once
#include "headers/enemy.h"
#include "headers/game.h"

class EnemyRed : public Enemy
{
  private:
    void chooseAndSetDirection() override;
};