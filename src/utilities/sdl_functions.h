//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_SDL_FUNCTIONS_H
#define PACMAN_SDL_FUNCTIONS_H

#include <SDL.h>
#include "constants.h"
#include "console_handler.h"
#include "../models/position.h"

void SDL_ExitWithError(const char *message);

int isPositionInRect(struct Position position, SDL_Rect *rect);

/// TO BE REMOVED
void initSDL();
void loadMedia();
void closeWindow();

#endif // PACMAN_SDL_FUNCTIONS_H
