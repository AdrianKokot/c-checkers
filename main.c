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

  char stringBoardResourceArr[2][255] = {
      "./resources/sprites/tile2.png",
      "./resources/sprites/tile1.png"};

  char stringPawnsResourceArr[2][255] = {
      "./resources/sprites/pawn1.png",
      "./resources/sprites/pawn2.png"};

  sfRenderWindow *window = createGameWindow(intBoardSize * intTextureSize);
  sfSprite ***spriteBoardArr = createSpriteBoard(intBoardSize, intBoard, stringBoardResourceArr, intTextureSize);
  sfSprite ***spritePawnArr = createSpritePlayerPawnBoard(intBoardSize, intPlayerBoard, stringPawnsResourceArr, intTextureSize);

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