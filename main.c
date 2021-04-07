#include "./resources/headers/game_window.h"
#include "./resources/headers/game_utils.h"
#include "./resources/headers/lang_utils.h"

int main()
{
  const int intBoardSize = 10,
            intTextureSize = 64,
            intPlayerCount = 2,
            intBoardBorder = 24,
            intPlayerPawnCount = ((intBoardSize - 2) / 2) * (intBoardSize / 2),
            intWindowSize = intBoardSize * intTextureSize + 2 * intBoardBorder;

  int **intBoard = createBoard(intBoardSize),
      **intPlayerBoard = createPlayerBoard(intBoardSize);

  char stringBoardResourceArr[2][255] = {
      "./resources/sprites/tile2.png",
      "./resources/sprites/tile1.png"};

  char stringPawnsResourceArr[2][255] = {
      "./resources/sprites/pawn1.png",
      "./resources/sprites/pawn2.png"};

  sfRenderWindow *window = createGameWindow(intWindowSize);
  sfSprite ***spriteBoardArr = createSpriteBoard(intBoardSize, intBoard, stringBoardResourceArr, intTextureSize, intBoardBorder);
  sfSprite ***spritePawnArr = createSpritePlayerPawnBoard(intBoardSize, intPlayerBoard, stringPawnsResourceArr, intTextureSize, intBoardBorder);

  // TESTOWY BACKGROUND
  sfColor sfColorBoardBackground = sfColor_fromRGB(78, 52, 46);
  sfSprite *spriteBoardBackground = createSprite("./resources/sprites/board_background.jpg");

  sfVector2f shapeBoardBorderSize = {intWindowSize - 32, intWindowSize - 32};
  sfVector2f shapeBoardBorderPosition = {16, 16};
  sfRectangleShape *shapeBoardBorder = sfRectangleShape_create();

  sfRectangleShape_setFillColor(shapeBoardBorder, sfColorBoardBackground);
  sfRectangleShape_setSize(shapeBoardBorder, shapeBoardBorderSize);
  sfRectangleShape_setPosition(shapeBoardBorder, shapeBoardBorderPosition);
  // sfSprite *spriteBoardBackground = sfSprite_create();
  // sfSprite_setColor(spriteBoardBackground, sfColorBoardBackground);

  // sfIntRect sfIntRectBackgroundSize = {0, 0, intBoardSize * intTextureSize + 2 * intBoardBorder};
  // sfSprite_setTextureRect(spriteBoardBackground, sfIntRectBackgroundSize);

  // KONIEC TESTU

  sfEvent event;
  if (!window)
    return 1;

  while (sfRenderWindow_isOpen(window))
  {
    while (sfRenderWindow_pollEvent(window, &event))
    {
      if (event.type == sfEvtClosed)
      {
        sfRenderWindow_close(window);
      }
    }

    sfRenderWindow_clear(window, sfBlack);

    // RENDER TEST BACKGROUND
    sfRenderWindow_drawSprite(window, spriteBoardBackground, NULL);
    sfRenderWindow_drawRectangleShape(window, shapeBoardBorder, NULL);
    // END RENDER TEST BACKGROUND

    // Main Game Loop
    draw2dArray(window, spriteBoardArr, intBoardSize, intBoardSize);
    draw2dArray(window, spritePawnArr, intPlayerCount, intPlayerPawnCount);

    sfRenderWindow_display(window);
  }

  sfRenderWindow_destroy(window);
  destory2dArray(intBoard);
  destorySprite2dArray(spriteBoardArr, intBoardSize, intBoardSize);
  destorySprite2dArray(spritePawnArr, intPlayerCount, intPlayerPawnCount);
  return 0;
}