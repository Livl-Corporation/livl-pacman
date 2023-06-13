#include "menu_window.h"

bool pMainMenuQuit = false;

SDL_Rect imgPacmanTitle = {4, 4, 180, 46};
SDL_Rect imgPacmanTitleZoom = {13, 100, 500, 130};
SDL_Rect imgBlackBackground = {0, 0, 0, 0};

SDL_Rect imgPlayButton = {89, 54, 46, 7};
int playButtonHoverMargin = 9;

SDL_Rect imgPlayButtonPosition = {TOTAL_SCREEN_WIDTH / 3, 400, 180, 35};

bool isPlayButtonHovered = false;

void startMainMenuLoop()
{
    drawMainMenu();

    while (!pMainMenuQuit)
    {
        handleMainMenuEvents();
        SDL_UpdateWindowSurface(pWindow);
    }
}

void drawMainMenu()
{
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgBlackBackground, pSurfaceWindow, &imgBlackBackground);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPacmanTitle, pSurfaceWindow, &imgPacmanTitleZoom);

    SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPlayButton, pSurfaceWindow, &imgPlayButtonPosition);
}

void handleMainMenuEvents()
{
    int x = 0, y = 0;
    SDL_Event event;
    while (!pMainMenuQuit && SDL_PollEvent(&event))
    {

        SDL_GetMouseState(&x, &y);

        isPlayButtonHovered = isPositionInRect(
            (struct Position){
                x,
                y,
            },
            &imgPlayButtonPosition);

        switch (event.type)
        {
        case SDL_QUIT:
            pMainMenuQuit = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if (isPlayButtonHovered)
            {
                startGameLoop();
                pMainMenuQuit = true;
            }
            break;
        case SDL_MOUSEMOTION:
            SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);

            SDL_Rect playButton = imgPlayButtonPosition;
            if (isPlayButtonHovered)
            {
                playButton.y += playButtonHoverMargin;
            }

            SDL_BlitScaled(pSurfacePacmanSpriteSheet, &playButton, pSurfaceWindow, &imgPlayButtonPosition);

            break;
        default:
            break;
        }
    }
}