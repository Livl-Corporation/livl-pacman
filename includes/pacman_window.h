//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_PACMAN_WINDOW_H
#define PACMAN_PACMAN_WINDOW_H

#include "main.h"

extern int count;
extern bool* pGameQuit;

void startGameLoop();
bool handleGameEvents();
void drawGame();

#endif //PACMAN_PACMAN_WINDOW_H
