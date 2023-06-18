//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_MENU_WINDOW_H
#define PACMAN_MENU_WINDOW_H

#include "../utilities/sdl_functions.h"
#include "game_window.h"

#define PACMAN_TITLE_W 180
#define PACMAN_TITLE_H 46
#define PACMAN_TITLE_UI_SCALE 2.75
#define PACMAN_TITLE_UI_Y 100

#define PLAY_HOVER_SPACING 9;
#define PLAY_W 46
#define PLAY_H 7
#define PLAY_UI_SCALE 5
#define PLAY_UI_Y 400

void startMenu();
void drawMainMenu();
void handleMainMenuEvents();

#endif // PACMAN_MENU_WINDOW_H
