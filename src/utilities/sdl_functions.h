//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_SDL_FUNCTIONS_H
#define PACMAN_SDL_FUNCTIONS_H

#define GAME_TITLE "PacMan"
#define PATH_SPRITE_SHEET_PACMAN "../assets/img/pacman_sprites.bmp"
#define PATH_SPRITE_SHEET_PLAY_BTN "../assets/img/play_btn.bmp"
#define WINDOW_SCREEN_WIDTH 700
#define WINDOW_SCREEN_HEIGHT 900

#include <SDL.h>
#include "console_handler.h"

void initSDL();
void loadMedia();
void SDL_ExitWithError(const char *message);
void closeWindow();

#endif //PACMAN_SDL_FUNCTIONS_H
