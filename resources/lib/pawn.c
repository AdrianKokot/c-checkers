#include "../headers/pawn.h"

typedef struct Pawn
{
  Player *player;
  BoardPosition *position;
  PawnType pawnType;
  sfSprite *sprite;
} Pawn;
