#ifndef PACMAN_PAUSE_MENU_H
#define PACMAN_PAUSE_MENU_H

#include <SDL.h>
#include "../constants.h"
#include "variables.h"
#include "../utilities/sdl_functions.h"
#include "game_window.h"

void drawPauseMenu();
void handlePauseMenuEvents();

#endif