#include "../headers/pawn.h"

Pawn *pawn_create(int iPosX, int iPosY, Player *player)
{
  Pawn *pawn = malloc(sizeof(Pawn));

  pawn->player = player;
  pawn->position = malloc(sizeof(BoardPosition));
  pawn->position->x = iPosX;
  pawn->position->y = iPosY;
  pawn->sprite = sfSprite_create();
  pawn->availableMoves = (PawnBeat *)malloc(sizeof(PawnBeat) * 255);
  pawn->availableMovesCount = 0;

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

PawnBeat pawn_checkMoveAvailableness(Pawn *pawn, int x, int y, int playerPawnId, bool previousToBeat)
{
  PawnBeat move = {-1, -1, (BoardPosition *)malloc(sizeof(BoardPosition) * 0), 0};

  if (x >= 0 && x < pawn->player->board->boardSize && y >= 0 && y < pawn->player->board->boardSize)
  {
    printf("\nCHECKING POS: %d %d val on board: %d", x, y, pawn->player->board->pawnsOnBoard[x][y]);

    if (pawn->player->board->pawnsOnBoard[x][y] == 0)
    {
      // TODO checking multi beat
      // if (previousToBeat == true)
      // {
      //   position = pawn_checkMoveAvailableness(pawn, pawn->position->x > x ? x - 1 : x + 1, y + playerPawnId, playerPawnId, false);

      //   if (position.x != -1 && position.x != pawn->position->x > x ? x - 1 : x + 1)
      //   {
      //     return position;
      //   }
      // }

      move.x = x;
      move.y = y;
    }
    else if (previousToBeat == false && pawn->player->board->pawnsOnBoard[x][y] == -1 * playerPawnId)
    {
      printf("\nCALCULATING BEAT: %d %d\n", x, y);

      BoardPosition beatpos = {x, y};

      move = pawn_checkMoveAvailableness(pawn, pawn->position->x > x ? x - 1 : x + 1, y + playerPawnId, playerPawnId, true);

      BoardPosition *beatpositions = (BoardPosition *)malloc(sizeof(BoardPosition) * move.pawnsToBeatCount + 1);
      for(int i = 0; i < move.pawnsToBeatCount; i++) {
        beatpositions[i] = move.pawnsToBeat[i];
      }
      beatpositions[move.pawnsToBeatCount++] = beatpos;
      move.pawnsToBeat = beatpositions;

    }
  }

  return move;
}

void pawn_generateAvailableMoves(Pawn *pawn)
{
  PawnBeat pos;

  int playerId = pawn->player->board->players[0] == pawn->player ? 0 : 1,
      playerPawnsId = playerId == 0 ? 1 : -1;

  if (pawn->pawnType == Queen)
  {
    // TODO queen available moves checking
    // for (int i = pawn->position->x; i < pawn->player->board->boardBorder; i += 2)
    // {
    //   for (int j = pawn->position->y; j < pawn->player->board->boardBorder; j += 2)
    //   {
    //     pos = pawn_checkMoveAvailableness(pawn, i, j, playerPawnsId, false);
    //     if (pos.x != -1)
    //     {
    //       availableMoves[filledAvailableMovesCount++] = pos;
    //     }
    //   }
    //   for (int j = pawn->position->y; j >= 0; j -= 2)
    //   {
    //     pos = pawn_checkMoveAvailableness(pawn, i, j, playerPawnsId, false);
    //     if (pos.x != -1)
    //     {
    //       availableMoves[filledAvailableMovesCount++] = pos;
    //     }
    //   }
    // }

    // for (int i = pawn->position->x; i >= 0; i -= 2)
    // {
    //   for (int j = pawn->position->y; j < pawn->player->board->boardBorder; j += 2)
    //   {
    //     pos = pawn_checkMoveAvailableness(pawn, i, j, playerPawnsId, false);
    //     if (pos.x != -1)
    //     {
    //       availableMoves[filledAvailableMovesCount++] = pos;
    //     }
    //   }
    //   for (int j = pawn->position->y; j >= 0; j -= 2)
    //   {
    //     pos = pawn_checkMoveAvailableness(pawn, i, j, playerPawnsId, false);
    //     if (pos.x != -1)
    //     {
    //       availableMoves[filledAvailableMovesCount++] = pos;
    //     }
    //   }
    // }
  }
  else
  {
    int xAxis[2] = {-1, 1};

    for (int i = 0; i < 2; i++)
    {
      pos = pawn_checkMoveAvailableness(pawn, pawn->position->x + xAxis[i], pawn->position->y + playerPawnsId, playerPawnsId, false);
      if (pos.x != -1)
      {
        pawn->availableMoves[pawn->availableMovesCount++] = pos;
      }
    }
  }
}

void pawn_markAvailableMoves(Pawn *pawn)
{
  board_resetTilesTextures(pawn->player->board);
  pawn_generateAvailableMoves(pawn);

  for (int i = 0; i < pawn->availableMovesCount; i++)
  {
    board_markTileTexture(pawn->player->board, pawn->availableMoves[i].x, pawn->availableMoves[i].y);
  }
}

void pawn_move(Pawn *pawn, BoardPosition position)
{
  if (
      (pawn->player->board->players[1]->bIsActive && position.y == 0) || (pawn->player->board->players[0]->bIsActive && position.y == pawn->player->board->boardSize - 1))
  {
    pawn_setType(pawn, Queen);
  }

  printf("\nPAWN POSITION: %d %d\nMOVE TO: %d %d\n", pawn->position->x, pawn->position->y, position.x, position.y);

  // Found move Index
  int fmIdx = -1;

  for (int i = 0; i < pawn->availableMovesCount; i++)
  {
    if (pawn->availableMoves[i].x == position.x && pawn->availableMoves[i].y == position.y)
    {
      fmIdx = i;
      break;
    }
  }

  if (fmIdx == -1)
    return;

  printf("FOUND MOVE: %d %d\n", pawn->availableMoves[fmIdx].x, pawn->availableMoves[fmIdx].y);

  for (int j = 0; j < pawn->availableMoves[fmIdx].pawnsToBeatCount; j++)
  {
    printf("REMOVED PAWN ON: %d %d\n", pawn->availableMoves[fmIdx].pawnsToBeat[j].x, pawn->availableMoves[fmIdx].pawnsToBeat[j].y);
    pawn_remove(pawn_findByPos(pawn->player->board, pawn->availableMoves[fmIdx].pawnsToBeat[j].x, pawn->availableMoves[fmIdx].pawnsToBeat[j].y));
  }

  pawn->availableMovesCount = 0;

  sfVector2f vectorOffset = {
      position.x * pawn->player->board->textureSize + pawn->player->board->boardBorder,
      position.y * pawn->player->board->textureSize + pawn->player->board->boardBorder};

  pawn->player->board->pawnsOnBoard[pawn->position->x][pawn->position->y] = 0;
  pawn->player->board->pawnsOnBoard[position.x][position.y] = pawn->player->board->players[0]->bIsActive ? 1 : -1;

  pawn->position->x = position.x;
  pawn->position->y = position.y;
  sfSprite_setPosition(pawn->sprite, vectorOffset);
}

void pawn_remove(Pawn *pawn)
{
  Pawn *temp = pawn->player->pawns[pawn->player->iPawnCount - 1];
  for (int i = 0; i < pawn->player->iPawnCount; i++)
  {
    if (pawn->player->pawns[i] == pawn)
    {
      pawn->player->pawns[i] = temp;
      pawn->player->pawns[pawn->player->iPawnCount - 1] = pawn;
      pawn->player->board->pawnsOnBoard[pawn->position->x][pawn->position->y] = 0;
      pawn->position->x = -1;
      pawn->position->y = -1;
      sfSprite_destroy(pawn->sprite);
      pawn->player->iPawnCount--;
      return;
    }
  }
}

Pawn *pawn_findByPos(Board *board, int x, int y)
{
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < board->players[i]->iPawnCount; j++)
    {
      if (board->players[i]->pawns[j]->position->x == x && board->players[i]->pawns[j]->position->y == y)
      {
        return board->players[i]->pawns[j];
      }
    }
  }
  return board->players[0]->pawns[0];
}