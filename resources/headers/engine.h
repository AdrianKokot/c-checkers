
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.h>

// TODO add javadoc to engine_createWindow
sfRenderWindow *engine_createWindow(int size);

// TODO add javadoc to engine_createSprite
sfSprite *engine_createSprite(char *texturePath);

// TODO add javadoc to engine_createSpriteFromTexture
sfSprite *engine_createSpriteFromTexture(sfTexture *spriteTexture);

#endif