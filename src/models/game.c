//
// Created by Franck GUTMANN on 27/05/2023.
//

#include <stdio.h>
#include "game.h"

int score = 0;
int lives = INITIAL_LIVES;

int getScore() {
    return score;
}

void incrementScore(int value) {
    score += value;
}

void decrementScore(int value) {
    score -= value;
}

int getLives() {
    return lives;
}

void decrementLives() {
    lives--;
}

void drawGameInfos() {
    // TODO : Issue #22 display informations on screen
}