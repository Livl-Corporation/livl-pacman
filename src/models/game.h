//
// Created by Franck GUTMANN on 27/05/2023.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "constants.h"

int getScore();

void incrementScore(int value);

void decrementScore(int value);

int getLives();

void decrementLives();

void drawGameInfos();

#endif //PACMAN_GAME_H