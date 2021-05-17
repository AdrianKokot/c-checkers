#include "../headers/engine.h"

sfRenderWindow *engine_createWindow(int size)
{
  char *windowTitle = "Warcaby";

  sfVideoMode videoMode = {size, size, 64};
  sfRenderWindow *window = sfRenderWindow_create(videoMode, windowTitle, sfClose, NULL);

  return window;
}

sfSprite *engine_createSprite(char *texturePath)
{
  sfTexture *spriteTexture = sfTexture_createFromFile(texturePath, NULL);
  sfSprite *sprite = sfSprite_create();

  sfSprite_setTexture(sprite, spriteTexture, sfTrue);

  return sprite;
}

sfSprite *engine_createSpriteFromTexture(sfTexture *spriteTexture)
{
  sfSprite *sprite = sfSprite_create();
  sfSprite_setTexture(sprite, spriteTexture, sfTrue);

  return sprite;
}

void engine_checkEvents(Board *board)
{
  sfEvent event;
  while (sfRenderWindow_pollEvent(board->window, &event))
  {
    if (event.type == sfEvtClosed)
    {
      sfRenderWindow_close(board->window);
    }
    if (event.type == sfEvtMouseButtonPressed)
    {
      board_checkPawnSelectionByMouse(board, event.mouseButton.x, event.mouseButton.y);
      board_checkTileSelectionByMouse(board, event.mouseButton.x, event.mouseButton.y);
    }
  }
}

bool engine_checkWinState(Board *board)
{
  if (board_checkWinStatus(board))
  {
    int wonPlayerIndex = board_getWinStatus(board);

    sfText_setString(board->endText, wonPlayerIndex == 0 ? "Player 1 won!" : "Player 2 won!");

    sfFloatRect textRect = sfText_getLocalBounds(board->endText);
    sfVector2f textpos = {textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f};
    float screensize = (board->boardSize * board->textureSize + board->boardBorder * 2) / 2.0f;
    sfVector2f scrpos = {screensize, screensize};

    sfText_setOrigin(board->endText, textpos);
    sfText_setPosition(board->endText, scrpos);

    sfRenderWindow_drawText(board->window, board->endText, NULL);

    return true;
  }
  return false;
}

void engine_attachBackgroundToBoard(Board *board)
{
  int intWindowSize = board->boardSize * board->textureSize + 2 * board->boardBorder;

  sfColor sfColorBoardBackground = sfColor_fromRGB(78, 52, 46);
  sfSprite *spriteBoardBackground = engine_createSprite("./resources/sprites/board_background.jpg");

  sfVector2f shapeBoardBorderSize = {intWindowSize - 32, intWindowSize - 32};
  sfVector2f shapeBoardBorderPosition = {16, 16};
  sfRectangleShape *shapeBoardBorder = sfRectangleShape_create();

  sfRectangleShape_setFillColor(shapeBoardBorder, sfColorBoardBackground);
  sfRectangleShape_setSize(shapeBoardBorder, shapeBoardBorderSize);
  sfRectangleShape_setPosition(shapeBoardBorder, shapeBoardBorderPosition);

  board->spriteBackground = spriteBoardBackground;
  board->shapeBackground = shapeBoardBorder;
}

int *engine_readConfig()
{
  int configLines = 3;
  FILE *confInput = fopen("./game.ini", "r");
  char temp[255];

  if (confInput == NULL)
  {
    printf("game.ini not found.");
    exit(0);
  }

  int *result = malloc(sizeof(int) * 3);

  for (int i = 0; i < configLines && !feof(confInput); i++)
  {
    fscanf(confInput, "%255[^=]= %d\n", temp, &result[i]);
  }

  fclose(confInput);

  return result;
}