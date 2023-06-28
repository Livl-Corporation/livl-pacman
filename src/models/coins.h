//
// Created by Franck GUTMANN on 27/06/2023.
//

#ifndef PACMAN_COINS_H
#define PACMAN_COINS_H

#include "constants.h"
#include "enums/maze-element.h"
#include "models/position.h"
#include "models/maze.h"
#include "utilities/sdl_functions.h"

/**
 * Fill the maze with coins
 */
void drawCoins(int frameCount);

void refillCoins();

#endif //PACMAN_COINS_H
