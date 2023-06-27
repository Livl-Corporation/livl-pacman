//
// Created by Franck GUTMANN on 27/06/2023.
//

#include "frightened.h"

int ghostEaten = 0;
MazeElement lastGhostEaten = EMPTY;

void eatGhost(MazeElement ghostElement)
{
    ghostEaten++;
    removeMazeElement(ghostElement, entityMaze);
    playAudioWithChannel(audioEatGhost, CHANNEL_EAT_GHOST);

    incrementScore(getEatenGhostScore(ghostEaten));

    setTimerCallback(&eatGhostAnimationTimer, endEatGhostAnimation);

    struct Position ghostSpawnPoint = getMazePositionOfElement(ghostElement, initialMaze);

    struct Ghost *sprite = getGhostByElement(ghostElement);

    if (sprite != NULL) {
        sprite->isDead = true;
        sprite->targetTile = ghostSpawnPoint;
    }

    resetTimer(&eatGhostAnimationTimer);
    startTimer(&eatGhostAnimationTimer);

    isGamePause = true;
    lastGhostEaten = ghostElement;
}

int getGhostEatenCount()
{
    return ghostEaten;
}

void resetGhostEatenCount()
{
    ghostEaten = 0;
}

void endEatGhostAnimation() {
    isGamePause = false;
}

bool isScoreAnimationOnGhostEaten()
{
    return eatGhostAnimationTimer.isRunning;
}

bool isGhostEatableRunningOut()
{
    return eatableGhostTimer.count < EATABLE_GHOST_DURATION / 4;
}

MazeElement getLastGhostEaten() {
    return lastGhostEaten;
}

int getEatenGhostScore(int eatenGhostCount)
{
    return pow(2, eatenGhostCount) * 100;
}