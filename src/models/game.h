//
// Created by Franck GUTMANN on 27/05/2023.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "constants.h"
#include "timer.h"

extern struct Timer eatableGhostTimer;
extern struct Timer readyTimer;
extern struct Timer gameOverTimer;
extern struct Timer eatGhostAnimationTimer;
extern struct Timer pacmanDeathAnimationTimer;
extern struct Timer pacmanDeathAnimationDelayTimer;

void initTimers();

int getScore();

int getHighScore();

void incrementScore(int value);

void decrementScore(int value);

void afterGameOverAnimation();

int getLives();

void decrementLives();

#endif // PACMAN_GAME_H