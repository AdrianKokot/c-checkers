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

// TODO found parts of multi beat add as available move to give the player possibility to decide
PawnBeat pawn_checkMoveAvailableness(Pawn *pawn, int x, int y, int xDir, int yDir, int playerPawnId, bool previousToBeat)
{
  PawnBeat move = {-1, -1, (BoardPosition *)malloc(sizeof(BoardPosition) * 0), 0};

  if (x >= 0 && x < pawn->player->board->boardSize && y >= 0 && y < pawn->player->board->boardSize)
  {

    if (pawn->player->board->pawnsOnBoard[x][y] == 0)
    {

      if (previousToBeat == true)
      {
        PawnBeat nextBeat = pawn_checkMoveAvailableness(pawn, x + xDir, y + yDir, xDir, yDir, playerPawnId, false);
        if (nextBeat.x < 0 || nextBeat.pawnsToBeatCount == 0)
        {
          nextBeat = pawn_checkMoveAvailableness(pawn, x - xDir, y + yDir, -xDir, yDir, playerPawnId, false);

          if (nextBeat.x < 0 || nextBeat.pawnsToBeatCount == 0)
          {
            nextBeat = pawn_checkMoveAvailableness(pawn, x + xDir, y - yDir, xDir, -yDir, playerPawnId, false);
          }
        }

        if (nextBeat.pawnsToBeatCount > 0 && nextBeat.x >= 0)
        {
          return nextBeat;
        }
      }

      move.x = x;
      move.y = y;
    }
    else if (previousToBeat == false && pawn->player->board->pawnsOnBoard[x][y] == -1 * playerPawnId)
    {

      BoardPosition beatpos = {x, y};

      move = pawn_checkMoveAvailableness(pawn, x + xDir, y + yDir, xDir, yDir, playerPawnId, true);

      BoardPosition *beatpositions = (BoardPosition *)malloc(sizeof(BoardPosition) * (move.pawnsToBeatCount + 1));

      for (int i = 0; i < move.pawnsToBeatCount; i++)
      {
        beatpositions[i] = move.pawnsToBeat[i];
      }

      beatpositions[move.pawnsToBeatCount++] = beatpos;
      move.pawnsToBeat = beatpositions;
    }
    else if (pawn->player->board->pawnsOnBoard[x][y] == playerPawnId)
    {
      // Same player pawn
      move.x = -2;
      move.y - 2;
    }
  }

  return move;
}

void pawn_generateAvailableMoves(Pawn *pawn)
{
  pawn->availableMovesCount = 0;

  PawnBeat pos;

  int playerId = pawn->player->board->players[0] == pawn->player ? 0 : 1,
      playerPawnsId = playerId == 0 ? 1 : -1;

  if (pawn->pawnType == Queen)
  {
    int x = pawn->position->x, y = pawn->position->y;

    int direction[5] = {-1, 1, 1, -1, -1};

    for (int d = 0; d < 4; d++)
    {
      int i = pawn->position->x + direction[d],
          j = pawn->position->y + direction[d + 1];

      while (i >= 0 && i < pawn->player->board->boardSize && j >= 0 && j < pawn->player->board->boardSize)
      {
        pos = pawn_checkMoveAvailableness(pawn, i, j, direction[d], direction[d + 1], playerPawnsId, false);

        if (pos.x >= 0)
          pawn->availableMoves[pawn->availableMovesCount++] = pos;
        else if (pos.x == -2)
        {
          break;
        }

        if (pos.pawnsToBeatCount > 0)
          break;

        i += direction[d];
        j += direction[d + 1];
      }
    }
  }
  else
  {
    int xAxis[2] = {-1, 1};

    for (int i = 0; i < 2; i++)
    {
      pos = pawn_checkMoveAvailableness(pawn, pawn->position->x + xAxis[i], pawn->position->y + playerPawnsId, xAxis[i], playerPawnsId, playerPawnsId, false);
      if (pos.x >= 0)
        pawn->availableMoves[pawn->availableMovesCount++] = pos;
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
  if (position.x < 0 || position.x >= pawn->player->board->boardSize || position.y < 0 || position.y >= pawn->player->board->boardSize)
    return;

  if (
      (pawn->player->board->players[1]->bIsActive && position.y == 0) || (pawn->player->board->players[0]->bIsActive && position.y == pawn->player->board->boardSize - 1))
  {
    pawn_setType(pawn, Queen);
  }

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

  for (int j = 0; j < pawn->availableMoves[fmIdx].pawnsToBeatCount; j++)
  {
    Pawn *fpawn = pawn_findByPos(pawn->player->board, pawn->availableMoves[fmIdx].pawnsToBeat[j].x, pawn->availableMoves[fmIdx].pawnsToBeat[j].y);
    if (fpawn)
    {
      pawn_remove(fpawn);
    }
  }

  sfVector2f vectorOffset = {
      position.x * pawn->player->board->textureSize + pawn->player->board->boardBorder,
      position.y * pawn->player->board->textureSize + pawn->player->board->boardBorder};

  pawn->position->x = position.x;
  pawn->position->y = position.y;
  sfSprite_setPosition(pawn->sprite, vectorOffset);

  board_calculatePawnsOnBoardArray(pawn->player->board);
}

void pawn_remove(Pawn *pawn)
{
  Pawn *temp = pawn->player->pawns[pawn->player->iPawnCount - 1];
  for (int i = 0; i < pawn->player->iPawnCount; i++)
  {
    if (pawn->player->pawns[i] == pawn)
    {
      pawn->player->pawns[i] = temp;

      free(pawn);
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
}