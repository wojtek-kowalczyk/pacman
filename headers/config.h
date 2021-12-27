#pragma once

constexpr int SCALE_FACTOR = 3;         // change this
constexpr int TRUE_SCREEN_WIDTH = 224;  // don't change
constexpr int TRUE_SCREEN_HEIGHT = 248; // don't change
constexpr int SCREEN_WIDTH = TRUE_SCREEN_WIDTH * SCALE_FACTOR;
constexpr int SCREEN_HEIGHT = TRUE_SCREEN_HEIGHT * SCALE_FACTOR;
constexpr float PLAYER_MOVE_SPEED = 3.0f;
constexpr float GHOST_MOVE_SPEED = 2.7f;
constexpr int FPS = 60;
constexpr int PIXELS_PER_UNIT = 8;
constexpr int POINTS_SMALL = 100;
constexpr int POINTS_BIG = 200;
constexpr int POINTS_GHOST = 400;
constexpr int HITBOX_SHRINK = 6 * SCALE_FACTOR;
