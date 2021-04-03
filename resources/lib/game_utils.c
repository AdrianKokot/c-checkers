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

int **createPlayerBoard(int size)
{
  int playerRows = (size - 2) / 2;
  int **board = create2dArray(size, size);

  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      board[i][j] = (i + j) % 2 ? (i < playerRows ? 1 : (i >= (size - playerRows) ? -1 : 0)) : 0;
    }
  }

  return board;
}

sfSprite ***createSpriteBoard(const int size, int **intBoard, char texturePaths[2][255], int spriteSize)
{
  sfSprite *spriteA = createSprite(texturePaths[0]),
           *spriteB = createSprite(texturePaths[1]);

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

sfSprite ***createSpritePlayerPawnBoard(const int size, int **intBoard, char texturePaths[2][255], int spriteSize)
{
  sfSprite *spriteA = createSprite(texturePaths[0]),
           *spriteB = createSprite(texturePaths[1]);

  sfSprite **(*spritesBoard) = (sfSprite ***)malloc(2 * sizeof(sfSprite **));
  int playerPawnCount = ((size - 2) / 2) * (size / 2);

  for (int i = 0; i < 2; i++)
  {
    spritesBoard[i] = (sfSprite **)malloc(playerPawnCount * sizeof(sfSprite *));
    for (int j = 0; j < playerPawnCount; j++)
    {
      spritesBoard[i][j] = i == 0 ? sfSprite_copy(spriteA) : sfSprite_copy(spriteB);
    }
  }

  int playerIdx = 0;
  int playerPawnIdx = 0;
  for (int i = 0; i < size; i++)
  {
    if (i == size / 2)
    {
      playerIdx = 1;
      playerPawnIdx = 0;
    }

    for (int j = 0; j < size; j++)
    {
      if (intBoard[i][j] != 0)
      {
        sfVector2f vectorOffset = {j * spriteSize, i * spriteSize};

        sfSprite_move(spritesBoard[playerIdx][playerPawnIdx], vectorOffset);
        playerPawnIdx++;
      }
    }
  }

  return spritesBoard;
}

void draw2dArray(sfRenderWindow *window, sfSprite ***spritesArr, int row, int col)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      sfRenderWindow_drawSprite(window, spritesArr[i][j], NULL);
    }
  }
}

void destorySprite2dArray(sfSprite ***spritesArr, int row, int col)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      sfSprite_destroy(spritesArr[i][j]);
    }
  }
}
