#include "menu_window.h"

bool pMainMenuQuit = false;

SDL_Rect imgPacmanTitle = {4, 4, PACMAN_TITLE_W, PACMAN_TITLE_H};
SDL_Rect imgPacmanTitlePosition = {
    TOTAL_SCREEN_WIDTH / 2 - PACMAN_TITLE_W * PACMAN_TITLE_UI_SCALE / 2,
    PACMAN_TITLE_UI_Y,
    PACMAN_TITLE_W *PACMAN_TITLE_UI_SCALE,
    PACMAN_TITLE_H *PACMAN_TITLE_UI_SCALE,
};

SDL_Rect imgPlayButton = {89, 54, PLAY_W, PLAY_H};
SDL_Rect imgPlayButtonPosition = {
    TOTAL_SCREEN_WIDTH / 2 - PLAY_W * PLAY_UI_SCALE / 2,
    PLAY_UI_Y,
    PLAY_W *PLAY_UI_SCALE,
    PLAY_H *PLAY_UI_SCALE,
};

bool isPlayButtonHovered = false;

SDL_Rect imgBlackBackground = {0, 0, 0, 0};

void startMenu()
{
    SDL_FillRect(pSurfaceWindow, 0, 0); // Clears the window's surface before drawing the new frame
    drawMainMenu();

    volumeAudio(audioPacmanDrill, SDL_MIX_MAXVOLUME/4);
    playAudioWithChannelLoop(audioPacmanDrill, CHANNEL_PACMAN_DRILL);

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
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPacmanTitle, pSurfaceWindow, &imgPacmanTitlePosition);

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
                stopAudio(CHANNEL_PACMAN_DRILL);
                startGame();
                pMainMenuQuit = true;
            }
            break;
        case SDL_MOUSEMOTION:
            SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);

            SDL_Rect playButton = imgPlayButton;
            if (isPlayButtonHovered)
            {
                playButton.y += PLAY_HOVER_SPACING;
            }

            SDL_BlitScaled(pSurfacePacmanSpriteSheet, &playButton, pSurfaceWindow, &imgPlayButtonPosition);

            break;
        default:
            break;
        }
    }
}