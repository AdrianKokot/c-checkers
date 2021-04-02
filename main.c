#include "./resources/headers/game_window.h"
#include "./resources/headers/game_utils.h"
#include "./resources/headers/lang_utils.h"

int main()
{
  const int intBoardSize = 8,
            intTextureSize = 64,
            intPlayerCount = 2,
            intPlayerPawnCount = ((intBoardSize - 2) / 2) * (intBoardSize / 2);

  int **intBoard = createBoard(intBoardSize),
      **intPlayerBoard = createPlayerBoard(intBoardSize);

  char stringResourceArr[][255] = {
      "./resources/sprites/board_tiles.pyxel.png",
      "./resources/sprites/player_pawns.pyxel.png"};

  sfRenderWindow *window = createGameWindow(intBoardSize * intTextureSize);
  sfSprite ***spriteBoard = createSpriteBoard(intBoardSize, intBoard, stringResourceArr[0], intTextureSize, 0, intTextureSize);
  sfSprite ***spritePlayerPawnArr = createSpritePlayerPawnBoard(intBoardSize, intPlayerBoard, stringResourceArr[1], intTextureSize, 0, intTextureSize);

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
    draw2dArray(window, spriteBoard, intBoardSize, intBoardSize);
    draw2dArray(window, spritePlayerPawnArr, intPlayerCount, intPlayerPawnCount);

    sfRenderWindow_display(window);
  }

  sfRenderWindow_destroy(window);
  destory2dArray(intBoard);
  destorySpriteBoard(spriteBoard, intBoardSize);
  return 0;
}