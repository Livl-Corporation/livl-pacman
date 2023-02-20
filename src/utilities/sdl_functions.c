#include "sdl_functions.h"

// TODO : To remove :
#define PATH_SPRITE_SHEET_PACMAN "../assets/img/pacman_sprites.bmp"

SDL_Window *pWindow = NULL;
SDL_Surface *pSurfaceWindow = NULL;
SDL_Surface *pSurfacePacmanSpriteSheet = NULL;
SDL_Surface *pSurfacePlayButton = NULL;

void initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation of the SDL");

    pWindow = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (pWindow == NULL)
        SDL_ExitWithError("Creation of the SDL window");

    pSurfaceWindow = SDL_GetWindowSurface(pWindow);
    if (pSurfaceWindow == NULL)
        SDL_ExitWithError("Creation of the SDL window surface");
}

void loadMedia()
{
    pSurfacePacmanSpriteSheet = SDL_LoadBMP(PATH_SPRITE_SHEET_PACMAN);
    if (pSurfacePacmanSpriteSheet == NULL)
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