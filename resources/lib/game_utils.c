#include "../headers/game_utils.h"
#include "../headers/lang_utils.h"

sfSprite *createSprite(char *texturePath)
{
  sfTexture *spriteTexture = sfTexture_createFromFile(texturePath, NULL);
  sfSprite *sprite = sfSprite_create();

  sfSprite_setTexture(sprite, spriteTexture, sfTrue);

  return sprite;
}

sfSprite *createSprite_Rect(char *texturePath, int left, int top, int width, int height)
{
  sfIntRect textureRect = {left, top, width, height};
  sfTexture *spriteTexture = sfTexture_createFromFile(texturePath, &textureRect);
  sfSprite *sprite = sfSprite_create();

  sfSprite_setTexture(sprite, spriteTexture, sfTrue);

  return sprite;
}

sfSprite *createSprite_FromTexture(sfTexture *spriteTexture)
{
  sfSprite *sprite = sfSprite_create();
  sfSprite_setTexture(sprite, spriteTexture, sfTrue);

  return sprite;
}

sfSprite *createSprite_FromTextureRect(sfTexture *spriteTexture, int left, int top, int width, int height)
{
  sfIntRect textureRect = {left, top, width, height};

  sfSprite *sprite = sfSprite_create();
  sfSprite_setTexture(sprite, spriteTexture, sfTrue);
  sfSprite_setTextureRect(sprite, textureRect);

  return sprite;
}

int **createBoard(int size)
{
  int **board = create2dArray(size, size);

  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      board[i][j] = (i + j) % 2;
    }
  }

  return board;
}

sfSprite ***createSpritesBoard(const int size, int **intBoard, char *texturePath, int firstSpriteStart, int secondSpriteStart, int spriteSize)
{
  sfSprite *spriteA = createSprite_Rect(texturePath, firstSpriteStart, 0, spriteSize, spriteSize),
           *spriteB = createSprite_Rect(texturePath, secondSpriteStart, 0, spriteSize, spriteSize);

  sfSprite **(*spritesBoard) = (sfSprite ***)malloc(size * sizeof(sfSprite **));

  for (int i = 0; i < size; i++)
  {
    spritesBoard[i] = (sfSprite **)malloc(size * sizeof(sfSprite *));

    for (int j = 0; j < size; j++)
    {
      sfVector2f vectorOffset = {i * spriteSize, j * spriteSize};

      spritesBoard[i][j] = intBoard[i][j] == 1 ? sfSprite_copy(spriteA) : sfSprite_copy(spriteB);
      sfSprite_move(spritesBoard[i][j], vectorOffset);
    }
  }

  return spritesBoard;
}

void drawBoard(sfRenderWindow *window, sfSprite ***spritesArr, int boardSize, int textureSize)
{
  for (int i = 0; i < boardSize; i++)
  {
    for (int j = 0; j < boardSize; j++)
    {
      sfRenderWindow_drawSprite(window, spritesArr[i][j], NULL);
    }
  }
}