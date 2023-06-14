#ifndef PACMAN_PAUSE_MENU_H
#define PACMAN_PAUSE_MENU_H

#include <SDL.h>
#include "../constants.h"
#include "variables.h"
#include "../utilities/sdl_functions.h"
#include "game_window.h"

#define TITLE_W 47
#define TITLE_H 7
#define TITLE_UI_SCALE 4

#define RESUME_BUTTON_W 47
#define RESUME_BUTTON_H 7

#define MAIN_MENU_BUTTON_W 71
#define MAIN_MENU_BUTTON_H 7

#define BUTTONS_UI_SCALE 3
#define BUTTONS_HOVER_SPACING 9

void drawPauseMenu();
void handlePauseMenuEvents();

#endif