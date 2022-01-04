#pragma once

constexpr int SCALE_FACTOR = 3;              // change this
constexpr int TRUE_SCREEN_WIDTH = 224;       // don't change
constexpr int TRUE_SCREEN_HEIGHT = 248 + 16; // don't change
constexpr int SCREEN_WIDTH = TRUE_SCREEN_WIDTH * SCALE_FACTOR;
constexpr int SCREEN_HEIGHT = TRUE_SCREEN_HEIGHT * SCALE_FACTOR;
constexpr int FPS = 60;
constexpr int PIXELS_PER_UNIT = 8;
constexpr int POINTS_SMALL = 100;
constexpr int POINTS_BIG = 200;
constexpr int POINTS_GHOST = 400;
constexpr int HITBOX_SHRINK = 6 * SCALE_FACTOR;
constexpr int ZVAL_TOP = 2;
constexpr int ZVAL_ALMOST_TOP = 1;

constexpr float PLAYER_MOVE_SPEED = 3.0f;
constexpr int PLAYER_ENTRY_COLUMN = 14;
constexpr int PLAYER_ENTRY_ROW = 19;

constexpr float GHOST_MOVE_SPEED = 2.5f;
constexpr float GHOST_MOVE_SPEED_SCARED = 1.5f;
constexpr int GHOST_ENTRY_COLUMN = 13;
constexpr int GHOST_ENTRY_ROW = 13;
constexpr int GHOST_HOUSE_COLUMN = 11;
constexpr int GHOST_HOUSE_ROW = 15;
constexpr int GHOST_RESPAWN_DELAY = 3000;   // ms
constexpr int GHOST_SCARE_TIME = 5000;      // ms
constexpr int GHOST_DEPLOY_INTERVAL = 8000; // ms