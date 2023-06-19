#ifndef PACMAN_GAME_INFO_PANEL_H
#define PACMAN_GAME_INFO_PANEL_H

#include <SDL.h>
#include <stdbool.h>
#include "variables.h"
#include "../models/game.h"
#include "../utilities/console_handler.h"
#include "models/position.h"
#include "models/pacman.h"
#include "models/fruit.h"
#include "utilities/sdl_functions.h"

#define GHOST_SCORE_W 15
#define GHOST_SCORE_H 7
#define GHOST_SCORE_UI_SCALE 2
#define GHOST_SCORES_SPACING 9

#define NUMBER_SPRITES_SPACING 8
#define NUMBER_UI_SPACING 13;

#define GAME_OVER_W 78
#define GAME_OVER_H 7
#define GAME_OVER_UI_SCALE 2

#define FRUIT_BAR_MAX_FRUITS 7
#define FRUIT_BAR_SPACING 3
#define FRUIT_BAR_UI_SCALE 2
#define FRUIT_BAR_RIGHT_MARGIN 200

#define BOTTOM_BAR_SPACING 33

void initGameInfoPanel();

void drawGameInfoPanel();

void drawHighScore();

void drawScore(int score, SDL_Rect imgUi);

void drawEatGhostScore(int eatenGhostCount, SDL_Rect imgUi);

void drawLives();

void drawUp();

void drawReady();

void drawGameOver();

int getNumDigits(int score);

void drawFruitBar();

#endif // PACMAN_GAME_INFO_PANEL_H
