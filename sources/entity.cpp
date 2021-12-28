#include "headers/entity.h"

bool Entity::canMove()
{
    int row = getOccupiedCell().x;
    int col = getOccupiedCell().y;
    switch (moveDirection)
    {
    case LEFT:
        col += -1;
        break;
    case RIGHT:
        col += 1;
        break;
    case UP:
        row += -1;
        break;
    case DOWN:
        row += 1;
        break;
    default:
        break;
    }
    return Board::query(row, col) != 0;
}

Vector2 Entity::getOccupiedCell()
{
    return Board::pxToCell(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
}

void Entity::setMoveDirection(Direction dir)
{
    if (dir != moveDirection)
    {
        moveDirection = dir;
    }
}

void Entity::setRequestedDirection(Direction dir)
{
    if (dir != requestedDirection)
    {
        requestedDirection = dir;
    }
}