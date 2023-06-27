//
// Created by Franck GUTMANN on 27/06/2023.
//

#include "arrow.h"

SDL_Rect arrowSprite = {4, 266, PACMAN_ARROW_SIZE, PACMAN_ARROW_SIZE};

void drawPacmanArrow()
{

    if (isGamePause)
        return;

    SDL_Rect newArrowSprite = getArrow(pacmanWishedDirection);

    struct Position arrowPos = {
            pacmanUIPos.x + ARROW_OFFSET,
            pacmanUIPos.y + ARROW_OFFSET,
    };

    updatePosition(&arrowPos, pacmanWishedDirection, PACMAN_ARROW_SPACING, DEFAULT_SPEED);

    struct SDL_Rect arrowPosSDL = {
            (int)arrowPos.x,
            (int)arrowPos.y,
            ARROW_DISPLAY_SIZE,
            ARROW_DISPLAY_SIZE,
    };

    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &newArrowSprite, pSurfaceWindow, &arrowPosSDL);
}

struct SDL_Rect getArrow(Direction direction)
{
    SDL_Rect arrow = arrowSprite;
    arrow.x += (int)direction * arrow.w;
    return arrow;
}