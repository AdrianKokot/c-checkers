#include "../headers/board.h"

typedef struct Board
{
  sfRenderWindow *window;
  Player **players;
} Board;

typedef struct BoardPosition
{
  int x;
  int y;
} BoardPosition;