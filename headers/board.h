#ifndef BOARD_H
#define BOARD_H

#include "headers/config.h"

// ? Why does this work?  Shouldn't the default constructor be with empty body and empty init list?
// ? ~ Pos p1 {3,3}; // gives -> p1.x = 3, p1.y =3
struct Position
{
    int x;
    int y;
};

// topleft cell is determined based on it's topleft. cell(0,0) is a cell that has it's corner
// at position px(0,0). cell(3,2) is a cell whose topleft is at position px(3*8,2*8), and spans
// the area from px(24+8, 16+8), with the right and bottom edge EXCLUDED, belonging to next cell.
class Board
{
  private:
    // 0 wall, 1 path
    static char board[TRUE_SCREEN_HEIGHT / PIXELS_PER_UNIT][TRUE_SCREEN_WIDTH / PIXELS_PER_UNIT];

  public:
    // returns topleft of grid cell in pixel coordinates
    static Position cellToPx(int cellX, int cellY);

    // retuns cell coordinates for given pixel coorinates
    static Position pxToCell(int screenX, int screenY);

    // return the value of a cell at given CELL position
    static int query(Position p);
};

#endif