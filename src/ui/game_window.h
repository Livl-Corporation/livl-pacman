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
#include "models/pacman.h"
#include "models/position.h"
#include "models/ghost.h"

extern int count;

void startGameLoop();
bool handleGameEvents();
void drawGame();

#endif // PACMAN_GAME_WINDOW_H
