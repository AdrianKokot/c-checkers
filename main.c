#include "./resources/headers/checkers.h"

int main()
{
  char stringBoardTileTexturesPaths[4][255] = {
      "./resources/sprites/tile2.png",
      "./resources/sprites/tile2_marked.png",
      "./resources/sprites/tile1.png",
      "./resources/sprites/tile1_marked.png"};

  char stringPlayerPawnTexturesPaths[4][255] = {
      "./resources/sprites/pawn1.png",
      "./resources/sprites/pawn1_queen.png",
      "./resources/sprites/pawn2.png",
      "./resources/sprites/pawn2_queen.png"};

  int *config = engine_readConfig();

  const int intWindowSize = (config[0]) * (config[1]) + 2 * (config[2]);

  Board *board = board_create(
      engine_createWindow(intWindowSize),
      config[0],
      config[1],
      config[2],
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