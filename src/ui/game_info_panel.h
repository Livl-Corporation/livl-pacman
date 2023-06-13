#ifndef PACMAN_GAME_INFO_PANEL_H
#define PACMAN_GAME_INFO_PANEL_H

#include <SDL.h>
#include <stdbool.h>
#include "variables.h"
#include "../models/game.h"
#include "../utilities/console_handler.h"
#include "models/position.h"
#include "models/pacman.h"

/**
 * @brief Get the img Numbers On Sprite image from number 0 to 9
 */
extern SDL_Rect imgNumbersSprite[10];

void initImgNumbersOnSprite();

void initGameInfoPanel();

void drawGameInfoPanel();

void drawHighScore();

void drawScore(int score, SDL_Rect imgUi);

void drawLives();

void drawUp();

int getNumDigits(int score);

#endif //PACMAN_GAME_INFO_PANEL_H
