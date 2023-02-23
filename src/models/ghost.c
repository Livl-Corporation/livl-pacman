//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "ghost.h"

SDL_Rect ghostRedRight;
SDL_Rect ghostRedLeft;
SDL_Rect ghostRedDown;
SDL_Rect ghostRedUp;

SDL_Rect ghostRoseRight;
SDL_Rect ghostRoseLeft;
SDL_Rect ghostRoseDown;
SDL_Rect ghostRoseUp;

SDL_Rect ghostTealRight;
SDL_Rect ghostTealLeft;
SDL_Rect ghostTealDown;
SDL_Rect ghostTealUp;

SDL_Rect ghostOrangeRight;
SDL_Rect ghostOrangeLeft;
SDL_Rect ghostOrangeDown;
SDL_Rect ghostOrangeUp;

struct Ghost *ghostList;

void initGhostList() {

    // Malloc ghost list
    ghostList = malloc(sizeof(struct Ghost) * GHOST_COUNT);

    for (int i = 0; i < GHOST_COUNT; i++) {
        ghostList[i].number = i;
        ghostList[i].uiPosition.x = 0;
        ghostList[i].uiPosition.y = 0;
        ghostList[i].gridPosition.x = 0;
        ghostList[i].gridPosition.y = 0;

        // Sprites :
        ghostList[i].spritePos = malloc(sizeof(SDL_Rect)*DIRECTION_COUNT);

    }

}

