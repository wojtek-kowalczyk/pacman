#include "headers/enemies.h"
#include "headers/game.h"

Vector2 EnemyBlue::chooseTarget()
{
    // THE LOOK-AHEAD
    int ahead = 4;
    Vector2 player = game->player->getOccupiedCell();
    return Vector2{player.x + v_directions[game->player->getMoveDirection()].y * ahead,
                   player.y + v_directions[game->player->getMoveDirection()].x * ahead};
}

Vector2 EnemyWhite::chooseTarget()
{
    // THE TACTICIAN
    Vector2 player = game->player->getOccupiedCell();
    Vector2 redToPlayer{player.x - game->ghostRed->getOccupiedCell().x, player.y - game->ghostRed->getOccupiedCell().y};
    return Vector2{redToPlayer.x * 2, redToPlayer.y * 2};
}

Vector2 EnemyOrange::chooseTarget()
{
    // THE RANDOM
    Vector2 player = game->player->getOccupiedCell();
    return Vector2{player.x + rand() % (4 * 2) - 4, player.y + rand() % (4 * 2) - 4};
}

Vector2 EnemyRed::chooseTarget()
{
    // THE FOLLOWER
    return game->player->getOccupiedCell();
}