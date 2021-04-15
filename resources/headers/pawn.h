#ifndef PAWN_H
#define PAWN_H

#include "./player.h"
#include "./board.h"

/**
 * @brief Pawn type representation
 */
typedef enum PawnType
{
  /**
   * Standard pawn
   */
  Standard,
  /**
   * Queen pawn
   */
  Queen
} PawnType;

/**
 * @brief Pawn representation on Board.
 */
typedef struct Pawn Pawn;

/**
 * @brief Pawn constructor.
 * @param iPosX position on X axis on Board
 * @param iPosY position on Y axis on Board
 * @param texture texture to assing to sprite
 * @return created pawn
 */
Pawn *pawn_create(int iPosX, int iPosY, const sfTexture *texture);

/**
 * @brief Set new texture to pawn.
 * @param texture texture to assing to sprite
 * @return void
 */
void pawn_setTexture(const sfTexture *texture);

/**
 * @brief Change pawn type. Changing type will change the sprite texture to proper one.
 * @param type type to assign
 * @return void
 */
void pawn_changeType(PawnType type);

/**
 * @brief Get available moves on board for given pawn.
 * @param pawn pawn
 * @return array of positions that are available
 */
BoardPosition* pawn_getAvailableMoves(Pawn *pawn);

/**
 * @brief Marks available moves for player on board.
 * @param pawn pawn that available moves will be marked
 * @return void
 */
void pawn_markAvailableMoves(Pawn *pawn);

/**
 * @brief Move given pawn to the given position.
 * @param pawn pawn to be moved
 * @param position position on board that is the destination for pawn
 * @return void
 */
// void pawn_move(Pawn *pawn, BoardPosition position);

#endif