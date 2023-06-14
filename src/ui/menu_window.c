#include "menu_window.h"

bool pMainMenuQuit = false;

SDL_Rect imgPacmanTitle = {4, 4, 180, 46 };
SDL_Rect imgPacmanTitleZoom = {13, 100, 500, 130 };
SDL_Rect imgBlackBackground = {0, 0, 0, 0 };

SDL_Rect imgPlayButton = {89, 54, 46, 7 };
SDL_Rect imgPlayButtonZoom = {TOTAL_SCREEN_WIDTH/3, 400, 180, 35};
SDL_Rect imgPlayButtonHover = {89, 63, 46, 7};
SDL_Rect imgPlayButtonHoverZoom = {TOTAL_SCREEN_WIDTH/3, 400, 180, 35 };

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
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPlayButton, pSurfaceWindow, &imgPlayButtonZoom);
}

void handleMainMenuEvents()
{
    int x = 0, y = 0;
    SDL_Event event;
    while (!pMainMenuQuit && SDL_PollEvent(&event))
    {
        SDL_GetMouseState(&x, &y);
        switch (event.type)
        {
            case SDL_QUIT:
                pMainMenuQuit = true;
                break;
            case SDL_MOUSEBUTTONUP:
                if (isPointInPlayButton(x, y)) {
                    startGameLoop();
                    pMainMenuQuit = true;
                }
                break;
            case SDL_MOUSEMOTION:
                SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);
                if (isPointInPlayButton(x, y))
                {
                    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPlayButtonHover, pSurfaceWindow, &imgPlayButtonHoverZoom);
                }
                else
                {
                    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPlayButton, pSurfaceWindow, &imgPlayButtonZoom);
                }
                break;
            default: break;
        }
    }
}

bool isPointInPlayButton(int x, int y)
{
    return x >= imgPlayButtonZoom.x && x <= imgPlayButtonZoom.x + imgPlayButtonZoom.w
           && y >= imgPlayButtonZoom.y && y <= imgPlayButtonZoom.y + imgPlayButtonZoom.h;
}