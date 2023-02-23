//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "ghost.h"

struct Sprite *ghostList;

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
        ghostList[i].spritePos = malloc(sizeof(SDL_Rect));

        for (int j = 0; j < DIRECTION_COUNT; j++) {
            ghostList[i].spritePos[j].x = j*2*(GHOST_SIZE+GHOST_SPACING_X);
            ghostList[i].spritePos[j].y = i*(GHOST_SIZE+GHOST_SPACING_Y);
            ghostList[i].spritePos[j].w = GHOST_SIZE;
            ghostList[i].spritePos[j].h = GHOST_SIZE;
        }

        spawnGhost(i);

    }

}

void freeGhostList() {
    for (int i = 0; i < GHOST_COUNT; i++) {
        free(ghostList[i].spritePos);
    }
    free(ghostList);
}

void spawnGhost(int ghostId) {
    ghostList[ghostId].gridPosition = getInitialPositionOfElement(ghostId);
    ghostList[ghostId].uiPosition = gridPosToUiPos(ghostList[ghostId].gridPosition);
}

void drawGhosts(int count) {
    for (int i = 0; i < GHOST_COUNT; i++) {
        updateGhost(ghostList[i], count);
    }
}

void updateGhost(struct Sprite ghost, int count) {



}

void blitGhost(struct Sprite ghost, SDL_Rect *spritePos) {
    SDL_Rect rect = {ghost.uiPosition.x, ghost.uiPosition.y, CELL_SIZE, CELL_SIZE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, spritePos, pSurfaceWindow, &rect);
}