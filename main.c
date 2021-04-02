#include "./resources/headers/game_window.h"
#include "./resources/headers/game_utils.h"

int main()
{
  const int intBoardSize = 8, intTextureSize = 64;
  int **intBoard = createBoard(intBoardSize);

  char stringResourceArr[][255] = {
      "./resources/sprites/board_tiles.pyxel.png",
      ""};

  sfRenderWindow *window = createGameWindow(intBoardSize * intTextureSize);
  sfSprite ***spriteBoard = createSpritesBoard(intBoardSize, intBoard, stringResourceArr[0], intTextureSize, 0, intTextureSize);

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

    // Main Game Loop
    drawBoard(window, spriteBoard, intBoardSize, intTextureSize);

    sfRenderWindow_display(window);
  }

  sfRenderWindow_destroy(window);
  return 0;
}