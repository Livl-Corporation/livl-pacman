#include "menu_window.h"

void displayMainMenu()
{
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgBlackBackground, pSurfaceWindow, &imgBlackBackground);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPacmanTitle, pSurfaceWindow, &imgPacmanTitleZoom);


    SDL_SetColorKey(pSurfacePlayButton, true, 0);
    SDL_BlitScaled(pSurfacePlayButton, &imgPlayButton, pSurfaceWindow, &imgPlayButtonZoom);

    SDL_UpdateWindowSurface(pWindow);

    handleMainMenuEvents();
}

void handleMainMenuEvents()
{
    bool quit = false;
    int x = 0, y = 0;

    while (!quit) // Wait for an event
    {
        SDL_Event event;
        while (!quit && SDL_PollEvent(&event))
        {
            SDL_GetMouseState(&x, &y);
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (isPointInPlayButton(x, y))
                        startGameLoop();
                    break;
                case SDL_MOUSEMOTION:
                    if (isPointInPlayButton(x, y))
                    {
                        SDL_SetColorKey(pSurfacePlayButton, true, 0);
                        SDL_BlitScaled(pSurfacePlayButton, &imgPlayButtonHover, pSurfaceWindow, &imgPlayButtonHoverZoom);
                    }
                    else
                    {
                        SDL_SetColorKey(pSurfacePlayButton, true, 0);
                        SDL_BlitScaled(pSurfacePlayButton, &imgPlayButton, pSurfaceWindow, &imgPlayButtonZoom);
                    }
                    SDL_UpdateWindowSurface(pWindow);

                    break;
                default: break;
            }
        }
    }
}

bool isPointInPlayButton(int x, int y)
{
    return x >= imgPlayButtonZoom.x && x <= imgPlayButtonZoom.x + imgPlayButtonZoom.w
           && y >= imgPlayButtonZoom.y && y <= imgPlayButtonZoom.y + imgPlayButtonZoom.h;
}