#include "headers/player.h"
#include "headers/collectible.h"
#include <iostream>

Player::Player()
{
    sprites[UP] = QPixmap("resources/pacman-up.png");
    sprites[DOWN] = QPixmap("resources/pacman-down.png");
    sprites[LEFT] = QPixmap("resources/pacman-left.png");
    sprites[RIGHT] = QPixmap("resources/pacman-right.png");

    setSprite(LEFT);
    moveDirection = LEFT;
    requestedDirection = LEFT;

    hitbox = new QGraphicsRectItem();
    hitbox->setParentItem(this);
    hitbox->setRect(x() + HITBOX_SHRINK, y() + HITBOX_SHRINK, pixmap().width() - 2 * HITBOX_SHRINK,
                    pixmap().height() - 2 * HITBOX_SHRINK);
    // hitbox->setVisible(false);
}

void Player::checkCollisions()
{
    QList<QGraphicsItem*> colliding = hitbox->collidingItems();
    for (int i = 0; i < colliding.size(); i++)
    {
        if (typeid(*(colliding[i])) == typeid(Collectible))
        {
            // todo - replace workaround
            // how do I access members of Collectible here?
            // virtual method allows the use of pointer to a base class, but I can't add my methods to the base class.
            // I NEED TO CALL MY METHOD ON COLLECTIBLE. now it's called in the destructor - seems wrong
            delete colliding[i];
        }
    }
}

void Player::setSprite(Direction dir)
{
    setPixmap(
        sprites[dir].scaled(sprites[dir].rect().width() * SCALE_FACTOR, sprites[dir].rect().height() * SCALE_FACTOR));
}

void Player::addScore(int score)
{
    this->score += score;
    std::cout << "Player's score: " << this->score << '\n';
}

void Player::setMoveDirection(Direction dir)
{
    if (dir != moveDirection)
    {
        moveDirection = dir;
        // set the sprite to face in the right direction
        setSprite(moveDirection);
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
    return Board::pxToCell(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
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
    // see if can move in the requested direction
    Vector2 playerCell{getOccupiedCell()};
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
    if (Board::query(playerCell.x, playerCell.y) != 0)
    {
        if (moveDirection != requestedDirection)
        {
            setMoveDirection(requestedDirection);
            // snap player to the center of the cell
            Vector2 targetPos{Board::cellToPx(getOccupiedCell().x, getOccupiedCell().y)};
            targetPos.x += PIXELS_PER_UNIT * SCALE_FACTOR / 2;
            targetPos.y += PIXELS_PER_UNIT * SCALE_FACTOR / 2;
            setPos(targetPos.x - pixmap().width() / 2, targetPos.y - pixmap().height() / 2);
            // ! when player hits the wall they stop a bit out of line, there is no snapping to the center of a cell
        }
    }

    if (!canMove())
    {
        return;
    }

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
    checkCollisions();
}