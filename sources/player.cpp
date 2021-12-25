#include "headers/player.h"

Player::Player()
{
    QPixmap pm("resources/pacman.png");
    setPixmap(pm.scaled(pm.rect().width() * SCALE_FACTOR, pm.rect().height() * SCALE_FACTOR));
    moveDirection = LEFT;
}

void Player::setMoveDirection(MoveDirection md)
{
    if (md != moveDirection)
    {
        moveDirection = md;
    }
}

void Player::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left)
    {
        setMoveDirection(LEFT);
    }
    else if (event->key() == Qt::Key_Right)
    {
        setMoveDirection(RIGHT);
    }
    else if (event->key() == Qt::Key_Up)
    {
        setMoveDirection(UP);
    }
    else if (event->key() == Qt::Key_Down)
    {
        setMoveDirection(DOWN);
    }
}
Position Player::getOccupiedCell()
{
    return Board::pxToCell(x() + pixmap().rect().width() / 2, y() + pixmap().rect().height() / 2);
}

bool Player::canMove()
{
    return true; // temp
    Position playerPos{Board::pxToCell(x(), y())};
    return Board::query(playerPos) != 0;
}

#include <QGraphicsScene>
void Player::DEBUG_drawCell()
{
    // debug:  make the current player's cell "light up"
    delete DEBUG_cell;
    DEBUG_cell = new QGraphicsRectItem();
    Position pos = Board::cellToPx(getOccupiedCell().x, getOccupiedCell().y);
    DEBUG_cell->setRect(pos.x, pos.y, 8 * SCALE_FACTOR, 8 * SCALE_FACTOR);
    DEBUG_cell->setBrush(Qt::white);
    scene()->addItem(DEBUG_cell);
}

void Player::move()
{
    if (!canMove())
    {
        return;
    }
    int _x, _y;
    switch (this->moveDirection)
    {
    case LEFT:
        _x = -1;
        _y = 0;
        break;
    case RIGHT:
        _x = 1;
        _y = 0;
        break;
    case UP:
        _y = -1;
        _x = 0;
        break;
    case DOWN:
        _y = 1;
        _x = 0;
        break;
    default:
        _x = -1;
        _y = 0;
        break;
    }
    setPos(x() + _x * PLAYER_MOVE_SPEED, y() + _y * PLAYER_MOVE_SPEED);
}