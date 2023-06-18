//
// Created by Julien on 18/06/2023.
//

#include "audio.h"

Mix_Chunk *audioDotOne = NULL;
Mix_Chunk *audioDotTwo = NULL;
Mix_Chunk *audioGameStart = NULL;
Mix_Chunk *audioPacmanDrill = NULL;

void initAudio()
{
    //loadSound(AUDIO_DEATH);
    loadSound(&audioDotOne, AUDIO_DOT_1);
    loadSound(&audioDotTwo, AUDIO_DOT_2);
    //loadSound(AUDIO_EAT_GHOST);
    //loadSound(AUDIO_EYES);
    //loadSound(AUDIO_FRUIT);
    loadSound(&audioGameStart, AUDIO_GAME_START);
    loadSound(&audioPacmanDrill, AUDIO_PACMAN_DRILL);
    //loadSound(AUDIO_PAUSE);
    //loadSound(AUDIO_PAUSE_BEAT);
    //loadSound(AUDIO_POWER_UP);
    //loadSound(AUDIO_SIREN_1);
}

void playDotSound()
{
    if (getEatenDotsCount() % 2 == 0)
        playAudio(audioDotOne);
    else
        playAudio(audioDotTwo);
}

void playAudio(Mix_Chunk *sound)
{
    playAudioWithChannelLoop(sound, CHANNEL_DEFAULT, LOOP_DEFAULT);
}

void playAudioWithChannel(Mix_Chunk *sound, int channel)
{
    playAudioWithChannelLoop(sound, channel, LOOP_DEFAULT);
}

void playAudioWithChannelLoop(Mix_Chunk *sound, int channel, int loops)
{
    Mix_PlayChannel(channel, sound, loops);
}

void volumeAudio(Mix_Chunk *sound, int volume)
{
    if(volume > 0 && volume <= MIX_MAX_VOLUME)
        Mix_VolumeChunk(sound, volume);
}

void stopAudio(int channel) {
    Mix_HaltChannel(channel);
}

void freeAudio()
{
    freeSound(audioDotOne);
    freeSound(audioDotTwo);
    freeSound(audioGameStart);
    freeSound(audioPacmanDrill);
}