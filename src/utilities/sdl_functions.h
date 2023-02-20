//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_SDL_FUNCTIONS_H
#define PACMAN_SDL_FUNCTIONS_H

#define PATH_SPRITE_SHEET_PLAY_BTN "../assets/img/play_btn.bmp"
#define WINDOW_SCREEN_WIDTH 700
#define WINDOW_SCREEN_HEIGHT 900

#include <SDL.h>
#include "constants.h"

void SDL_ExitWithError(const char *message);

/// TO BE REMOVED
void initSDL();
void loadMedia();
void closeWindow();

#endif // PACMAN_SDL_FUNCTIONS_H
