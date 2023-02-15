//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_GAME_WINDOW_H
#define PACMAN_GAME_WINDOW_H

#include <stdbool.h>
#include <SDL.h>

#include "variables.h"

extern int count;
extern bool* pGameQuit;

void startGameLoop();
bool handleGameEvents();
void drawGame();

#endif //PACMAN_GAME_WINDOW_H
