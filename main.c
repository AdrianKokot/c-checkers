#include "./resources/headers/checkers.h"

int main()
{

  const int intBoardSize = 10,
            intTextureSize = 64,
            intBoardBorder = 24,
            intWindowSize = intBoardSize * intTextureSize + 2 * intBoardBorder;

  const char stringBoardTileTexturesPaths[4][255] = {
      "./resources/sprites/tile2.png",
      "./resources/sprites/tile2.png",
      "./resources/sprites/tile1.png",
      "./resources/sprites/tile1.png"};

  const char stringPlayerPawnTexturesPaths[4][255] = {
      "./resources/sprites/pawn1.png",
      "./resources/sprites/pawn1.png",
      "./resources/sprites/pawn2.png",
      "./resources/sprites/pawn2.png"};

  Board *board = board_create(
      createGameWindow(intWindowSize),
      intBoardSize,
      intTextureSize,
      intBoardBorder,
      stringBoardTileTexturesPaths,
      stringPlayerPawnTexturesPaths);


  // TESTOWY BACKGROUND
  sfColor sfColorBoardBackground = sfColor_fromRGB(78, 52, 46);
  sfSprite *spriteBoardBackground = createSprite("./resources/sprites/board_background.jpg");

  sfVector2f shapeBoardBorderSize = {intWindowSize - 32, intWindowSize - 32};
  sfVector2f shapeBoardBorderPosition = {16, 16};
  sfRectangleShape *shapeBoardBorder = sfRectangleShape_create();

  sfRectangleShape_setFillColor(shapeBoardBorder, sfColorBoardBackground);
  sfRectangleShape_setSize(shapeBoardBorder, shapeBoardBorderSize);
  sfRectangleShape_setPosition(shapeBoardBorder, shapeBoardBorderPosition);

  // KONIEC TESTU

  sfEvent event;
  if (!board->window)
    return 1;

  while (sfRenderWindow_isOpen(board->window))
  {
    while (sfRenderWindow_pollEvent(board->window, &event))
    {
      if (event.type == sfEvtClosed)
      {
        sfRenderWindow_close(board->window);
      }
    }

    sfRenderWindow_clear(board->window, sfBlack);

    // RENDER TEST BACKGROUND
    sfRenderWindow_drawSprite(board->window, spriteBoardBackground, NULL);
    sfRenderWindow_drawRectangleShape(board->window, shapeBoardBorder, NULL);
    // END RENDER TEST BACKGROUND

    board_draw(board);

    sfRenderWindow_display(board->window);
  }

  board_destroy(board);
  return 0;
}