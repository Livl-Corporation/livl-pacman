//
// Created by Franck GUTMANN on 27/05/2023.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "constants.h"
#include <stdbool.h>
#include <stdio.h>

int getScore();

int getHighScore();

void incrementScore(int value);

void decrementScore(int value);

int getLives();

void decrementLives();

void drawGameInfos();

void decrementTimerGameOverImage();

bool isTimerGameOverImage();

#endif //PACMAN_GAME_H