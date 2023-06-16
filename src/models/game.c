//
// Created by Franck GUTMANN on 27/05/2023.
//

#include "game.h"

int score = 0;
int high_score = 0;
int lives = INITIAL_LIVES;

int roundNumber = 0;
int dotsCount = 0;
int eatenDotsCount = 0;

struct Timer eatableGhostTimer;
struct Timer readyTimer;
struct Timer gameOverTimer;
struct Timer eatGhostAnimationTimer;
struct Timer pacmanDeathAnimationTimer;
struct Timer pacmanDeathAnimationDelayTimer;

int getScore()
{
    return score;
}

int getHighScore()
{
    return high_score;
}

void incrementScore(int value)
{
    score += value;

    if (score > high_score)
    {
        high_score = score;
    }
}

void decrementScore(int value)
{
    score -= value;
}

int getLives()
{
    return lives;
}

void decrementLives()
{
    lives--;
}

void initTimers()
{
    initTimer(&eatableGhostTimer, EATABLE_GHOST_DURATION);

    initTimer(&readyTimer, READY_DURATION);

    // TODO : initTimer(gameOverTimer, GAME_OVER_DURATION);

    initTimer(&eatGhostAnimationTimer, SCORE_GHOST_EATEN_DURATION);

    initTimer(&pacmanDeathAnimationTimer, PACMAN_DEATH_ANIMATION_DURATION);

    initTimer(&pacmanDeathAnimationDelayTimer, PACMAN_DEATH_ANIMATION_DELAY);
}

void initGame() {
    score = 0;
    lives = INITIAL_LIVES;
    roundNumber = 0;
    eatenDotsCount = 0;
    initTimers();
}

int getRound() {
    return roundNumber;
}
void nextRound(){
    roundNumber++;
}

int getEatenDotsCount() {
    return eatenDotsCount;
}
void incrementEatenDotsCount() {
    eatenDotsCount++;
}

int getInitialDotsCount() {
    return dotsCount;
}
void setInitialDotsCount(int value) {
    dotsCount = value;
}

