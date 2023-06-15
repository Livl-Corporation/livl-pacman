#include "sdl_functions.h"

SDL_Window *pWindow = NULL;
SDL_Surface *pSurfaceWindow = NULL;
SDL_Surface *pSurfacePacmanSpriteSheet = NULL;
SDL_Surface *pSurfacePlayButton = NULL;

void initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation of the SDL");

    pWindow = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TOTAL_SCREEN_WIDTH, TOTAL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
}

void SDL_ExitWithError(const char *message)
{
    ConsoleHandlerDisplayError("%s > %s", message, SDL_GetError());
    closeWindow();
    exit(EXIT_FAILURE);
}

void closeWindow()
{
    ConsoleHandlerDisplayMessage("Freeing SDL Surfaces and Window.");
    SDL_FreeSurface(pSurfacePacmanSpriteSheet);
    SDL_FreeSurface(pSurfacePlayButton);
    SDL_FreeSurface(pSurfaceWindow);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}

int isPositionInRect(struct Position position, SDL_Rect *rect)
{
    return position.x >= rect->x && position.x <= rect->x + rect->w && position.y >= rect->y && position.y <= rect->y + rect->h;
}

void exportSprites(SDL_Rect *srcRect, SDL_Rect *destRect, int count, int xStep, int yStep)
{
    for (int i = 0; i < count; i++)
    {
        destRect[i].x = srcRect->x + i * xStep;
        destRect[i].y = srcRect->y + i * yStep;
        destRect[i].w = srcRect->w;
        destRect[i].h = srcRect->h;
    }
}
