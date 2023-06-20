//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "ghost.h"

struct Sprite *ghostList;

int ghostEaten = 0;
MazeElement ghostElementEaten = EMPTY;

SDL_Rect eatableGhostRect;

void initGhostList()
{

    ghostList = malloc(sizeof(struct Sprite) * GHOST_COUNT);

    for (int i = 0; i < GHOST_COUNT; i++)
    {
        ghostList[i].number = i;
        ghostList[i].uiPosition.x = 0;
        ghostList[i].uiPosition.y = 0;
        ghostList[i].gridPosition.x = 0;
        ghostList[i].gridPosition.y = 0;
        ghostList[i].ghostElement = i + '0';
        ghostList[i].direction = DIRECTION_RIGHT;

        // Sprites :
        ghostList[i].rects = malloc(sizeof(SDL_Rect) * DIRECTION_COUNT);

        SDL_Rect initialGhost = {
            GHOST_INITIAL_POS_X,
            GHOST_INITIAL_POS_Y + i * (GHOST_SIZE + GHOST_SPACING_Y),
            GHOST_SIZE, GHOST_SIZE};

        exportSprites(
            &initialGhost,
            ghostList[i].rects,
            DIRECTION_COUNT,
            2 * (GHOST_SIZE + GHOST_SPACING_X),
            0);
    }

    eatableGhostRect = (SDL_Rect){
        GHOST_INITIAL_POS_X,
        GHOST_INITIAL_POS_Y + 4 * (GHOST_SIZE + GHOST_SPACING_Y),
        GHOST_SIZE,
        GHOST_SIZE};
}

void spawnGhosts() {
    for (int i = 0; i < GHOST_COUNT; i++)
    {
        spawnGhost(i);
    }
}

void freeGhosts()
{
    for (int i = 0; i < GHOST_COUNT; i++)
    {
        free(ghostList[i].rects);
    }
    free(ghostList);
}

void spawnGhost(int ghostId)
{
    ghostList[ghostId].lastRect = ghostList[ghostId].rects[0];
    ghostList[ghostId].gridPosition = getInitialPositionOfElement(ghostList[ghostId].ghostElement);
    setMazeElementAt(ghostList[ghostId].gridPosition, ghostList[ghostId].ghostElement);
    ghostList[ghostId].uiPosition = gridPosToUiPos(ghostList[ghostId].gridPosition);
}

void drawGhosts()
{
    // Don't draw ghosts during delay after Pacman death animation
    if(pacmanDeathAnimationTimer.isRunning || (pacmanDeathAnimationTimer.isFinished && pacmanDeathAnimationDelayTimer.isRunning)) return;

    for (int i = 0; i < GHOST_COUNT; i++)
    {
        if (canBlitGhostInPausedGame(i))
            blitGhost(&ghostList[i], &ghostList[i].lastRect);
        else if (!isGamePause)
            updateGhost(&ghostList[i]);
    }
}

bool canBlitGhostInPausedGame(int ghostId)
{
    return ((isGamePause && !isScoreAnimationOnGhostEaten()) || (isScoreAnimationOnGhostEaten() && ghostList[ghostId].ghostElement != ghostElementEaten));
}

void updateGhost(struct Sprite *sprite)
{
    SDL_Rect ghost_in2;

    if (isGhostEatable())
    {
        ghost_in2 = eatableGhostRect;

        if (isGhostEatableRunningOut() && (frameCount / ANIMATION_SPEED / 2) % 2)
            ghost_in2.x += 2 * (GHOST_SIZE + GHOST_SPACING_X);
    }
    else
    {
        ghost_in2 = sprite->rects[sprite->direction];
    }

    // Animation
    if ((frameCount / ANIMATION_SPEED) % 2)
        ghost_in2.x += (GHOST_SIZE + GHOST_SPACING_X);

    sprite->lastRect = ghost_in2;

    blitGhost(sprite, &ghost_in2);
}

void blitGhost(struct Sprite *sprite, SDL_Rect *spritePos)
{
    SDL_Rect rect = {sprite->uiPosition.x, sprite->uiPosition.y, CELL_SIZE, CELL_SIZE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, spritePos, pSurfaceWindow, &rect);
}

void makeGhostsEatable()
{
    resetTimer(&eatableGhostTimer);
    startTimer(&eatableGhostTimer);
    ghostEaten = 0;
}

bool isGhostEatable()
{
    return eatableGhostTimer.isRunning;
}

bool isGhostEatableRunningOut()
{
    return eatableGhostTimer.count < EATABLE_GHOST_DURATION / 4;
}

int getEatenGhostScore(int ghostEaten)
{
    return pow(2, ghostEaten) * 100;
}