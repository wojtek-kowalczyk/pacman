#include "headers/entity.h"

bool Entity::canMove()
{
    if (!allowMovement)
        return false;
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
    }
    return Board::query(row, col) != 0;
}

void Entity::DEBUG_drawCell()
{
    if (DEBUG_cell)
        delete DEBUG_cell;
    DEBUG_cell = new QGraphicsRectItem();
    Vector2 pos = Board::cellToPx(getOccupiedCell().x, getOccupiedCell().y);
    DEBUG_cell->setRect(pos.x, pos.y, 8 * SCALE_FACTOR, 8 * SCALE_FACTOR);
    DEBUG_cell->setBrush(Qt::white);
    scene()->addItem(DEBUG_cell);
}

Vector2 Entity::getOccupiedCell()
{
    return Board::pxToCell(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
}

void Entity::putCenterInCell(int row, int col)
{
    this->setPos(Board::cellToPx(row, col).x + PIXELS_PER_UNIT * SCALE_FACTOR / 2,
                 Board::cellToPx(row, col).y + PIXELS_PER_UNIT * SCALE_FACTOR / 2);
    this->setPos(this->x() - this->pixmap().rect().width() / 2, this->y() - this->pixmap().rect().height() / 2);
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

void Entity::snapToCenter()
{
    Vector2 targetPos{Board::cellToPx(getOccupiedCell().x, getOccupiedCell().y)};
    targetPos.x += PIXELS_PER_UNIT * SCALE_FACTOR / 2;
    targetPos.y += PIXELS_PER_UNIT * SCALE_FACTOR / 2;
    setPos(targetPos.x - pixmap().width() / 2, targetPos.y - pixmap().height() / 2);
};