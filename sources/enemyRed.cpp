#include "headers/enemyRed.h"

void EnemyRed::chooseAndSetDirection()
{
    // query front and side cells, pick to one closest to the player

    // if I already checked this cell -> move on
    Vector2 me = getOccupiedCell();
    if (prevCell.x == me.x && prevCell.y == me.y)
        return;
    prevCell = me;

    // get cells
    Vector2 player = game->player->getOccupiedCell();
    Vector2 cell_fwd{me.x + v_directions[moveDirection].y, me.y + v_directions[moveDirection].x};
    Vector2 cell_left{me.x + v_directions[(moveDirection + 3) % 4].y, me.y + v_directions[(moveDirection + 3) % 4].x};
    Vector2 cell_right{me.x + v_directions[(moveDirection + 1) % 4].y, me.y + v_directions[(moveDirection + 1) % 4].x};

    // compute distances
    float sqrDistances[3] = {999999.0, 999999.0, 999999.0};
    if (Board::query(cell_fwd.x, cell_fwd.y))
        sqrDistances[0] = Vector2::sqrDistance(player, cell_fwd);
    if (Board::query(cell_left.x, cell_left.y))
        sqrDistances[1] = Vector2::sqrDistance(player, cell_left);
    if (Board::query(cell_right.x, cell_right.y))
        sqrDistances[2] = Vector2::sqrDistance(player, cell_right);

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
        setMoveDirection(static_cast<Direction>((moveDirection + 3) % 4));
    else if (minIdx == 2)
        setMoveDirection(static_cast<Direction>((moveDirection + 1) % 4));
}