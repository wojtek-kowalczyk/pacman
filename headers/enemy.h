#pragma once
#include "headers/entity.h"

class Enemy : public Entity
{
  protected:
    Vector2 prevCell{-1, -1};
    void checkCollisions() override;
    virtual void chooseAndSetDirection() = 0;

  public:
    Enemy();
    // doesn't have to be declared as slot. already declared in
    // base class. Ther's only such need for additional function base class doesn't have
    void move() override;
};