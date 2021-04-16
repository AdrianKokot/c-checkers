#ifndef BOARD_H
#define BOARD_H

#include "./types.h"

/**
 * @brief Position on the board
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
 * @param sfRenderWindow *window
 * @param Player **players
 */
struct Board
{
  sfRenderWindow *window;
  Player **players;
};

/**
 * @brief Board constructor.
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
    char boardTileTextures[2][2][255],
    char playerPawnTextures[2][2][255]);

/**
 * @brief Draw board tiles on sfRenderWindow
 * @return void
 */
void board_drawBoard();

/**
 * @brief Draw player pawns on sfRenderWindow
 * @return void
 */
void board_drawPawns();

/**
 * @brief Check if game has ended
 * @return true in case of win / tie, false otherwise
 */
bool board_checkWinStatus();

/**
 * @brief Gets index of player that won
 * @return index of player that won, -1 if nobody won
 */
int board_getWinStatus();

/**
 * @brief Checks if current player selected their pawn by mouse event
 *        if yes, then pawn's available moves are marked
 * @return void
 */
void board_checkPawnSelectionByMouse();

#endif