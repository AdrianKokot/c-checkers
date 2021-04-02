#include "../headers/game_window.h"

sfRenderWindow *createGameWindow(int size)
{
  char *windowTitle = "Warcaby";

  sfVideoMode videoMode = {size, size, 64};
  sfRenderWindow *window = sfRenderWindow_create(videoMode, windowTitle, sfClose, NULL);

  return window;
}