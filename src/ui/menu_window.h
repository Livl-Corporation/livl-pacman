//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_MENU_WINDOW_H
#define PACMAN_MENU_WINDOW_H

#define GAME_TITLE "PacMan"
#define PATH_SPRITE_SHEET_PACMAN "../assets/img/pacman_sprites.bmp"
#define PATH_SPRITE_SHEET_PLAY_BTN "../assets/img/play_btn.bmp"

#include "game_window.h"

void startMainMenuLoop();
void drawMainMenu();
void handleMainMenuEvents();
bool isPointInPlayButton(int x, int y);

#endif //PACMAN_MENU_WINDOW_H
