#ifndef PLAYER_H
#define PLAYER_H

/**
 * @brief Player representation on Board.
 */
typedef struct Player Player;

/**
 * @brief Player constructor.
 * @param iPawnCount number of pawns to create
 * @param texturePaths string array that contains two paths:
 *                     to the standard pawn texture and
 *                     the queen pawn texture
 * @return created player
 */
Player *player_create(int iPawnCount, char **texturePaths);

/**
 * @brief Makes given player an active one on the board.
 * @param board board that contains player
 * @param player player that will be made active one
 * @return void
 */
void player_makeActive(Player *player);

#include <SFML/Graphics.h>
#include "./lang_utils.h"
#include "./board.h"
#include "./pawn.h"
#include "./game_utils.h"
#include "./game_window.h"

#endif