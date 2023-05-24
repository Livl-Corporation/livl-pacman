#include "game_window.h"

int count = 0;

bool pGameQuit = false;

SDL_Rect imgMazeBlueWithoutCoins = {370, 4, 166, 215};
SDL_Rect imgMazeBlueWithoutCoinsZoom = {0, 0, WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT};

void startGameLoop()
{
    initMaze();

    initGhostList();

    spawnPacman();

    double delayInSec = 1.0 / GAME_SPEED;
    Uint32 delayInMs = (delayInSec * 1000);

    while (!pGameQuit)
    {
        clock_t before = clock();

        count = (count + 1) % (512);

        handleGameEvents();

        drawGame();

        SDL_UpdateWindowSurface(pWindow);

        clock_t difference = clock() - before;
        int msec = difference * 1000 / CLOCKS_PER_SEC;

        if (delayInMs > msec)
            SDL_Delay(delayInMs - msec);

    }

    freeMaze();
    freeGhostList();
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
    // TODO : Move maze display to maze file
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, false, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgMazeBlueWithoutCoins, pSurfaceWindow, &imgMazeBlueWithoutCoinsZoom);

    drawGhosts(count);

    drawPacman(count);

    fillMazeWithCoins();
}