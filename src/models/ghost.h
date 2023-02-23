//
// Created by Franck GUTMANN on 23/02/2023.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <SDL.h>
#include "models/position.h"
#include "enums/direction.h"
#include "constants.h"
#include "maze.h"

struct Ghost {
    int number;
    struct Position uiPosition;
    struct Position gridPosition;
    SDL_Rect *spritePos;
};

/**
 * Initialize the ghost list
 * <!> Must be called before any other ghost function
 */
void initGhostList();

/**
 * Place a ghost on his spawn point
 * @param ghostId
 */
void spawnGhost(int ghostId);

/**
 * Make all ghost movesafare
 * @param count
 */
void drawGhosts(int count);

/**
 * Free the ghost list
 * <!> Must be called at the end of the game
 */
void freeGhostList();

// Private
void updateGhost(struct Ghost ghost, int count);
void blitGhost(struct Ghost ghost, SDL_Rect *spritePos);

#endif //PACMAN_GHOST_H
