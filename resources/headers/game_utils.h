
#ifndef GAME_UTILS_H
#define GAME_UTILS_H
#include <SFML/Graphics.h>

sfSprite *createSprite(char *texturePath);
sfSprite *createSprite_Rect(char *texturePath, int left, int top, int width, int height);
sfSprite *createSprite_FromTexture(sfTexture *spriteTexture);
sfSprite *createSprite_FromTextureRect(sfTexture *spriteTexture, int left, int top, int width, int height);
int **createBoard(int size);
void destory2dArray(int **arr);

void drawBoard(sfRenderWindow *window, sfSprite ***spritesArr, int boardSize, int textureSize);
sfSprite ***createSpritesBoard(const int size, int **intBoard, char *texturePath, int firstSpriteStart, int secondSpriteStart, int spriteSize);

#endif