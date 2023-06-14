#include "game_window.h"

int frameCount = 0;
double delayInSec = 1.0 / GAME_SPEED;
Uint32 delayInMs = 0;

bool pGameQuit = false, isGamePause = false, isPauseMenuOpen = false;

SDL_Rect imgMazeOnSprite = {201, 4, 166, 214};
SDL_Rect imgMazeOnUi = {0, HEADER_SCREEN_HEIGHT, TOTAL_SCREEN_WIDTH, MAZE_SCREEN_HEIGHT};

SDL_Rect imgBlackHeaderOnSprite = {0, 0, 0, 0};
SDL_Rect imgBlackHeaderOnUi = {0, 0, TOTAL_SCREEN_WIDTH, HEADER_SCREEN_HEIGHT};

#define READY_W 46
#define READY_H 7
#define READY_UI_SCALE 3
SDL_Rect imgReadyOnSprite = {4, 63, READY_W, READY_H};

void startGameLoop()
{
    initMaze();

    initGhostList();

    spawnPacman();

    initGameInfoPanel();

    delayInMs = (Uint32)(delayInSec * 1000);
    startReadyLoop();

    while (!pGameQuit)
    {
        clock_t before = clock();
        frameCount++;

        SDL_FillRect(pSurfaceWindow, 0, 0); // Clears the window's surface before drawing the new frame

        if (isPauseMenuOpen)
        {
            drawPauseMenu();
            handlePauseMenuEvents();
        }
        else
        {
            drawHeader();
            drawGame();
            handleGameEvents();
        }

        SDL_UpdateWindowSurface(pWindow);
        delayToMaintainFrameRate(before, delayInMs);
    }

    freeMaze();
    freeGhostList();
}

void handleGameEvents()
{
    SDL_Event event;
    int numberOfKeyboardScancodes;
    const Uint8 *keys = SDL_GetKeyboardState(&numberOfKeyboardScancodes);

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
        setPause(true);
    if (keys[SDL_SCANCODE_ESCAPE])
        pGameQuit = true;

    handlePacmanEvents();
}

void startReadyLoop()
{
    isGamePause = true;

    Uint32 startTime = SDL_GetTicks();

    while (SDL_GetTicks() - startTime < TIME_START_GAME_READY)
    {
        clock_t before = clock();
        frameCount++;

        SDL_FillRect(pSurfaceWindow, 0, 0);

        drawGame();
        drawReadyImg();

        SDL_UpdateWindowSurface(pWindow);

        delayToMaintainFrameRate(before, delayInMs);
    }

    isGamePause = false;
}

void drawGame()
{
    drawMaze();
    drawGhosts();
    drawPacman();
    drawGameInfoPanel();
    drawCoins(frameCount);
    drawPacmanArrow();
    decreaseEatableGhostTimer();
}

void drawMaze()
{
    // TODO : Move maze display to maze file
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, false, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgMazeOnSprite, pSurfaceWindow, &imgMazeOnUi);
}

void drawReadyImg()
{
    struct Position position = getGridPosToUiPos((struct Position){8, 15});
    SDL_Rect imgReadyOnUi = {position.x, position.y, READY_W * READY_UI_SCALE, READY_H * READY_UI_SCALE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, false, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgReadyOnSprite, pSurfaceWindow, &imgReadyOnUi);
}

void drawHeader()
{
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, false, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgBlackHeaderOnSprite, pSurfaceWindow, &imgBlackHeaderOnUi);
}

void delayToMaintainFrameRate(clock_t before, Uint32 desiredDelayInMs)
{
    clock_t difference = clock() - before;
    int64_t milliseconds = (difference * 1000) / CLOCKS_PER_SEC;

    if (desiredDelayInMs > milliseconds)
        SDL_Delay(desiredDelayInMs - milliseconds);
}

void setPause(int isPaused)
{
    isGamePause = isPaused;
    isPauseMenuOpen = isPaused;
}