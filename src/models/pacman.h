//
// Created by Franck GUTMANN on 15/02/2023.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include <SDL.h>
#include "utilities/sdl_functions.h"
#include "ui/variables.h"
#include "models/position.h"
#include "constants.h"
#include "models/direction.h"
#include "models/maze.h"

/**
 * Initialize pacman position at his spawn point
 * <!> This function must be called at least once before any other pacman function
 */
void spawnPacman();

/**
 * Handle user input
 */
void handlePacmanEvents();

/**
 * Calculate, validate, update and draw pacman position
 * @param count used for animations
 */
void drawPacman(int count);

/**
 * Perform action when pacman has moved in grid
 */
void onPacmanGridMove();

// -- Private --
void pacmanBlit(SDL_Rect *srcRect);

#endif // PACMAN_PACMAN_H
