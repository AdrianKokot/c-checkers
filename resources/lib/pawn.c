#include "../headers/pawn.h"

Pawn pawn_create(int iPosX, int iPosY, Player *player)
{
  BoardPosition position = {iPosX, iPosY};

  sfSprite *pawnSprite = sfSprite_create();

  Pawn pawn = {player, &position, Standard, pawnSprite};

  pawn_setTexture(&pawn, pawn.player->textures[pawn.pawnType]);

  return pawn;
}

void pawn_setTexture(Pawn *pawn, const sfTexture *texture)
{
  sfSprite_setTexture(pawn->sprite, texture, sfTrue);
}

void pawn_changeType(Pawn *pawn, PawnType type)
{
  pawn->pawnType = pawn->pawnType == Standard ? Standard : Queen;

  pawn_setTexture(pawn, pawn->player->textures[pawn->pawnType]);
}

BoardPosition *pawn_getAvailableMoves(Pawn *pawn, int *boardPositionArraySize)
{
  return NULL;
}

void pawn_markAvailableMoves(Pawn *pawn)
{
}
