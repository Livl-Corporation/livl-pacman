#include "pause_menu.h"

SDL_Rect imgPauseMenuOnSprite = {4, 81, 47, 7};

SDL_Rect imgPauseTitle = {TOTAL_SCREEN_WIDTH / 3, 400, 180, 35};

void drawPauseMenu()
{
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPauseMenuOnSprite, pSurfaceWindow, &imgPauseTitle);
}