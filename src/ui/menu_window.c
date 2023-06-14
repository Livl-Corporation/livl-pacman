#include "menu_window.h"

bool pMainMenuQuit = false;

#define PACMAN_TITLE_W 180
#define PACMAN_TITLE_H 46
#define PACMAN_TITLE_SCALE 3
SDL_Rect imgPacmanTitle = {4, 4, PACMAN_TITLE_W, PACMAN_TITLE_H};
SDL_Rect imgPacmanTitlePosition = {13, 100, PACMAN_TITLE_W *PACMAN_TITLE_SCALE, PACMAN_TITLE_H *PACMAN_TITLE_SCALE};
SDL_Rect imgBlackBackground = {0, 0, 0, 0};

#define PLAY_W 46
#define PLAY_H 7
#define PLAY_UI_SCALE 3
SDL_Rect imgPlayButton = {89, 54, PLAY_W, PLAY_H};
int playButtonHoverMargin = 9;

SDL_Rect imgPlayButtonPosition = {TOTAL_SCREEN_WIDTH / 3, 400, PLAY_W *PLAY_UI_SCALE, PLAY_H *PLAY_UI_SCALE};

bool isPlayButtonHovered = false;

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
                startGameLoop();
                pMainMenuQuit = true;
            }
            break;
        case SDL_MOUSEMOTION:
            SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);

            SDL_Rect playButton = imgPlayButton;
            if (isPlayButtonHovered)
            {
                playButton.y += playButtonHoverMargin;
            }

            SDL_BlitScaled(pSurfacePacmanSpriteSheet, &playButton, pSurfaceWindow, &imgPlayButtonPosition);

            break;
        default:
            break;
        }
    }
}