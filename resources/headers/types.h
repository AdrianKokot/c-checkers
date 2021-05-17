#ifndef TYPES_H
#define TYPES_H

typedef enum {false, true} bool;

/**
 * @brief Position on the board
 *
 * @param x position on X axis
 * @param y position on Y axis
 */
typedef struct BoardPosition BoardPosition;

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
 * @param spriteBackground board background sprite
 * @param shapeBackground board background shape
 * @param endText text struct to display on ending
 */
typedef struct Board Board;

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
typedef struct Player Player;

/**
 * @brief Pawn representation on Board.
 *
 * @param player owner pointer
 * @param position position on the board
 * @param pawnType type of the pawn
 * @param sprite sprite struct
 * @param availableMoves array of available moves for the pawn
 * @param availableMovesCount number of available moves
 */
typedef struct Pawn Pawn;

/**
 * @brief Representation of Pawn's move on board
 *
 * @param x position on board on X axis
 * @param y position on board on X axis
 * @param pawnsToBeat array of pawns that are beatable on that path
 * @param pawnsToBeatCount number of pawns that are beatable
 */
typedef struct PawnBeat PawnBeat;

#endif