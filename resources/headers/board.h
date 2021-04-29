#ifndef BOARD_H
#define BOARD_H

#include "./checkers.h"

/**
 * @brief Position on the board
 *
 * @param int x
 * @param int y
 */
struct BoardPosition
{
  int x;
  int y;
};

/**
 * @brief Board representation
 *
 * @param sfRenderWindow *window
 * @param Player **players
 */
struct Board
{
  sfRenderWindow *window;
  int playerPawnCount;
  int playerCount;
  int boardSize;
  int textureSize;
  int boardBorder;
  Player **players;
  sfTexture **tileTextures;
  sfSprite ***tileSprites;
};

/**
 * @brief Board constructor.
 *
 * @param window sfRenderWindow instance
 * @param boardSize number of rows and columns of board
 * @param textureSize size of texture in pixels
 * @param boardBorder size of border (space betweend window and position that board will be drawn) in pixels
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
 * @return void
 */
void board_draw(Board *board);

/**
 * @brief Draw board tiles on sfRenderWindow
 *
 * @return void
 */
void board_drawBoard(Board *board);

/**
 * @brief Draw player pawns on sfRenderWindow
 *
 * @return void
 */
void board_drawPawns(Board *board);

/**
 * @brief Destroy memory allocation for all items in board. Including window, players, pawns
 *
 * @return void
 */
void board_destroy(Board *board);

/**
 * @brief Check if game has ended
 *
 * @return true in case of win / tie, false otherwise
 */
bool board_checkWinStatus(Board *board);

/**
 * @brief Gets index of player that won
 *
 * @return index of player that won, -1 if nobody won
 */
int board_getWinStatus(Board *board);

/**
 * @brief Checks if current player selected their pawn by mouse event
 *        if yes, then pawn's available moves are marked
 *
 * @return void
 */
void board_checkPawnSelectionByMouse(Board *board, int mousePosX, int mousePosY);

#endif