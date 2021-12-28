#include "headers/enemy.h"
#include <iostream>

Enemy::Enemy()
{
    QPixmap* pm = new QPixmap("resources/ghost-red.png");
    setPixmap(pm->scaled(pm->rect().width() * SCALE_FACTOR, pm->rect().height() * SCALE_FACTOR));
}

void Enemy::move()
{
    chooseAndSetDirection();

    Vector2 dir;
    switch (moveDirection)
    {
    case LEFT:
        dir = Vector2{-1, 0};
        break;
    case RIGHT:
        dir = Vector2{1, 0};
        break;
    case UP:
        dir = Vector2{0, -1};
        break;
    case DOWN:
        dir = Vector2{0, 1};
        break;
    default:
        dir = Vector2{-1, 0};
        break;
    }
    setPos(x() + dir.x * PLAYER_MOVE_SPEED, y() + dir.y * PLAYER_MOVE_SPEED);

    // edge teleportation
    if (x() < 0)
        setPos(x() + scene()->width(), y());
    else if (x() > scene()->width())
        setPos(x() - scene()->width(), y());
    // not adding vertical case -> same reason as in Board::query
    checkCollisions();
}

void Enemy::checkCollisions()
{
    // todo - implement
}