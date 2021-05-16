#include "./resources/headers/checkers.h"
#include <windows.h>

int main()
{
  // TODO read those variables from config
  const int intBoardSize = 10,
            intTextureSize = 64,
            intBoardBorder = 24,
            intWindowSize = intBoardSize * intTextureSize + 2 * intBoardBorder;

  const char stringBoardTileTexturesPaths[4][255] = {
      "./resources/sprites/tile2.png",
      "./resources/sprites/tile2_marked.png",
      "./resources/sprites/tile1.png",
      "./resources/sprites/tile1_marked.png"};

  const char stringPlayerPawnTexturesPaths[4][255] = {
      "./resources/sprites/pawn1.png",
      "./resources/sprites/pawn1_queen.png",
      "./resources/sprites/pawn2.png",
      "./resources/sprites/pawn2_queen.png"};

  Board *board = board_create(
      engine_createWindow(intWindowSize),
      intBoardSize,
      intTextureSize,
      intBoardBorder,
      stringBoardTileTexturesPaths,
      stringPlayerPawnTexturesPaths);

  engine_attachBackgroundToBoard(board);

  if (!board->window)
    return 1;

  while (sfRenderWindow_isOpen(board->window))
  {
    engine_checkEvents(board);

    sfRenderWindow_clear(board->window, sfBlack);

    if (!engine_checkWinState(board))
    {
      board_draw(board);
    }

    sfRenderWindow_display(board->window);
  }

  board_destroy(board);
  return 0;
}