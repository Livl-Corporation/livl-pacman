//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_GAME_WINDOW_H
#define PACMAN_GAME_WINDOW_H

#include <stdbool.h>
#include <SDL.h>
#include "../models/maze.h"
#include "../utilities/console_handler.h"
#include "variables.h"

#define SQUARE_WIDTH 32
#define SQUARE_HEIGHT 32

typedef enum {
    MOVEMENT_DIRECTION_LEFT = 0,
    MOVEMENT_DIRECTION_RIGHT = 1,
    MOVEMENT_DIRECTION_UP = 2,
    MOVEMENT_DIRECTION_DOWN = 3,
} MovementDirection;

extern int count;
extern bool pGameQuit;
extern MovementDirection actualPacmanMovementDirection;

MovementDirection getMovementDirectionFromKey(SDL_Keycode key);
void initLoadMaze();
void startGameLoop();
bool handleGameEvents();
SDL_Point getPacmanPosition(SDL_Rect pacman);
void drawGame();

#endif //PACMAN_GAME_WINDOW_H
