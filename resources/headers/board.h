#ifndef BOARD_H
#define BOARD_H

#include "./checkers.h"

/**
 * @brief Position on the board
 *
 * @param x position on X axis
 * @param y position on Y axis
 */
struct BoardPosition
{
  int x;
  int y;
};

/**
 * @brief Board representation
 *
 * @param window CSFML window struct pointer
 * @param playerPawnCount count of pawns that every player has
 * @param playerCount count of players
 * @param boardSize size of board (number of tiles on every axis)
 * @param textureSize size of texture in pixels
 * @param boardBorder size of border from window to board
 * @param pawnsOnBoard array of pawn positions on board
 * @param players array of pointers to players
 * @param tileTextures textures of tiles
 * @param tileSprites sprites of tiles
 * @param font pointer to font
 * @param spriteBackground board background sprite
 * @param shapeBackground board background shape
 */
struct Board
{
  sfRenderWindow *window;
  int playerPawnCount;
  int playerCount;
  int boardSize;
  int textureSize;
  int boardBorder;
  int **pawnsOnBoard;
  Player **players;
  sfTexture **tileTextures;
  sfSprite ***tileSprites;
  sfFont *font;
  sfSprite *spriteBackground;
  sfRectangleShape *shapeBackground;
};

/**
 * @brief Board constructor.
 *
 * @param window sfRenderWindow instance
 * @param boardSize number of rows and columns of board
 * @param textureSize size of texture in pixels
 * @param boardBorder size of border in pixels
 *                    (space between window and position that board will be drawn)
 * @param boardTileTextures 2d array of paths to tiles and marked tiles textures
 * @param playerPawnTextures 2d array of paths to each player standard and queen pawns textures
 * @return created Board
 */
Board *board_create(
    sfRenderWindow *window,
    int boardSize,
    int textureSize,
    int boardBorder,
    const char boardTileTextures[4][255],
    const char playerPawnTextures[4][255]);

/**
 * @brief Create players for board
 *
 * @param board board that players will be assigned to
 * @param intPlayerPawnTexturesCount number of pawn textures for each player
 * @param playerPawnTextures 2d array of paths to each player standard and queen pawns textures
 * @param intRect sfIntRect for texture
 * @return void
 */
void board_createPlayers(
    Board *board,
    int intPlayerPawnTexturesCount,
    const char playerPawnTextures[4][255],
    sfIntRect *intRect);

/**
 * @brief Create sprites for board tiles
 *
 * @param board board
 * @return void
 */
void board_createBoardSprites(Board *board);

/**
 * @brief Draw board tiles and player pawns on sfRenderWindow
 *
 * @param board board
 * @return void
 */
void board_draw(Board *board);

/**
 * @brief Draw board tiles on sfRenderWindow
 *
 * @param board board
 * @return void
 */
void board_drawBoard(Board *board);

/**
 * @brief Draw player pawns on sfRenderWindow
 *
 * @param board board
 * @return void
 */
void board_drawPawns(Board *board);

/**
 * @brief Destroy memory allocation for all items in board. Including window, players, pawns
 *
 * @param board board
 * @return void
 */
void board_destroy(Board *board);

/**
 * @brief Check if game has ended
 *
 * @param board board
 * @return true in case any player has won, false otherwise
 */
bool board_checkWinStatus(Board *board);

/**
 * @brief Gets index of player that won
 *
 * @param board board
 * @return index of player that won, -1 if nobody won
 */
int board_getWinStatus(Board *board);

/**
 * @brief Checks if current player selected their pawn by mouse event
 *        if yes, then pawn's available moves are marked
 *
 * @param board board
 * @param mousePosX position of mouse X axis
 * @param mousePosY position of mouse Y axis
 * @return void
 */
void board_checkPawnSelectionByMouse(Board *board, int mousePosX, int mousePosY);

/**
 * @brief Checks if current player selected their pawn available move by mouse event
 *        if yes, then pawn is moved
 *
 * @param board board
 * @param mousePosX position of mouse X axis
 * @param mousePosY position of mouse Y axis
 * @return void
 */
void board_checkTileSelectionByMouse(Board *board, int mousePosX, int mousePosY);

/**
 * @brief Resets all tiles texture to the default one
 *
 * @param board board
 * @return void
 */
void board_resetTilesTextures(Board *board);

/**
 * @brief Marks tile on a given coordinates as available to move to
 *
 * @param board with tiles
 * @param x position on X axis of tile
 * @param y position on Y axis of tile
 * @return void
 */
void board_markTileTexture(Board *board, int x, int y);

/**
 * @brief Calculates positions of pawns and inserts to array
 *
 * @param board
 * @return void
 */
void board_calculatePawnsOnBoardArray(Board *board);

#endif