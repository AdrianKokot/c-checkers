#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.h>
#include "./lang_utils.h"

/**
 * @brief Position on the board
 */
typedef struct BoardPosition BoardPosition;

/**
 * @brief Board representation
 */
typedef struct Board Board;

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

#include "./player.h"

#endif