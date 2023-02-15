//
// Created by Julien on 12/02/2023.
//

#include "sdl_music.h"

void initMusic()
{
    //Initialize the audio subsystem
    if (Mix_OpenAudio(AUDIO_FREQUENCY, AUDIO_FORMAT_S16, AUDIO_CHANNELS, AUDIO_SAMPLES) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize audio: %s\n", Mix_GetError());
    }

    // Load the music
    Mix_Music *music = Mix_LoadMUS(PATH_MENU_MUSIC);
    if (!music) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load music: %s\n", Mix_GetError());
    }

    // Start playing the music
    if (Mix_PlayMusic(music, -1) == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't play music: %s\n", Mix_GetError());
    }

    // Wait until the music has finished
    while (Mix_PlayingMusic()) {
        SDL_Delay(100);
    }

    // Clean up
    Mix_FreeMusic(music);
    Mix_CloseAudio();
}