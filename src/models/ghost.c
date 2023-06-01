//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "ghost.h"

struct Sprite *ghostList;

int eatableGhostTimer = 0;

int isGhostEatable() {
    return eatableGhostTimer > 0;
}

void initGhostList() {

    // TODO : [sprite refactor] use this code also for pacman

    // Malloc ghost list
    ghostList = malloc(sizeof(struct Sprite) * GHOST_COUNT);

    for (int i = 0; i < GHOST_COUNT; i++) {
        ghostList[i].number = i;
        ghostList[i].uiPosition.x = 0;
        ghostList[i].uiPosition.y = 0;
        ghostList[i].gridPosition.x = 0;
        ghostList[i].gridPosition.y = 0;

        // Sprites :
        ghostList[i].rects = malloc(sizeof(SDL_Rect) * DIRECTION_COUNT);

        for (int j = 0; j < DIRECTION_COUNT; j++) {
            SDL_Rect rect = {0, 0, 0, 0};

            rect.x = GHOST_INITIAL_POS_X + j*2*(GHOST_SIZE+GHOST_SPACING_X);
            rect.y = GHOST_INITIAL_POS_Y + i*(GHOST_SIZE+GHOST_SPACING_Y);
            rect.w = GHOST_SIZE;
            rect.h = GHOST_SIZE;

            ghostList[i].rects[j] = rect;
        }

        spawnGhost(i);

    }

}

void freeGhostList() {
    for (int i = 0; i < GHOST_COUNT; i++) {
        free(ghostList[i].rects);
    }
    free(ghostList);
}

void spawnGhost(int ghostId) {
    ghostList[ghostId].gridPosition = getInitialPositionOfElement(ghostId+'0');
    ghostList[ghostId].uiPosition = getGridPosToUiPos(ghostList[ghostId].gridPosition);
}

void drawGhosts(int count) {
    for (int i = 0; i < GHOST_COUNT; i++) {
        updateGhost(&ghostList[i], count);
    }
}

void updateGhost(struct Sprite *sprite, int count) {
    
    // Animation
    SDL_Rect ghost_in2 = sprite->rects[sprite->direction];
    if ((count / ANIMATION_SPEED) % 2)
        ghost_in2.x += 17;

    blitGhost(sprite, &ghost_in2);

}

void blitGhost(struct Sprite *sprite, SDL_Rect *spritePos) {
    SDL_Rect rect = {sprite->uiPosition.x, sprite->uiPosition.y, CELL_SIZE, CELL_SIZE};

    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, spritePos, pSurfaceWindow, &rect);
}

void makeGhostsEatable() {
    eatableGhostTimer = EATABLE_GHOST_DURATION;
}

void decreaseEatableGhostTimer() {
    if (eatableGhostTimer > 0)
        eatableGhostTimer--;
}