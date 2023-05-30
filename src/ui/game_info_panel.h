#ifndef PACMAN_GAME_INFO_PANEL_H
#define PACMAN_GAME_INFO_PANEL_H

#include <SDL.h>
#include <stdbool.h>
#include "variables.h"
#include "../models/game.h"
#include "../utilities/console_handler.h"

/**
 * @brief Get the img Numbers On Sprite image from number 0 to 9
 */
extern SDL_Rect imgNumbersSprite[10];

/**
 * @brief Get the img Numbers On Sprite image
 */
void initImgNumbersOnSprite();

/**
 * @brief Display the score on the game UI
 */
void drawScore();

#endif //PACMAN_GAME_INFO_PANEL_H
