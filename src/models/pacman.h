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
#include "enums/direction.h"
#include "models/maze.h"
#include "models/game.h"
#include "models/ghost.h"
#include "../ui/game_window.h"

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
 */
void drawPacman();

/**
 * Perform action when pacman has moved in grid
 * @return pacman position in UI
 */
struct Position onPacmanGridMove(struct Position *pacmanUiPos);

// -- Private --
void pacmanBlit(SDL_Rect srcRect);
int canMoveInDirection(Direction direction);
void updatePosition(struct Position *position, Direction direction);

struct Position teleportPacman(MazeElement teleporter);

#endif // PACMAN_PACMAN_H
