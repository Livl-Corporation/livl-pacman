#include "pause_menu.h"

#define TITLE_W 47
#define TITLE_H 7
#define TITLE_UI_SCALE 4

SDL_Rect imgPauseMenuOnSprite = {
    4,
    81,
    TITLE_W,
    TITLE_H,
};
SDL_Rect imgPauseTitlePosition = {
    TOTAL_SCREEN_WIDTH / 3,
    300,
    TITLE_W *TITLE_UI_SCALE,
    TITLE_H *TITLE_UI_SCALE,
};

#define RESUME_BUTTON_W 71
#define RESUME_BUTTON_H 7

#define MAIN_MENU_BUTTON_W 47
#define MAIN_MENU_BUTTON_H 7

#define BUTTONS_UI_SCALE 3

// SPRITES
SDL_Rect imgResumeButton = {
    89,
    72,
    RESUME_BUTTON_W,
    RESUME_BUTTON_H,
};
SDL_Rect imgMainMenuButton = {
    140,
    54,
    MAIN_MENU_BUTTON_W,
    MAIN_MENU_BUTTON_H,
};
int hoverImgMargin = 9;

// POSITIONS
SDL_Rect imgResumeButtonPosition = {
    TOTAL_SCREEN_WIDTH / 2 - RESUME_BUTTON_W * BUTTONS_UI_SCALE / 2,
    450,
    RESUME_BUTTON_W *BUTTONS_UI_SCALE,
    RESUME_BUTTON_H *BUTTONS_UI_SCALE,
};
SDL_Rect imgMainMenuButtonPosition = {
    TOTAL_SCREEN_WIDTH / 2 - MAIN_MENU_BUTTON_W * BUTTONS_UI_SCALE / 2,
    400,
    MAIN_MENU_BUTTON_W *BUTTONS_UI_SCALE,
    MAIN_MENU_BUTTON_H *BUTTONS_UI_SCALE,
};

bool isResumeButtonHovered = false;
bool isMainMenuButtonHovered = false;

void drawPauseMenu()
{

    // Title
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPauseMenuOnSprite, pSurfaceWindow, &imgPauseTitlePosition);

    SDL_Rect resumeButton = imgResumeButton;
    if (isResumeButtonHovered)
    {
        resumeButton.y += hoverImgMargin;
    }

    // Resume button
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &resumeButton, pSurfaceWindow, &imgResumeButtonPosition);

    SDL_Rect mainMenuButton = imgMainMenuButton;
    if (isMainMenuButtonHovered)
    {
        mainMenuButton.y += hoverImgMargin;
    }

    // Main menu button
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &mainMenuButton, pSurfaceWindow, &imgMainMenuButtonPosition);
}

void handlePauseMenuEvents()
{

    int x = 0, y = 0;
    SDL_Event event;

    SDL_PollEvent(&event);
    SDL_GetMouseState(&x, &y);

    struct Position mousePosition = {x, y};

    isResumeButtonHovered = isPositionInRect(mousePosition, &imgResumeButtonPosition);

    isMainMenuButtonHovered = isPositionInRect(mousePosition, &imgMainMenuButtonPosition);
}