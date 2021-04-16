#include "../headers/player.h"

Player *player_create(int iPawnCount, Board *board, sfTexture **textures, bool isTopPlayer)
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

  int start = isTopPlayer ? 0 : player->board->boardSize / 2 + 1,
      size = player->board->boardSize / 2 + start,
      pawnIdx = 0;

  for (int i = start; i < size && pawnIdx < player->iPawnCount; i++)
  {
    for (int j = 0; j < player->board->boardSize && pawnIdx < player->iPawnCount; j++)
    {
      if ( (i + j) % 2 == 1)
      {
        sfVector2f vectorOffset = {
            j * board->textureSize + board->boardBorder,
            i * board->textureSize + board->boardBorder};

        sfSprite_move(player->pawns[pawnIdx]->sprite, vectorOffset);
        pawnIdx++;
      }
    }
  }

  return player;
}

void player_makeActive(Player *player)
{
  player->board->players[0]->bIsActive = false;
  player->board->players[1]->bIsActive = false;

  player->bIsActive = true;
}