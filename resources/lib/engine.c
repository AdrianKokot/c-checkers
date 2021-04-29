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
    }
  }
}