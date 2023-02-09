#ifndef PACMAN_H
#define PACMAN_H

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define GAME_TITLE "PacMan"
#define PATH_SPRITE_SHEET_IMAGE "../assets/img/pacman_sprites.bmp"
#define PATH_PLAY_BTN_IMAGE "../assets/img/play_btn.bmp"
#define WINDOW_SCREEN_WIDTH 700
#define WINDOW_SCREEN_HEIGHT 900

/**
 * VARIABLES
**/
int count = 0;
bool* pGameQuit = false;
SDL_Window* pWindow = NULL;
SDL_Surface* pSurfaceWindow = NULL;
SDL_Surface* pSurfacePacmanSpriteSheet = NULL;
SDL_Surface* pSurfacePlayButton = NULL;

/**
 * IMAGE : Spire-Sheets
**/
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

/**
 * IMAGE : Play button
**/
SDL_Rect imgPlayButton = {0, 0, 98, 28 };
SDL_Rect imgPlayButtonZoom = {200, 400, 300, 100 };

/**
 * FUNCTIONS
**/
void initSDL();
void loadMedia();

void displayMainMenu();
void handleMainMenuEvents();
bool isPointInPlayButton(int x, int y);

void startGameLoop();
bool handleGameEvents();
void draw();

void SDL_ExitWithError(const char *message);
void closeWindow();

#endif // PACMAN_H