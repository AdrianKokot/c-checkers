#include "../headers/pawn.h"

Pawn *pawn_create(int iPosX, int iPosY, Player *player)
{
  Pawn *pawn = malloc(sizeof(Pawn));

  pawn->player = player;
  pawn->position = malloc(sizeof(BoardPosition));
  pawn->position->x = iPosX;
  pawn->position->y = iPosY;
  pawn->sprite = sfSprite_create();

  pawn_setType(pawn, Standard);

  return pawn;
}

void pawn_setTexture(Pawn *pawn, const sfTexture *texture)
{
  sfSprite_setTexture(pawn->sprite, texture, sfTrue);
}

void pawn_setType(Pawn *pawn, PawnType type)
{
  pawn->pawnType = type;

  pawn_setTexture(pawn, pawn->player->textures[pawn->pawnType]);
}

BoardPosition *pawn_getAvailableMoves(Pawn *pawn, int *boardPositionArraySize)
{
  // TODO fill pawn_getAvailableMoves method
  return NULL;
}

void pawn_markAvailableMoves(Pawn *pawn)
{
  // TODO add reseting status of tiles
  // TODO add method for marking board tiles
  printf("Selected pawn pos: X: %d Y: %d\n", pawn->position->x, pawn->position->y);
}
