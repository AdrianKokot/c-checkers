#include "../headers/player.h"

Player *player_create(int iPawnCount, Board *board, sfTexture **textures)
{
  Player *player = malloc(sizeof(Player));

  player->bIsActive = false;
  player->iPawnCount = iPawnCount;
  player->textures = textures;
  player->board = board;

  player->pawns = malloc(sizeof(Pawn) * iPawnCount);

  for (int i = 0; i < iPawnCount; i++)
  {
    player->pawns[i] = pawn_create(0, 0, player);
  }

  return player;
}

void player_makeActive(Player *player) {
  player->board->players[0]->bIsActive = false;
  player->board->players[1]->bIsActive = false;

  player->bIsActive = true;
}