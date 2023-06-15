//
// Created by Franck GUTMANN on 27/05/2023.
//

#include "game.h"

int score = 0;
int high_score = 0;
int lives = INITIAL_LIVES;
int timerGameOverImage = 0;

int getScore() {
    return score;
}

int getHighScore() {
    return high_score;
}

void incrementScore(int value) {
    score += value;

    if (score > high_score) {
        high_score = score;
    }
}

void decrementScore(int value) {
    score -= value;
}

int getLives() {
    return lives;
}

void decrementLives() {
    lives--;

    if(lives == 0) timerGameOverImage = GAME_OVER_DURATION;
}

void decrementTimerGameOverImage()
{
    timerGameOverImage--;
}

bool isTimerGameOverImage()
{
    return timerGameOverImage > 0;
}


void drawGameInfos() {
    // TODO : Issue #22 display informations on screen
}