//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_SDL_FUNCTIONS_H
#define PACMAN_SDL_FUNCTIONS_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "console_handler.h"

void SDL_ExitWithError(const char *message);

/// TO BE REMOVED
void initSDL();
void loadMedia();
void closeWindow();

#endif // PACMAN_SDL_FUNCTIONS_H
