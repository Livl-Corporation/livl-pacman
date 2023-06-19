//
// Created by Julien on 18/06/2023.
//

#include "audio.h"

Mix_Chunk *audioDeath = NULL;
Mix_Chunk *audioDotOne = NULL;
Mix_Chunk *audioDotTwo = NULL;
Mix_Chunk *audioEatGhost = NULL;
Mix_Chunk *audioEyes = NULL;
Mix_Chunk *audioFruit = NULL;
Mix_Chunk *audioGameStart = NULL;
Mix_Chunk *audioPacmanDrill = NULL;
Mix_Chunk *audioPause = NULL;
Mix_Chunk *audioPauseBeat = NULL;
Mix_Chunk *audioPowerUp = NULL;
Mix_Chunk *audioSirenOne = NULL;

bool isPowerUpPlaying = false;
bool isSirenPlaying = false;

void initAudio()
{
    Mix_AllocateChannels(MAX_CHANNELS);

    loadSound(&audioDeath, AUDIO_DEATH);
    loadSound(&audioDotOne, AUDIO_DOT_1);
    loadSound(&audioDotTwo, AUDIO_DOT_2);
    loadSound(&audioEatGhost, AUDIO_EAT_GHOST);
    loadSound(&audioEyes, AUDIO_EYES);
    loadSound(&audioFruit, AUDIO_FRUIT);
    loadSound(&audioGameStart, AUDIO_GAME_START);
    loadSound(&audioPacmanDrill, AUDIO_PACMAN_DRILL);
    loadSound(&audioPause, AUDIO_PAUSE);
    loadSound(&audioPauseBeat, AUDIO_PAUSE_BEAT);
    loadSound(&audioPowerUp, AUDIO_POWER_UP);
    loadSound(&audioSirenOne, AUDIO_SIREN_1);
}

void playDotSound()
{
    if (getEatenDotsCount() % 2 == 0) {
        stopAudio(CHANNEL_DOT_2);
        playAudioWithChannel(audioDotOne, CHANNEL_DOT);
    }
    else {
        stopAudio(CHANNEL_DOT);
        playAudioWithChannel(audioDotTwo, CHANNEL_DOT_2);
    }
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
    if((pacmanDeathAnimationDelayTimer.isRunning || pacmanDeathAnimationTimer.isRunning)
        || nextRoundAnimationTimer.isRunning || readyTimer.isRunning || gameOverTimer.isRunning) {
        stopSirenOrPowerUpSound();
        return;
    }

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
    playAudioWithChannelLoop(sound, channel, NO_LOOP);
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

void freeAudios()
{
    freeSound(audioDotOne);
    freeSound(audioDotTwo);
    freeSound(audioGameStart);
    freeSound(audioPacmanDrill);
    freeSound(audioPause);
    freeSound(audioPauseBeat);
    freeSound(audioPowerUp);
    freeSound(audioSirenOne);
    freeSound(audioDeath);
    freeSound(audioEatGhost);
    freeSound(audioEyes);
    freeSound(audioFruit);
}