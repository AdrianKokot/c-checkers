#include "../headers/board.h"

Board *board_create(
    sfRenderWindow *window,
    int boardSize,
    int textureSize,
    int boardBorder,
    const char boardTileTextures[4][255],
    const char playerPawnTextures[4][255])
{
  Board *board = malloc(sizeof(Board));

  // Init values
  int intBoardTilesTexturesCount = 4;
  board->window = window;
  board->boardSize = boardSize;
  board->textureSize = textureSize;
  board->boardBorder = boardBorder;
  board->playerPawnCount = ((boardSize - 2) / 2) * (boardSize / 2);
  board->playerCount = 2;

  // End Text creation
  board->endText = sfText_create();

  sfText_setFont(board->endText, sfFont_createFromFile("./resources/fonts/arial.ttf"));
  sfText_setCharacterSize(board->endText, 50);
  sfText_setColor(board->endText, sfWhite);

  // Pawns on board generation
  board->pawnsOnBoard = (int **)malloc(sizeof(int *) * boardSize);
  for (int i = 0; i < boardSize; i++)
  {
    board->pawnsOnBoard[i] = (int *)malloc(sizeof(int) * boardSize);
  }

  // Setting tile's textures
  sfIntRect intRect = {0, 0, textureSize, textureSize};

  board->tileTextures = malloc(sizeof(sfTexture *) * 4);
  for (int i = 0; i < intBoardTilesTexturesCount; i++)
  {
    board->tileTextures[i] = sfTexture_createFromFile(boardTileTextures[i], &intRect);
  }

  board_createPlayers(board, 2, playerPawnTextures, &intRect);
  board_createBoardSprites(board);

  player_makeActive(board->players[1]);

  board_calculatePawnsOnBoardArray(board);

  return board;
}

void board_createBoardSprites(Board *board)
{
  sfSprite *spriteA = engine_createSpriteFromTexture(board->tileTextures[0]),
           *spriteB = engine_createSpriteFromTexture(board->tileTextures[2]);

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
    const char playerPawnTextures[4][255],
    sfIntRect *intRect)
{
  board->players = malloc(sizeof(Player) * 2);
  for (int i = 0; i < board->playerCount; i++)
  {
    sfTexture **playerTextures = (sfTexture **)malloc(sizeof(sfTexture *) * intPlayerPawnTexturesCount);

    for (int j = 0; j < intPlayerPawnTexturesCount; j++)
    {
      playerTextures[j] = sfTexture_createFromFile(playerPawnTextures[board->playerCount * i + j], intRect);
    }

    board->players[i] = player_create(board->playerPawnCount, board, playerTextures, i == 0 ? true : false);
  }
}

void board_destroy(Board *board)
{
  sfRenderWindow_destroy(board->window);

  for (int i = 0; i < board->boardSize; i++)
  {
    for (int j = 0; j < board->boardSize; j++)
    {
      sfSprite_destroy(board->tileSprites[i][j]);
    }
  }

  for (int i = 0; i < board->playerCount; i++)
  {
    for (int j = 0; j < board->players[i]->iPawnCount; j++)
    {
      sfSprite_destroy(board->players[i]->pawns[j]->sprite);
      free(board->players[i]->pawns[j]);
    }

    for (int j = 0; j < 2; j++)
    {
      sfTexture_destroy(board->players[i]->textures[j]);
    }

    free(board->players[i]);
  }
}

void board_draw(Board *board)
{
  sfRenderWindow_drawSprite(board->window, board->spriteBackground, NULL);
  sfRenderWindow_drawRectangleShape(board->window, board->shapeBackground, NULL);

  board_drawBoard(board);
  board_drawPawns(board);
}

void board_drawBoard(Board *board)
{
  for (int i = 0; i < board->boardSize; i++)
  {
    for (int j = 0; j < board->boardSize; j++)
    {
      sfRenderWindow_drawSprite(board->window, board->tileSprites[i][j], NULL);
    }
  }
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
  return board->players[0]->iPawnCount == 0 || board->players[1]->iPawnCount == 0;
}

int board_getWinStatus(Board *board)
{
  return board->players[0]->iPawnCount == 0 ? 1 : 0;
}

void board_checkPawnSelectionByMouse(Board *board, int mousePosX, int mousePosY)
{
  if (mousePosX > board->boardBorder && mousePosY > board->boardBorder)
  {
    BoardPosition pos = {(mousePosX - board->boardBorder) / board->textureSize, (mousePosY - board->boardBorder) / board->textureSize};

    int idx = board->players[0]->bIsActive ? 0 : 1;

    for (int i = 0; i < board->players[idx]->iPawnCount; i++)
    {
      if (board->players[idx]->pawns[i]->position->x == pos.x && board->players[idx]->pawns[i]->position->y == pos.y)
      {
        board->players[idx]->selectedPawn = board->players[idx]->pawns[i];
        pawn_markAvailableMoves(board->players[idx]->selectedPawn);
        return;
      }
    }
  }
}

void board_checkTileSelectionByMouse(Board *board, int mousePosX, int mousePosY)
{
  if (mousePosX > board->boardBorder && mousePosY > board->boardBorder)
  {
    BoardPosition pos = {(mousePosX - board->boardBorder) / board->textureSize, (mousePosY - board->boardBorder) / board->textureSize};

    int idx = board->players[0]->bIsActive ? 0 : 1;

    if (sfSprite_getTexture(board->tileSprites[pos.x][pos.y]) == board->tileTextures[(pos.x + pos.y) % 2 == 1 ? 1 : 3])
    {
      pawn_move(board->players[idx]->selectedPawn, pos);
      board_resetTilesTextures(board);
      player_makeActive(board->players[idx == 0 ? 1 : 0]);
    }
  }
}

void board_resetTilesTextures(Board *board)
{
  for (int i = 0; i < board->boardSize; i++)
  {
    for (int j = 0; j < board->boardSize; j++)
    {
      sfSprite_setTexture(board->tileSprites[i][j], board->tileTextures[(i + j) % 2 == 1 ? 0 : 2], sfFalse);
    }
  }
}

void board_markTileTexture(Board *board, int x, int y)
{
  sfSprite_setTexture(board->tileSprites[x][y], board->tileTextures[(x + y) % 2 == 1 ? 1 : 3], sfFalse);
}

void board_calculatePawnsOnBoardArray(Board *board)
{
  for (int i = 0; i < board->boardSize; i++)
    for (int j = 0; j < board->boardSize; j++)
      board->pawnsOnBoard[i][j] = 0;

  for (int x = 0; x < board->playerCount; x++)
  {
    for (int i = 0; i < board->players[x]->iPawnCount; i++)
    {
      int pX = board->players[x]->pawns[i]->position->x,
          pY = board->players[x]->pawns[i]->position->y;

      if (pX < 0 || pX >= board->boardSize || pY < 0 || pY >= board->boardSize)
        continue;

      board->pawnsOnBoard[pX][pY] = x == 0 ? 1 : -1;

      // board->players[x]->pawns[i]->availableMoves = (PawnBeat *)malloc(sizeof(PawnBeat) * 255);
      board->players[x]->pawns[i]->availableMovesCount = 0;
    }
  }
}