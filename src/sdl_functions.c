#include "sdl_functions.h"
#include "pacman.h"

SDL_Rect imgMazeBlueCoins = {200, 3, 168, 216 };
SDL_Rect imgMazeBlueCoinsZoom = {4, 4, 672, 864 }; // we zoom the maze x4 to fit the window

SDL_Rect ghostRedEyesRight = {3, 123, 16, 16 };
SDL_Rect ghostRedEyesLeft = {37, 123, 16, 16 };
SDL_Rect ghostRedEyesDown = {105, 123, 16, 16 };
SDL_Rect ghostRedEyesUp = {71, 123, 16, 16 };
SDL_Rect ghostRedZoom = {34, 34, 32, 32 }; // we zoom the ghost x2

SDL_Rect imgPacmanTitle = {0, 0, 190, 50 };
SDL_Rect imgPacmanTitleZoom = {100, 100, 500, 130 };
SDL_Rect imgBlackBackground = {0, 0, 0, 0 };

SDL_Rect imgPlayButton = {0, 0, 110, 30 };
SDL_Rect imgPlayButtonZoom = {200, 400, 290, 100 };
SDL_Rect imgPlayButtonHover = {0, 30, 110, 30 };
SDL_Rect imgPlayButtonHoverZoom = {200, 400, 290, 100 };

SDL_Window* pWindow = NULL;
SDL_Surface* pSurfaceWindow = NULL;
SDL_Surface* pSurfacePacmanSpriteSheet = NULL;
SDL_Surface* pSurfacePlayButton = NULL;
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
    pSurfacePacmanSpriteSheet = SDL_LoadBMP(PATH_SPRITE_SHEET_PACMAN);
    if(pSurfacePacmanSpriteSheet == NULL)
        SDL_ExitWithError("Loading of the sprite-sheet");

    pSurfacePlayButton = SDL_LoadBMP(PATH_SPRITE_SHEET_PLAY_BTN);
    if (pSurfacePlayButton == NULL)
        SDL_ExitWithError("Loading of the button play");
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