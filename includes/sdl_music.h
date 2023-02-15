//
// Created by Julien on 12/02/2023.
//

#ifndef PACMAN_SDL_MUSIC_H
#define PACMAN_SDL_MUSIC_H

#include "SDL.h"
#include "SDL_mixer.h"

#define AUDIO_FREQUENCY 44100
#define AUDIO_FORMAT_S16 MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS 2
#define AUDIO_SAMPLES 4096

#define PATH_MENU_MUSIC "../../assets/sounds/intro.wav"

void initMusic();

#endif //PACMAN_SDL_MUSIC_H
