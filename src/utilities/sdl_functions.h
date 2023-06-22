//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_SDL_FUNCTIONS_H
#define PACMAN_SDL_FUNCTIONS_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "console_handler.h"
#include "../models/position.h"

void SDL_ExitWithError(const char *message);

int isPositionInRect(struct Position position, SDL_Rect *rect);

void exportSprites(SDL_Rect *srcRect, SDL_Rect *destRect, int count, int xStep, int yStep);

void initSDL_Mixer();
void loadSound(Mix_Chunk **audio, char *path);
void freeSound(Mix_Chunk *audio);
void closeSDL_Mixer();

void initSDL();
void loadMedia();
void closeWindow();


#endif // PACMAN_SDL_FUNCTIONS_H
