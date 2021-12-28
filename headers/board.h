#ifndef BOARD_H
#define BOARD_H

#include "headers/config.h"

// ? Why does this work?  Shouldn't the default constructor be with empty body and empty init list?
// ? ~ Pos p1 {3,3}; // gives -> p1.x = 3, p1.y =3
struct Vector2
{
    int x;
    int y;
    static float sqrDistance(Vector2 v1, Vector2 v2);
};

// topleft cell is determined based on it's topleft. cell(0,0) is a cell that has it's corner
// at position px(0,0). cell(3,2) is a cell whose topleft is at position px(3*8,2*8), and spans
// the area from px(24+8, 16+8), with the right and bottom edge EXCLUDED, belonging to next cell.
class Board
{
  public:
    static constexpr int rows = TRUE_SCREEN_HEIGHT / PIXELS_PER_UNIT;
    static constexpr int cols = TRUE_SCREEN_WIDTH / PIXELS_PER_UNIT;

    // 0 wall, 1 path with small point, 2 path with no point, 3 path with big point
    static char board[rows][cols];

    // returns topleft of grid cell in pixel coordinates (considers SCALE_FACTOR)
    static Vector2 cellToPx(int row, int col);

    // retuns cell coordinates for given pixel coorinates (considers SCALE_FACTOR)
    static Vector2 pxToCell(int screenX, int screenY);

    // return the value of a cell at given CELL position
    static int query(int row, int col);
};

#endif