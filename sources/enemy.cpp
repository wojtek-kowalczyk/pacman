#include "headers/enemy.h"
#include "headers/game.h"
#include <iostream>

Enemy::Enemy(QPixmap sprite)
{
    setPixmap(sprite.scaled(sprite.rect().width() * SCALE_FACTOR, sprite.rect().height() * SCALE_FACTOR));
}

void Enemy::chooseAndSetDirection()
{
    // * FOLLOW A RANDOM POINT THAT IS within 4 cells away from player

    // query front and side cells, pick to one closest to target

    // if I already checked this cell -> move on
    Vector2 me = getOccupiedCell();
    if (prevCell.x == me.x && prevCell.y == me.y)
        return;
    prevCell = me;

    // get cells
    Vector2 target = chooseTarget();
    Vector2 cell_fwd{me.x + v_directions[moveDirection].y, me.y + v_directions[moveDirection].x};
    Vector2 cell_left{me.x + v_directions[(moveDirection + 3) % 4].y, me.y + v_directions[(moveDirection + 3) % 4].x};
    Vector2 cell_right{me.x + v_directions[(moveDirection + 1) % 4].y, me.y + v_directions[(moveDirection + 1) % 4].x};

    // compute distances
    float sqrDistances[3] = {999999.0, 999999.0, 999999.0};
    if (Board::query(cell_fwd.x, cell_fwd.y))
        sqrDistances[0] = Vector2::sqrDistance(target, cell_fwd);
    if (Board::query(cell_left.x, cell_left.y))
        sqrDistances[1] = Vector2::sqrDistance(target, cell_left);
    if (Board::query(cell_right.x, cell_right.y))
        sqrDistances[2] = Vector2::sqrDistance(target, cell_right);

    // find minimum
    float minVal = sqrDistances[0];
    int minIdx = 0;
    for (int i = 1; i < 3; i++)
    {
        if (sqrDistances[i] < minVal)
        {
            minVal = sqrDistances[i];
            minIdx = i;
        }
    }

    // set correct direction
    if (minIdx == 1)
    {
        setMoveDirection(static_cast<Direction>((moveDirection + 3) % 4));
        snapToCenter();
    }
    else if (minIdx == 2)
    {
        setMoveDirection(static_cast<Direction>((moveDirection + 1) % 4));
        snapToCenter();
    }
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
    setPos(x() + dir.x * GHOST_MOVE_SPEED, y() + dir.y * GHOST_MOVE_SPEED);

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

void Enemy::DEBUG_drawTarget(Vector2 target, Qt::GlobalColor color)
{
    if (DEBUG_targetCell)
        delete DEBUG_targetCell;
    DEBUG_targetCell = new QGraphicsRectItem();
    DEBUG_targetCell->setRect(Board::cellToPx(target.x, target.y).x, Board::cellToPx(target.x, target.y).y,
                              8 * SCALE_FACTOR, 8 * SCALE_FACTOR);
    DEBUG_targetCell->setBrush(color);
    scene()->addItem(DEBUG_targetCell);
}