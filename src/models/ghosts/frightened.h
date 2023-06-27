//
// Created by Franck GUTMANN on 27/06/2023.
//

#ifndef PACMAN_FRIGHTENED_H
#define PACMAN_FRIGHTENED_H

#include <SDL.h>
#include "enums/maze-element.h"
#include <stdbool.h>
#include "models/game.h"
#include "models/audio.h"
#include "models/timer.h"

int getEatenGhostScore(int eatenGhostCount);

void eatGhost(MazeElement ghostElement);

int getGhostEatenCount();

void resetGhostEatenCount();

bool isGhostEatableRunningOut();

void endEatGhostAnimation();

bool isScoreAnimationOnGhostEaten();

MazeElement getLastGhostEaten();

#endif //PACMAN_FRIGHTENED_H
