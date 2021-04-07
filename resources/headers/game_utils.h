
#ifndef GAME_UTILS_H
#define GAME_UTILS_H
#include <SFML/Graphics.h>

sfSprite *createSprite(char *texturePath);
sfSprite *createSprite_Rect(char *texturePath, int left, int top, int width, int height);
sfSprite *createSprite_FromTexture(sfTexture *spriteTexture);
sfSprite *createSprite_FromTextureRect(sfTexture *spriteTexture, int left, int top, int width, int height);
int **createBoard(int size);
int **createPlayerBoard(int size);
void destory2dArray(int **arr);

sfSprite ***createSpriteBoard(const int size, int **intBoard, char texturePaths[2][255], int spriteSize, int boardBorder);
sfSprite ***createSpritePlayerPawnBoard(const int size, int **intBoard, char texturePaths[2][255], int spriteSize, int boardBorder);
void destorySprite2dArray(sfSprite ***spritesArr, int row, int col);
void draw2dArray(sfRenderWindow *window, sfSprite ***spritesArr, int row, int col);

#endif