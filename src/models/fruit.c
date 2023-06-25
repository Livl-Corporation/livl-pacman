//
// Created by Franck GUTMANN on 16/06/2023.
//

#include "fruit.h"

SDL_Rect initialFruitPos = {122, 271, FRUIT_SIZE, FRUIT_SIZE};
SDL_Rect initialFruitScorePos = {177, 133, FRUIT_SCORE_W, FRUIT_SCORE_H};

int fruitPoints[] = {100, 300, 500, 700, 1000, 2000, 3000, 5000};
int fruitLevels[] = {1, 2, 3, 5, 7, 9, 11, 13};

SDL_Rect fruitsRects[FRUIT_COUNTS];
SDL_Rect fruitScoresRects[FRUIT_COUNTS];

int fruitLevel = 0;

SDL_Rect fruitUiPos;
SDL_Rect fruitScoreUiPos;

void initFruits()
{
    exportSprites(
        &initialFruitPos,
        fruitsRects,
        FRUIT_COUNTS,
        FRUIT_SIZE + FRUIT_X_SPACING,
        0);

    exportSprites(
        &initialFruitScorePos,
        fruitScoresRects,
        FRUIT_COUNTS,
        0,
        FRUIT_SCORE_H + FRUIT_SCORE_Y_SPACING);
    struct Position gridPos = getMazePositionOfElement(FRUIT, initialMaze);
    struct Position uiPos = gridPosToUiPos(gridPos);
    fruitUiPos = (SDL_Rect){
        uiPos.x,
        uiPos.y,
        CELL_SIZE,
        CELL_SIZE};
    fruitScoreUiPos = (SDL_Rect){
        uiPos.x - CELL_SIZE / 2 + FRUIT_SCORE_W / 2,
        uiPos.y + CELL_SIZE / 2 - FRUIT_SCORE_H,
        FRUIT_SCORE_W * FRUIT_SCORE_UI_SCALE,
        FRUIT_SCORE_H * FRUIT_SCORE_UI_SCALE};
}

int getFruitLevel(int round)
{
    int level = 0;
    for (int i = 0; i < FRUIT_COUNTS; i++)
    {
        if (round >= fruitLevels[i])
        {
            level = i;
        }
    }
    return level;
}

void handleFruitCollision()
{

    if (!fruitTimer.isRunning)
        return;

    stopTimer(&fruitTimer);

    playAudioWithChannel(audioFruit, CHANNEL_FRUIT);
    incrementScore(fruitPoints[fruitLevel]);

    resetTimer(&fruitScoreAnimationTimer);
    startTimer(&fruitScoreAnimationTimer);
}

void spawnFruit()
{
    fruitLevel = getFruitLevel(getRound());
    resetTimer(&fruitTimer);
    startTimer(&fruitTimer);
}

void drawFruit()
{
    if (fruitTimer.isRunning)
    {

        SDL_BlitScaled(
            pSurfacePacmanSpriteSheet,
            &fruitsRects[fruitLevel],
            pSurfaceWindow,
            &fruitUiPos);
    }

    if (fruitScoreAnimationTimer.isRunning)
    {
        SDL_BlitScaled(
            pSurfacePacmanSpriteSheet,
            &fruitScoresRects[fruitLevel],
            pSurfaceWindow,
            &fruitScoreUiPos);
    }
}

void resetFruit()
{
    stopTimer(&fruitTimer);
}