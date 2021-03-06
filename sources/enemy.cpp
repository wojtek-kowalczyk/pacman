#include "headers/enemy.h"
#include "headers/game.h"
#include <iostream>
#include <map>
#include <vector>

Enemy::Enemy(QPixmap sprite)
{

    regularSprite = sprite;
    scaredSprite = QPixmap("resources/ghost-scared.png");
    setPixmap(sprite.scaled(sprite.rect().width() * SCALE_FACTOR, sprite.rect().height() * SCALE_FACTOR));

    // although this is copy&paste from player I'm not moving this to base class since
    // I might want this to be different than players's someday
    hitbox = new QGraphicsRectItem();
    hitbox->setParentItem(this);
    hitbox->setRect(x() + HITBOX_SHRINK, y() + HITBOX_SHRINK, pixmap().width() - 2 * HITBOX_SHRINK,
                    pixmap().height() - 2 * HITBOX_SHRINK);
    hitbox->setVisible(false);
    QObject::connect(this, SIGNAL(playerCaught()), game->player, SLOT(getCaught()));
    deployTimer = new QTimer();
    deployTimer->setSingleShot(true);
}

// todo - this could be improved
void Enemy::chooseAndSetDirection()
{
    // query front and side cells, pick to one closest to target

    // if I already checked this cell -> move on
    Vector2 me = getOccupiedCell();
    if (prevCell.x == me.x && prevCell.y == me.y)
        return;
    prevCell = me;

    // get cells
    Vector2 cell_fwd{me.x + v_directions[moveDirection].y, me.y + v_directions[moveDirection].x};
    Vector2 cell_left{me.x + v_directions[(moveDirection + 3) % 4].y, me.y + v_directions[(moveDirection + 3) % 4].x};
    Vector2 cell_right{me.x + v_directions[(moveDirection + 1) % 4].y, me.y + v_directions[(moveDirection + 1) % 4].x};

    if (mode == CHASE)
    {
        Vector2 target = chooseTarget();

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
            // left of curr
            setMoveDirection(static_cast<Direction>((moveDirection + 3) % 4));
            snapToCenter();
        }
        else if (minIdx == 2)
        {
            // right of curr
            setMoveDirection(static_cast<Direction>((moveDirection + 1) % 4));
            snapToCenter();
        }
        // else remain curr (forward)
    }
    else if (mode == SCARED)
    {
        std::vector<Vector2> avlb;

        // check which directions are available to move:
        if (Board::query(cell_fwd.x, cell_fwd.y))
            avlb.push_back(cell_fwd);
        if (Board::query(cell_left.x, cell_left.y))
            avlb.push_back(cell_left);
        if (Board::query(cell_right.x, cell_right.y))
            avlb.push_back(cell_right);

        // choose random
        // this makes the seed change everytime the function is run so if all
        // ghosts call this on the same frame they get different seed
        static unsigned int run = 1;
        srand(time(0) + (run++));
        if (avlb.size() > 0)
        {
            int random = rand() % avlb.size();
            if (avlb[random].x == cell_left.x && avlb[random].y == cell_left.y)
            {
                setMoveDirection(static_cast<Direction>((moveDirection + 3) % 4));
                snapToCenter();
            }
            else if (avlb[random].x == cell_right.x && avlb[random].y == cell_right.y)
            {
                setMoveDirection(static_cast<Direction>((moveDirection + 1) % 4));
                snapToCenter();
            }
        }
        // else just keep moving in the same dir
    }
}

void Enemy::move()
{
    if (!allowMovement)
        return;
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
    float speed = mode == CHASE ? GHOST_MOVE_SPEED : GHOST_MOVE_SPEED_SCARED;
    setPos(x() + dir.x * speed, y() + dir.y * speed);

    // edge teleportation
    if (x() < 0)
        setPos(x() + scene()->width(), y());
    else if (x() > scene()->width())
        setPos(x() - scene()->width(), y());

    checkCollisions();
}

void Enemy::checkCollisions()
{
    QList<QGraphicsItem*> colliding = hitbox->collidingItems();
    for (int i = 0; i < colliding.size(); i++)
    {
        if (typeid(*(colliding[i])) == typeid(Player))
        {
            if (mode == CHASE)
            {
                emit playerCaught();
            }
            else if (mode == SCARED)
            {
                this->getCaught();
            }
        }
    }
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

void Enemy::scare()
{
    mode = SCARED;
    moveDirection = static_cast<Direction>((moveDirection + 2) % 4); // reverse
    setPixmap(
        scaredSprite.scaled(scaredSprite.rect().width() * SCALE_FACTOR, scaredSprite.rect().height() * SCALE_FACTOR));
    // the behaviour also changes since direction choosing depends on mode
    QTimer::singleShot(GHOST_SCARE_TIME, this, SLOT(unscare()));
}

void Enemy::unscare()
{
    mode = CHASE;
    setPixmap(regularSprite.scaled(regularSprite.rect().width() * SCALE_FACTOR,
                                   regularSprite.rect().height() * SCALE_FACTOR));
}

void Enemy::getCaught()
{
    game->player->addScore(POINTS_GHOST);
    setPos(Board::cellToPx(GHOST_HOUSE_ROW, GHOST_HOUSE_COLUMN).x,
           Board::cellToPx(GHOST_HOUSE_ROW, GHOST_HOUSE_COLUMN).y);
    allowMovement = false;
    QTimer::singleShot(GHOST_RESPAWN_DELAY, this, SLOT(deploy()));
    unscare();
}

void Enemy::deploy()
{
    putCenterInCell(GHOST_ENTRY_ROW, GHOST_ENTRY_COLUMN);
    allowMovement = true;
}