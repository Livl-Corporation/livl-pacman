#include "pacman.h"

void initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation of the SDL");

    pWindow = SDL_CreateWindow(GAME_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_SCREEN_WIDTH,WINDOW_SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (pWindow == NULL)
        SDL_ExitWithError("Creation of the SDL window");

    pSurfaceWindow = SDL_GetWindowSurface(pWindow);
    if(pSurfaceWindow == NULL)
        SDL_ExitWithError("Creation of the SDL window surface");
}

void loadMedia()
{
    pSurfacePacmanSpriteSheet = SDL_LoadBMP(PATH_SPRITE_SHEET_IMAGE);
    if(pSurfacePacmanSpriteSheet == NULL)
        SDL_ExitWithError("Loading of the sprite-sheet");

    pSurfacePlayButton = SDL_LoadBMP(PATH_PLAY_BTN_IMAGE);
    if (pSurfacePlayButton == NULL)
        SDL_ExitWithError("Loading of the button play");
}

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
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    SDL_GetMouseState(&x, &y);
                    if (isPointInPlayButton(x, y))
                    {
                        startGameLoop();
                    }
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

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv)
{
    initSDL();

    loadMedia();

    displayMainMenu();

    closeWindow();

    return 0;
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERROR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void closeWindow()
{
    SDL_FreeSurface(pSurfacePacmanSpriteSheet);
    SDL_FreeSurface(pSurfacePlayButton);
    SDL_FreeSurface(pSurfaceWindow);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}