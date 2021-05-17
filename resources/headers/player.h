#ifndef PLAYER_H
#define PLAYER_H

#include "./checkers.h"

/**
 * @brief Player representation on Board.
 *
 * @param bIsActive bool that represents
 *                  whether player is now the active one
 * @param iPawnCount count of player's available pawns
 * @param textures array of textures for player's pawns
 * @param pawns array of player's pawns
 * @param board pointer to board
 * @param selectedPawn currently selected by click pawn
 */
struct Player
{
  bool bIsActive;
  int iPawnCount;
  sfTexture **textures;
  Pawn **pawns;
  Board *board;
  Pawn *selectedPawn;
};

/**
 * @brief Player constructor.
 *
 * @param iPawnCount number of pawns to create
 * @param board that player is assigned to
 * @param textures array of textures that contains two textures:
 *                     the standard pawn texture and
 *                     the queen pawn texture
 * @param isTopPlayer bool that deremines where pawns
 *                    are going to be drawn
 * @return created player
 */
Player *player_create(int iPawnCount, Board *board, sfTexture **textures, bool isTopPlayer);

/**
 * @brief Makes given player an active one on the board.
 *
 * @param player player that will be made active one
 * @return void
 */
void player_makeActive(Player *player);

#endif