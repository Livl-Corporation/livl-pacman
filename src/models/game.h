//
// Created by Franck GUTMANN on 27/05/2023.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "constants.h"
#include "timer.h"
#include "ghost.h"
#include "maze.h"
#include "ui/menu_window.h"

extern struct Timer eatableGhostTimer;
extern struct Timer readyTimer;
extern struct Timer gameOverTimer;
extern struct Timer eatGhostAnimationTimer;
extern struct Timer pacmanDeathAnimationTimer;
extern struct Timer pacmanDeathAnimationDelayTimer;
extern struct Timer fruitTimer;
extern struct Timer fruitScoreAnimationTimer;
extern struct Timer nextRoundAnimationTimer;

void initTimers();

void initGame();

int getScore();

int getHighScore();

void incrementScore(int value);

void afterGameOverAnimation();

int getLives();

void decrementLives();

int getRound();
void nextRound();
void startNextRoundAnimation();
void endNextRoundAnimation();

int getEatenDotsCount();
void incrementEatenDotsCount();
void resetEatenDotsCount();

int getInitialDotsCount();
void setInitialDotsCount(int value);

void freeGame();

void goBackToMenu();

#endif // PACMAN_GAME_H