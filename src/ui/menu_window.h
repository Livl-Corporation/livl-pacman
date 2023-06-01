//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_MENU_WINDOW_H
#define PACMAN_MENU_WINDOW_H

#include "game_window.h"

void startMainMenuLoop();
void drawMainMenu();
void handleMainMenuEvents();
bool isPointInPlayButton(int x, int y);

#endif //PACMAN_MENU_WINDOW_H
