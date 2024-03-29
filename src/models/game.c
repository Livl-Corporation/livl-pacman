//
// Created by Franck GUTMANN on 27/05/2023.
//

#include "game.h"

int score = 0;
int high_score = 0;
int lives = INITIAL_LIVES;

int roundNumber = 1;
int dotsCount = 0;
int eatenDotsCount = 0;

struct Timer eatableGhostTimer;
struct Timer readyTimer;
struct Timer gameOverTimer;
struct Timer eatGhostAnimationTimer;
struct Timer pacmanDeathAnimationTimer;
struct Timer pacmanDeathAnimationDelayTimer;
struct Timer fruitTimer;
struct Timer fruitScoreAnimationTimer;
struct Timer nextRoundAnimationTimer;
struct Timer ghostModeTimer;

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

int getLives()
{
    return lives;
}

void decrementLives()
{
    lives--;
}

void afterGameOverAnimation()
{
    goBackToMenu();
}

void initTimers()
{
    initTimer(&eatableGhostTimer, EATABLE_GHOST_DURATION);
    setTimerRunCondition(&eatableGhostTimer, &isGameRunning);

    initTimer(&readyTimer, READY_DURATION);

    initTimer(&gameOverTimer, GAME_OVER_DURATION);

    initTimer(&eatGhostAnimationTimer, SCORE_GHOST_EATEN_DURATION);

    initTimer(&pacmanDeathAnimationTimer, PACMAN_DEATH_ANIMATION_DURATION);

    initTimer(&pacmanDeathAnimationDelayTimer, PACMAN_DEATH_ANIMATION_DELAY);

    initTimer(&fruitTimer, FRUIT_APPEAR_DURATION);
    setTimerRunCondition(&fruitTimer, &isGameRunning);

    initTimer(&fruitScoreAnimationTimer, FRUIT_SCORE_DISPLAY_DURATION);
    setTimerRunCondition(&fruitScoreAnimationTimer, &isGameRunning);

    initTimer(&nextRoundAnimationTimer, NEXT_ROUND_ANIMATION_DURATION);

    initTimer(&ghostModeTimer, 0);
    setTimerRunCondition(&ghostModeTimer, &isGameRunning);

}

void initGame() {
    score = 0;
    lives = INITIAL_LIVES;
    roundNumber = 1;
    eatenDotsCount = 0;
    initTimers();
}

int getRound() {
    return roundNumber;
}
void nextRound(){
    roundNumber++;
    startNextRoundAnimation();
    stopEyeSound();
}

void startNextRoundAnimation()
{
    isGamePause = true;
    setTimerCallback(&nextRoundAnimationTimer, endNextRoundAnimation);
    resetTimer(&nextRoundAnimationTimer);
    startTimer(&nextRoundAnimationTimer);
}

void endNextRoundAnimation()
{
    refillCoins();
    resetEatenDotsCount();
    spawnPacman();
    spawnGhosts();
    startReady(READY_DURATION);
}

int getEatenDotsCount() {
    return eatenDotsCount;
}

void incrementEatenDotsCount() {
    eatenDotsCount++;
}

void resetEatenDotsCount() {
    eatenDotsCount = 0;
}

int getInitialDotsCount() {
    return dotsCount;
}
void setInitialDotsCount(int value) {
    dotsCount = value;
}

void freeGame()
{
    resetGameWindow();
    clearTimers();
    freeMaze();
    freeGhosts();
}

void goBackToMenu()
{
    freeGame();
    startMenu();
}