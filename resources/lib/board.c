#include "../headers/board.h"

Board *board_create(
    sfRenderWindow *window,
    int boardSize,
    int textureSize,
    int boardBorder,
    char boardTileTextures[4][255],
    char playerPawnTextures[4][255])
{
  int intBoardTilesTexturesCount = 4;

  Board *board = malloc(sizeof(Board));

  board->window = window;
  board->boardSize = boardSize;
  board->textureSize = textureSize;
  board->boardBorder = boardBorder;
  board->playerPawnCount = ((boardSize - 2) / 2) * (boardSize / 2);
  board->playerCount = 2;

  sfIntRect intRect = {0, 0, textureSize, textureSize};

  board->tileTextures = malloc(sizeof(sfTexture *) * 4);
  for (int i = 0; i < intBoardTilesTexturesCount; i++)
  {
    board->tileTextures[i] = sfTexture_createFromFile(boardTileTextures[i], &intRect);
  }

  board_createPlayers(board, 4, playerPawnTextures, &intRect);
  board_createBoardSprites(board);

  return board;
}

void board_createBoardSprites(Board *board)
{
  sfSprite *spriteA = createSprite_FromTexture(board->tileTextures[0]),
           *spriteB = createSprite_FromTexture(board->tileTextures[2]);

  board->tileSprites = (sfSprite ***)malloc(board->boardSize * sizeof(sfSprite **));

  for (int i = 0; i < board->boardSize; i++)
  {
    board->tileSprites[i] = (sfSprite **)malloc(board->boardSize * sizeof(sfSprite *));

    for (int j = 0; j < board->boardSize; j++)
    {
      sfVector2f vectorOffset = {
          i * board->textureSize + board->boardBorder,
          j * board->textureSize + board->boardBorder};

      board->tileSprites[i][j] = (i + j) % 2 == 1
                                     ? sfSprite_copy(spriteA)
                                     : sfSprite_copy(spriteB);

      sfSprite_move(board->tileSprites[i][j], vectorOffset);
    }
  }
}

void board_createPlayers(
    Board *board,
    int intPlayerPawnTexturesCount,
    char playerPawnTextures[4][255],
    sfIntRect *intRect)
{
  board->players = malloc(sizeof(Player) * 2);
  for (int i = 0; i < board->playerCount; i++)
  {
    sfTexture **playerTextures = malloc(sizeof(sfTexture *) * intPlayerPawnTexturesCount);

    for (int j = 0; j < intPlayerPawnTexturesCount; j++)
    {
      playerTextures[j] = sfTexture_createFromFile(playerPawnTextures[board->playerCount * i + j], intRect);
    }

    board->players[i] = player_create(board->playerPawnCount, board, playerTextures);
  }
}

void board_drawBoard(Board *board)
{
  draw2dArray(board->window, board->tileSprites, board->boardSize, board->boardSize);
}

void board_drawPawns(Board *board)
{
  for (int i = 0; i < board->playerCount; i++)
  {
    for (int j = 0; j < board->players[i]->iPawnCount; j++)
    {
      sfRenderWindow_drawSprite(board->window, board->players[i]->pawns[j]->sprite, NULL);
    }
  }
}

bool board_checkWinStatus(Board *board)
{
  return false;
}

int board_getWinStatus(Board *board)
{
  return -1;
}

void board_checkPawnSelectionByMouse(Board *board)
{
}
