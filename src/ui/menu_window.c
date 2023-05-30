#include "menu_window.h"

bool pMainMenuQuit = false;

SDL_Rect imgPacmanTitle = {0, 0, 190, 50 };
SDL_Rect imgPacmanTitleZoom = {20, 100, 500, 130 };
SDL_Rect imgBlackBackground = {0, 0, 0, 0 };

SDL_Rect imgPlayButton = {0, 0, 110, 30 };
SDL_Rect imgPlayButtonZoom = {TOTAL_SCREEN_WIDTH/5, 400, 290, 100 };
SDL_Rect imgPlayButtonHover = {0, 30, 110, 30 };
SDL_Rect imgPlayButtonHoverZoom = {TOTAL_SCREEN_WIDTH/5, 400, 290, 100 };

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


    SDL_SetColorKey(pSurfacePlayButton, true, 0);
    SDL_BlitScaled(pSurfacePlayButton, &imgPlayButton, pSurfaceWindow, &imgPlayButtonZoom);
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
                SDL_SetColorKey(pSurfacePlayButton, true, 0);
                if (isPointInPlayButton(x, y))
                {
                    SDL_BlitScaled(pSurfacePlayButton, &imgPlayButtonHover, pSurfaceWindow, &imgPlayButtonHoverZoom);
                }
                else
                {
                    SDL_BlitScaled(pSurfacePlayButton, &imgPlayButton, pSurfaceWindow, &imgPlayButtonZoom);
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