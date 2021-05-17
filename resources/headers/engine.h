
#ifndef ENGINE_H
#define ENGINE_H

#include "./checkers.h"

/**
 * @brief Create sfRenderwindow
 *
 * @param size size of the window (squre)
 * @return created window struct
 */
sfRenderWindow *engine_createWindow(int size);

/**
 * @brief Create sprite with texture from given path
 *
 * @param texturePath path to the texture
 * @return created sprite struct
 */
sfSprite *engine_createSprite(char *texturePath);

/**
 * @brief Create sprite with given texture
 *
 * @param spriteTexture sfTexture pointer
 *                      that will be attached to sprite
 * @return created sprite with given texture
 */
sfSprite *engine_createSpriteFromTexture(sfTexture *spriteTexture);

/**
 * @brief Check sfRenderWindow events
 *
 * @param board board
 * @return void
 */
void engine_checkEvents(Board *board);

/**
 * @brief Checks game win state, if any player won, then displays end text
 *
 * @param board board
 * @return true if any player has won, false otherwise
 */
bool engine_checkWinState(Board *board);

/**
 * @brief Add background sprites to render in given board
 *
 * @param board board
 */
void engine_attachBackgroundToBoard(Board *board);

/**
 * @brief Read boardSize, textureSize, boardBorderSize from config
 *
 * @return array with 3 items - boardSize, textureSize and boardBorderSize
 */
int *engine_readConfig();

#endif