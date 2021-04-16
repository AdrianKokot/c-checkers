
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.h>

sfRenderWindow *engine_createWindow(int size);

sfSprite *engine_createSprite(char *texturePath);

sfSprite *engine_createSpriteFromTexture(sfTexture *spriteTexture);

#endif