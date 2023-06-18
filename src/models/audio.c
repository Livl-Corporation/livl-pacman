//
// Created by Julien on 18/06/2023.
//

#include "audio.h"

Mix_Chunk *audioDotOne = NULL;
Mix_Chunk *audioDotTwo = NULL;
Mix_Chunk *audioGameStart = NULL;
Mix_Chunk *audioPacmanDrill = NULL;
Mix_Chunk *audioPowerUp = NULL;
Mix_Chunk *audioSirenOne = NULL;

bool isPowerUpPlaying = false;
bool isSirenPlaying = false;

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
    loadSound(&audioPowerUp, AUDIO_POWER_UP);
    loadSound(&audioSirenOne, AUDIO_SIREN_1);
}

void playDotSound()
{
    if (getEatenDotsCount() % 2 == 0)
        playAudioWithChannel(audioDotOne, CHANNEL_DOT);
    else
        playAudioWithChannel(audioDotTwo, CHANNEL_DOT);
}

void stopSirenOrPowerUpSound()
{
    stopAudio(CHANNEL_SIREN);
    stopAudio(CHANNEL_POWER_UP);
    isSirenPlaying = false;
    isPowerUpPlaying = false;
}

void playSirenOrPowerUpSound()
{
    if (isGhostEatable()) {
        if (!isPowerUpPlaying) {
            playAudioWithChannelLoop(audioPowerUp, CHANNEL_POWER_UP, LOOP_INFINITE);
            isPowerUpPlaying = true;
        }
        if (isSirenPlaying) {
            stopAudio(CHANNEL_SIREN);
            isSirenPlaying = false;
        }
    } else {
        if (!isSirenPlaying) {
            playAudioWithChannelLoop(audioSirenOne, CHANNEL_SIREN, LOOP_INFINITE);
            isSirenPlaying = true;
        }
        if (isPowerUpPlaying) {
            stopAudio(CHANNEL_POWER_UP);
            isPowerUpPlaying = false;
        }
    }
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