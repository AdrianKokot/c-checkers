#include "../headers/player.h"

typedef struct Player
{
  bool bIsActive;
  int iPawnCount;
  Pawn **pawns;
  Board *board;
} Player;
