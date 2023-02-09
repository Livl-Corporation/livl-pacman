//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_MENU_WINDOW_H
#define PACMAN_MENU_WINDOW_H

#include <stdbool.h>
#include "pacman_window.h"

void displayMainMenu();
void handleMainMenuEvents();
bool isPointInPlayButton(int x, int y);

#endif //PACMAN_MENU_WINDOW_H
