#include "game_window.h"

int frameCount = 0;

bool pGameQuit = false, isGamePause = false, isPauseMenuOpen = false;

SDL_Rect imgBlackHeaderOnSprite = {0, 0, 0, 0};
SDL_Rect imgBlackHeaderOnUi = {0, 0, TOTAL_SCREEN_WIDTH, HEADER_SCREEN_HEIGHT};

void startGame()
{
    initMaze();
    initGhostList();
    initPacmanSprites();
    initGameInfoPanel();
    initGame();
    initFruits();

    int dotsCount = getInitialElementAmount(BIG_COIN) + getInitialElementAmount(SMALL_COIN);
    setInitialDotsCount(dotsCount);

    spawnPacman();
    spawnGhosts();

    playAudioWithChannel(audioGameStart, CHANNEL_GAME_START);
    startReady(GAME_START_DURATION);

    while (!pGameQuit)
    {
        clock_t before = clock();
        frameCount++;

        SDL_FillRect(pSurfaceWindow, 0, 0); // Clears the window's surface before drawing the new frame

        if (isPauseMenuOpen)
        {
            drawPauseMenu();
            handlePauseMenuEvents();
            stopSirenOrPowerUpSound();
        }
        else
        {
            drawHeader();
            drawGame();
            handleGameEvents();

            if (readyTimer.isRunning) drawReady();

            playSirenOrPowerUpSound();
        }

        SDL_UpdateWindowSurface(pWindow);

        updateTimers();

        delayToMaintainFrameRate(before, DELAY_MS);
    }

    freeGame();
    freeAudios();
}

void resetGameWindow()
{
    pGameQuit = false;
    isGamePause = false;
    isPauseMenuOpen = false;
    frameCount = 0;
}

void endReady() {
    isGamePause = false;
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

void startReady(int duration)
{
    isGamePause = true;
    setTimerInitialCount(&readyTimer, duration);
    setTimerCallback(&readyTimer, endReady);
    resetTimer(&readyTimer);
    startTimer(&readyTimer);
}

void drawGame()
{
    if(nextRoundAnimationTimer.isRunning && nextRoundAnimationTimer.count < NEXT_ROUND_ANIMATION_DURATION/2)
    {
        if (nextRoundAnimationTimer.count % MAZE_BLINK_WHITE_BLUE_RATE) drawMaze(true);
        else drawMaze(false);

        drawPacman();
        return;
    }

    drawMaze(false);

    drawGameInfoPanel();
    drawCoins(frameCount);
    drawFruit();

    if(!gameOverTimer.isRunning) {
        drawGhosts();
        drawPacman();
        drawPacmanArrow();
    }
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