#include "pause_menu.h"

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

// SPRITES
SDL_Rect imgResumeButton = {
    140,
    54,
    RESUME_BUTTON_W,
    RESUME_BUTTON_H,
};
SDL_Rect imgMainMenuButton = {
    89,
    72,
    MAIN_MENU_BUTTON_W,
    MAIN_MENU_BUTTON_H,
};

// POSITIONS
SDL_Rect imgResumeButtonPosition = {
    TOTAL_SCREEN_WIDTH / 2 - RESUME_BUTTON_W * BUTTONS_UI_SCALE / 2,
    400,
    RESUME_BUTTON_W *BUTTONS_UI_SCALE,
    RESUME_BUTTON_H *BUTTONS_UI_SCALE,
};
SDL_Rect imgMainMenuButtonPosition = {
    TOTAL_SCREEN_WIDTH / 2 - MAIN_MENU_BUTTON_W * BUTTONS_UI_SCALE / 2,
    450,
    MAIN_MENU_BUTTON_W *BUTTONS_UI_SCALE,
    MAIN_MENU_BUTTON_H *BUTTONS_UI_SCALE,
};

bool isResumeButtonHovered = false;
bool isMainMenuButtonHovered = false;

void drawPauseMenu()
{

    // Title
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPauseMenuOnSprite, pSurfaceWindow, &imgPauseTitlePosition);

    // Resume button
    SDL_Rect resumeButton = imgResumeButton;
    if (isResumeButtonHovered)
    {
        resumeButton.y += BUTTONS_HOVER_SPACING;
    }

    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &resumeButton, pSurfaceWindow, &imgResumeButtonPosition);

    // Main menu button
    SDL_Rect mainMenuButton = imgMainMenuButton;
    if (isMainMenuButtonHovered)
    {
        mainMenuButton.y += BUTTONS_HOVER_SPACING;
    }

    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &mainMenuButton, pSurfaceWindow, &imgMainMenuButtonPosition);
}

void handlePauseMenuEvents()
{

    int numberOfKeyboardScancodes;
    const Uint8 *keys = SDL_GetKeyboardState(&numberOfKeyboardScancodes);

    if (keys[SDL_SCANCODE_L])
    {
        setPause(false);
        return;
    }

    if (keys[SDL_SCANCODE_ESCAPE])
    {
        pGameQuit = true;
        return;
    }

    int x = 0, y = 0;
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        SDL_GetMouseState(&x, &y);

        struct Position mousePosition = {x, y};

        isResumeButtonHovered = isPositionInRect(mousePosition, &imgResumeButtonPosition);

        isMainMenuButtonHovered = isPositionInRect(mousePosition, &imgMainMenuButtonPosition);

        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (isResumeButtonHovered)
            {
                setPause(false);
                return;
            }

            if (isMainMenuButtonHovered)
            {
                stopAudio(CHANNEL_PAUSE_BEAT);
                goBackToMenu();
                return;
            }

            break;
        default:
            break;
        }
    }
}