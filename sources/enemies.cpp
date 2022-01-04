#include "headers/enemies.h"
#include "headers/game.h"

Vector2 EnemyBlue::chooseTarget()
{
    // THE LOOK-AHEAD
    // targets 4 cell in front of player.
    int ahead = 4;
    Vector2 player = game->player->getOccupiedCell();
    Vector2 target{player.x + v_directions[game->player->getMoveDirection()].y * ahead,
                   player.y + v_directions[game->player->getMoveDirection()].x * ahead};
#ifdef GAME_DEBUG
    DEBUG_drawTarget(target, Qt::blue);
#endif
    return target;
}

Vector2 EnemyWhite::chooseTarget()
{
    // THE TACTICIAN
    // targets the cell at 2x vector from red to blue's target
    int ahead = 4;
    Vector2 player = game->player->getOccupiedCell();
    player = Vector2{player.x + v_directions[game->player->getMoveDirection()].y * ahead,
                     player.y + v_directions[game->player->getMoveDirection()].x * ahead};

    Vector2 red = game->ghostRed->getOccupiedCell();
    Vector2 redToPlayer{player.x - red.x, player.y - red.y};
    Vector2 target{red.x + redToPlayer.x * 2, red.y + redToPlayer.y * 2};
#ifdef GAME_DEBUG
    DEBUG_drawTarget(target, Qt::white);
#endif
    return target;
}

Vector2 EnemyOrange::chooseTarget()
{
    // THE RANDOM
    Vector2 player = game->player->getOccupiedCell();
    Vector2 target{player.x + (rand() % (4 * 2)) - 4, player.y + (rand() % (4 * 2)) - 4};
#ifdef GAME_DEBUG
    DEBUG_drawTarget(target, Qt::darkYellow);
#endif
    return target;
}

Vector2 EnemyRed::chooseTarget()
{
    // THE FOLLOWER
    // no drawing of target since it's always the player
    return game->player->getOccupiedCell();
}