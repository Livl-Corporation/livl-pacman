#include "game_window.h"

int count = 0;

bool pGameQuit = false;

SDL_Rect imgMazeBlueCoins = {200, 3, 168, 216};
SDL_Rect imgMazeBlueCoinsZoom = {4, 4, 672, 864};

SDL_Rect ghostRedEyesRight = {3, 123, 16, 16};
SDL_Rect ghostRedEyesLeft = {37, 123, 16, 16};
SDL_Rect ghostRedEyesDown = {105, 123, 16, 16};
SDL_Rect ghostRedEyesUp = {71, 123, 16, 16};
SDL_Rect ghostRedZoom = {34, 34, 36, 36};

void startGameLoop()
{
    initMaze();

    spawnPacman();

    while (!pGameQuit)
    {
        handleGameEvents();

        drawGame();

        SDL_Delay((1/GAME_SPEED)*1000);

        SDL_UpdateWindowSurface(pWindow);
    }

    freeMaze();
}

// This function should trigger all required events handling
bool handleGameEvents()
{
    SDL_Event event;

    while (!pGameQuit && SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            pGameQuit = true;
            break;
        }
    }

    int numberOfKeyboardScancodes;
    const Uint8 *keys = SDL_GetKeyboardState(&numberOfKeyboardScancodes);

    if (keys[SDL_SCANCODE_ESCAPE])
        pGameQuit = true;

    handlePacmanEvents();
}

void drawGame()
{
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, false, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgMazeBlueCoins, pSurfaceWindow, &imgMazeBlueCoinsZoom);

    SDL_Rect *newGhost = NULL;
    switch (count / 128)
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

    count = (count + 1) % (512);

    SDL_Rect ghost_in2 = *newGhost;
    if ((count / ANIMATION_SPEED) % 2)
        ghost_in2.x += 17;

    SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &ghost_in2, pSurfaceWindow, &ghostRedZoom);

    drawPacman(count);
}