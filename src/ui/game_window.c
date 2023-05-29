#include "game_window.h"

int count = 0;

bool pGameQuit = false, gamePause = false; // Fixed variable name

SDL_Rect imgMazeBlueCoins = {200, 3, 168, 216};
SDL_Rect imgMazeBlueCoinsZoom = {4, 4, 672, 864};

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

        if (!gamePause)
        {
            handleGameEvents();
            drawGame();
            SDL_UpdateWindowSurface(pWindow);
        } else
        {
            handlePauseEvents();
            // add here any extra bit of code for the pause
            // maybe add a delay to prevent the loop from
            // constatly being used
        }

        clock_t difference = clock() - before;
        int msec = difference * 1000 / CLOCKS_PER_SEC;

        if (delayInMs > msec)
            SDL_Delay(delayInMs - msec);

    }

    freeMaze();
    freeGhostList();
}

// This function exists to handle the game events while the game is paused
// Returns void, not really sure why handleGameEvents(); returns bool
void handlePauseEvents()
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

    if (keys[SDL_SCANCODE_P])
        gamePause = !gamePause;
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
    
    // Moved out of the event loop
    if (keys[SDL_SCANCODE_P])
        gamePause = !gamePause;

    handlePacmanEvents();
}

void drawGame()
{
    // TODO : Move maze display to maze file
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, false, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgMazeBlueCoins, pSurfaceWindow, &imgMazeBlueCoinsZoom);

    drawGhosts(count);

    drawPacman(count);
}
