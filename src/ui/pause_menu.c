#include "pause_menu.h"

SDL_Rect imgPauseMenuOnSprite = {4, 81, 47, 7};

SDL_Rect imgPauseTitlePosition = {TOTAL_SCREEN_WIDTH / 3, 400, 180, 35};

SDL_Rect imgResumeButton = {89, 72, 71, 7};
SDL_Rect imgMainMenuButton = {140, 54, 47, 7};
int hoverImgMargin = 9;

SDL_Rect imgResumeButtonPosition = {TOTAL_SCREEN_WIDTH / 3, 400, 180, 35};
SDL_Rect imgMainMenuButtonPosition = {TOTAL_SCREEN_WIDTH / 3, 500, 180, 35};

bool isResumeButtonHovered = false;
bool isMainMenuButtonHovered = false;

void drawPauseMenu()
{

    // Title
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPauseMenuOnSprite, pSurfaceWindow, &imgPauseTitlePosition);

    // Resume button
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgResumeButton, pSurfaceWindow, &imgResumeButtonPosition);

    // Main menu button
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgMainMenuButton, pSurfaceWindow, &imgMainMenuButtonPosition);
}

void handlePauseMenuEvents()
{
}