//
// Created by Franck GUTMANN on 27/05/2023.
//

#include <stdio.h>
#include "game.h"

int score = 0;
int high_score = 0;
int lives = INITIAL_LIVES;

struct Timer eatableGhostTimer;
struct Timer readyTimer;
struct Timer gameOverTimer;
struct Timer eatGhostAnimationTimer;
struct Timer pacmanDeathAnimationTimer;

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

    initTimer(&readyTimer, TIME_START_GAME_READY);

    // TODO : initTimer(gameOverTimer, GAME_OVER_DURATION);

    initTimer(&eatGhostAnimationTimer, SCORE_GHOST_EATEN_DURATION);

    initTimer(&pacmanDeathAnimationTimer, PACMAN_DEATH_ANIMATION_DURATION);
}
