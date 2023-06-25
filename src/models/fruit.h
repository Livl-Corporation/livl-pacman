//
// Created by Franck GUTMANN on 16/06/2023.
//

#ifndef PACMAN_FRUIT_H
#define PACMAN_FRUIT_H

#include <SDL.h>
#include "../utilities/sdl_functions.h"
#include "timer.h"
#include "game.h"
#include "../ui/variables.h"
#include "maze.h"

#define FRUIT_COUNTS 8
#define FRUIT_SIZE 14
#define FRUIT_X_SPACING 2

#define FRUIT_SCORE_W 17
#define FRUIT_SCORE_H 7
#define FRUIT_SCORE_Y_SPACING 2
#define FRUIT_SCORE_UI_SCALE 2

extern SDL_Rect fruitsRects[FRUIT_COUNTS];

void initFruits();

int getFruitLevel(int round);

void handleFruitCollision();

void spawnFruit();

void drawFruit();

void resetFruit();

#endif // PACMAN_FRUIT_H
