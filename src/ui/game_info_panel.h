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
 * @brief Init all the different required img from the sprite sheet
 */
void initGameInfoPanel();

/**
 * @brief Display all the different things (score, lives, etc) to draw on the UI
 */
void drawGameInfoPanel();

/**
 * @brief Display the high score title and value
 */
void drawHighScore();

/**
 * @brief Display the score on the game UI
 */
void drawScore(int score, SDL_Rect imgUi);

/**
 * @brief Display the lives on the game UI
 */
void drawLives();

void drawUp();

int getNumDigits(int score);

#endif //PACMAN_GAME_INFO_PANEL_H
