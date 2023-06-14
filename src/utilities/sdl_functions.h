//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_SDL_FUNCTIONS_H
#define PACMAN_SDL_FUNCTIONS_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "console_handler.h"

extern Mix_Chunk *soundMenu;
void SDL_ExitWithError(const char *message);

/// TO BE REMOVED
void initSDL();
void loadMedia();
void closeWindow();
void initSDLMixer();
void loadSound();
void playSound(Mix_Chunk *sound);
void SDLMixer_FreeAudio(Mix_Chunk *sound);
void SDLMixer_CleanupAudio();

#endif // PACMAN_SDL_FUNCTIONS_H
