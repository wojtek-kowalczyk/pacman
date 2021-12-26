#include "headers/player.h"
#include <iostream>

Player::Player()
{
    QPixmap pm("resources/pacman.png");
    setPixmap(pm.scaled(pm.rect().width() * SCALE_FACTOR, pm.rect().height() * SCALE_FACTOR));
    moveDirection = LEFT;
    requestedDirection = LEFT;
}

void Player::setMoveDirection(Direction dir)
{
    if (dir != moveDirection)
    {
        moveDirection = dir;
    }
}
void Player::setRequestedDirection(Direction dir)
{
    if (dir != requestedDirection)
    {
        requestedDirection = dir;
    }
}

void Player::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left)
    {
        setRequestedDirection(LEFT);
    }
    else if (event->key() == Qt::Key_Right)
    {
        setRequestedDirection(RIGHT);
    }
    else if (event->key() == Qt::Key_Up)
    {
        setRequestedDirection(UP);
    }
    else if (event->key() == Qt::Key_Down)
    {
        setRequestedDirection(DOWN);
    }
    else // debug:: advance with space for example. setting dir doesn't move
    {
        move();
    }
}

Vector2 Player::getOccupiedCell()
{
    return Board::pxToCell(x() + pixmap().rect().width() / 2, y() + pixmap().rect().height() / 2);
}

// returns true if the next cell in movedirection is not a wall
bool Player::canMove()
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
    std::cout << "INSIDE canMove(): querying board at " << row << ", " << col << '\n';
    return Board::query(row, col) != 0;
}

#include <QGraphicsScene>
void Player::DEBUG_drawCell()
{
    // debug:  make the current player's cell "light up"
    delete DEBUG_cell;
    DEBUG_cell = new QGraphicsRectItem();
    Vector2 pos = Board::cellToPx(getOccupiedCell().x, getOccupiedCell().y);
    DEBUG_cell->setRect(pos.x, pos.y, 8 * SCALE_FACTOR, 8 * SCALE_FACTOR);
    DEBUG_cell->setBrush(Qt::white);
    scene()->addItem(DEBUG_cell);
}

void Player::move()
{
    std::cout << "trying to move the player\n";
    // see if can move in the requested direction
    Vector2 playerCell{getOccupiedCell()};
    std::cout << "player in cell: " << playerCell.x << ", " << playerCell.y << '\n';
    switch (requestedDirection)
    {
    case LEFT:
        playerCell.y += -1;
        break;
    case RIGHT:
        playerCell.y += 1;
        break;
    case UP:
        playerCell.x += -1;
        break;
    case DOWN:
        playerCell.x += 1;
        break;
    default:
        break;
    }
    std::cout << "requested cell: " << playerCell.x << ", " << playerCell.y << '\n';
    if (Board::query(playerCell.x, playerCell.y) != 0)
    {
        std::cout << "setting movedir to requested dir\n";
        setMoveDirection(requestedDirection);
    }

    std::cout << "checking if can move\n";
    if (!canMove())
    {
        std::cout << "can't, returning\n";
        return;
    }

    std::cout << "can, moving\n";
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
}