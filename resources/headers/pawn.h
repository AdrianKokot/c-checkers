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
 * @param player owner pointer
 * @param position position on the board
 * @param pawnType type of the pawn
 * @param sprite sprite struct
 * @param availableMoves array of available moves for the pawn
 * @param availableMovesCount number of available moves
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
 * @brief Representation of Pawn's move on board
 *
 * @param x position on board on X axis
 * @param y position on board on X axis
 * @param pawnsToBeat array of pawns that are beatable on that path
 * @param pawnsToBeatCount number of pawns that are beatable
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
 * @param pawn pawn pointer
 * @param texture texture to assing to sprite
 * @return void
 */
void pawn_setTexture(Pawn *pawn, const sfTexture *texture);

/**
 * @brief Change pawn type. Changing type will change the
 *        sprite texture to proper one.
 *
 * @param pawn pawn pointer
 * @param type pawn type to assign
 * @return void
 */
void pawn_setType(Pawn *pawn, PawnType type);

/**
 * @brief Generate available moves on board for given pawn.
 *
 * @param pawn pawn pointer
 * @return void
 */
void pawn_generateAvailableMoves(Pawn *pawn);

/**
 * @brief Marks available moves for player on board.
 *
 * @param pawn pointer to the pawn that available moves will be marked
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
 * @brief Remove given pawn from the board and memory
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
 * @return found pawn
 */
Pawn *pawn_findByPos(Board *board, int x, int y);
#endif