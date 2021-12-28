#pragma once
#include "headers/entity.h"
class Enemy : public Entity
{
  private:
    Vector2 prevCell{-1, -1};
    void checkCollisions() override;
    void chooseAndSetDirection();

  public:
    Enemy();
    // doesn't have to be declared as slot. already declared in
    // base class. Ther's only such need for additional function base class doesn't have
    void move() override;
};