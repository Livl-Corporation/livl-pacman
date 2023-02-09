#include "pacman_window.h"
#include "pacman.h"

int count = 0;
bool* pGameQuit = false;

bool handleGameEvents()
{
    SDL_Event event;
    while (!pGameQuit && SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *pGameQuit = true;
                break;
        }
    }

    int numberOfKeyboardScancodes;
    const Uint8* keys = SDL_GetKeyboardState(&numberOfKeyboardScancodes);

    if (keys[SDL_SCANCODE_ESCAPE])
        *pGameQuit = true;
    if (keys[SDL_SCANCODE_LEFT])
        SDL_Log("LEFT");
    if (keys[SDL_SCANCODE_RIGHT])
        SDL_Log("RIGHT");
    if (keys[SDL_SCANCODE_UP])
        SDL_Log("UP");
    if (keys[SDL_SCANCODE_DOWN])
        SDL_Log("DOWN");
}


void startGameLoop()
{
    while (!pGameQuit)
    {
        handleGameEvents();

        draw();

        SDL_Delay(20); // ~50 fps use SDL_GetTicks64() pour plus de precision

        SDL_UpdateWindowSurface(pWindow);
    }
}

void draw()
{
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, false, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgMazeBlueCoins, pSurfaceWindow, &imgMazeBlueCoinsZoom);

    SDL_Rect* newGhost = NULL;
    switch (count/128)
    {
        case 0:
            newGhost = &(ghostRedEyesRight);
            ghostRedZoom.x++;
            break;
        case 1:
            newGhost = &(ghostRedEyesDown);
            ghostRedZoom.y++;
            break;
        case 2:
            newGhost = &(ghostRedEyesLeft);
            ghostRedZoom.x--;
            break;
        case 3:
            newGhost = &(ghostRedEyesUp);
            ghostRedZoom.y--;
            break;
    }
    count =(count+1)%(512);

    SDL_Rect ghost_in2 = *newGhost;
    if ((count/4)%2)
        ghost_in2.x += 17;

    SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &ghost_in2, pSurfaceWindow, &ghostRedZoom);
}