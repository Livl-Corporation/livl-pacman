//
// Created by Julien on 18/06/2023.
//

#ifndef PACMAN_AUDIO_H
#define PACMAN_AUDIO_H

#include <SDL_mixer.h>
#include "../utilities/sdl_functions.h"
#include "game.h"
#include "models/ghost-mode-manager.h"

#define AUDIO_DEATH "../assets/sounds/death.wav"
#define AUDIO_DOT_1 "../assets/sounds/dot_1.wav"
#define AUDIO_DOT_2 "../assets/sounds/dot_2.wav"
#define AUDIO_EAT_GHOST "../assets/sounds/eat_ghost.wav"
#define AUDIO_EYES "../assets/sounds/eyes.wav"
#define AUDIO_FRUIT "../assets/sounds/fruit.wav"
#define AUDIO_GAME_START "../assets/sounds/game_start.wav"
#define AUDIO_PACMAN_DRILL "../assets/sounds/pacman_drill.wav"
#define AUDIO_PAUSE "../assets/sounds/pause.wav"
#define AUDIO_PAUSE_BEAT "../assets/sounds/pause_beat.wav"
#define AUDIO_POWER_UP "../assets/sounds/power_up.wav"
#define AUDIO_SIREN_1 "../assets/sounds/siren_1.wav"

#define CHANNEL_DEFAULT (-1)
#define MAX_CHANNELS 13
#define CHANNEL_PACMAN_DRILL 1
#define CHANNEL_GAME_START 2
#define CHANNEL_DOT 3
#define CHANNEL_SIREN 4
#define CHANNEL_POWER_UP 5
#define CHANNEL_PAUSE_BEAT 6
#define CHANNEL_PAUSE 7
#define CHANNEL_EAT_GHOST 8
#define CHANNEL_EYES 9
#define CHANNEL_FRUIT 10
#define CHANNEL_DEATH 11
#define CHANNEL_DOT_2 12

#define NO_LOOP 0
#define LOOP_INFINITE (-1)

extern Mix_Chunk *audioDeath;
extern Mix_Chunk *audioDotOne;
extern Mix_Chunk *audioDotTwo;
extern Mix_Chunk *audioEatGhost;
extern Mix_Chunk *audioEyes;
extern Mix_Chunk *audioFruit;
extern Mix_Chunk *audioGameStart;
extern Mix_Chunk *audioPacmanDrill;
extern Mix_Chunk *audioPause;
extern Mix_Chunk *audioPauseBeat;
extern Mix_Chunk *audioPowerUp;
extern Mix_Chunk *audioSirenOne;

void initAudio();
void playAudioWithChannelLoop(Mix_Chunk *sound, int channel);
void playAudioWithChannel(Mix_Chunk *sound, int channel);
void volumeAudio(Mix_Chunk *sound, int volume);
void playDotSound();
void playSirenOrPowerUpSound();
void stopSirenOrPowerUpSound();
void stopAudio(int channel);
void freeAudios();

#endif //PACMAN_AUDIO_H
