#ifndef PAWN_H
#define PAWN_H

#include "./checkers.h"

/**
 * @brief Pawn type representation
 */
typedef enum
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
 *
 * @param Player *player
 * @param BoardPosition *position
 * @param PawnType pawnType
 * @param sfSprite *sprite
 */
struct Pawn
{
  Player *player;
  BoardPosition *position;
  PawnType pawnType;
  sfSprite *sprite;
  PawnBeat *availableMoves;
  int availableMovesCount;
};

/**
 * @brief Representation of Pawn's move on board with beating.
 *
 * @param BoardPosition destination
 * @param Pawn **pawnsToBeat array of pawns to beat
 * @param int pawnsToBeatCount
 */
struct PawnBeat {
  int x;
  int y;
  BoardPosition *pawnsToBeat;
  int pawnsToBeatCount;
};

/**
 * @brief Pawn constructor.
 *
 * @param iPosX position on X axis on Board
 * @param iPosY position on Y axis on Board
 * @param player player that pawn will be assigned to
 * @return created pawn
 */
Pawn *pawn_create(int iPosX, int iPosY, Player *player);

/**
 * @brief Set new texture to pawn.
 *
 * @param pawn
 * @param texture texture to assing to sprite
 * @return void
 */
void pawn_setTexture(Pawn *pawn, const sfTexture *texture);

/**
 * @brief Change pawn type. Changing type will change the
 *        sprite texture to proper one.
 *
 * @param pawn that
 * @param type type to assign
 * @return void
 */
void pawn_setType(Pawn *pawn, PawnType type);

/**
 * @brief Generate available moves on board for given pawn.
 *
 * @param pawn pawn
 * @return void
 */
void pawn_generateAvailableMoves(Pawn *pawn);

/**
 * @brief Marks available moves for player on board.
 *
 * @param pawn pawn that available moves will be marked
 * @return void
 */
void pawn_markAvailableMoves(Pawn *pawn);

/**
 * @brief Move given pawn to the given position.
 *
 * @param pawn pawn to be moved
 * @param position position on board that is the destination for pawn
 * @return void
 */
void pawn_move(Pawn *pawn, BoardPosition position);

/**
 * @brief Remove given pawn from the game
 *
 * @param pawn
 * @return void
 */
void pawn_remove(Pawn *pawn);

/**
 * @brief Find pawn on board on given axis
 *
 * @param board
 * @param x
 * @param y
 * @return Pawn*
 */
Pawn *pawn_findByPos(Board *board, int x, int y);
#endif