#ifndef PACMAN_H
#define PACMAN_H

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define GAME_TITLE "PacMan"
#define PATH_SPRITE_SHEET_PACMAN "../assets/img/pacman_sprites.bmp"
#define PATH_SPRITE_SHEET_PLAY_BTN "../assets/img/play_btn.bmp"
#define WINDOW_SCREEN_WIDTH 700
#define WINDOW_SCREEN_HEIGHT 900

/**
 * VARIABLES
**/
extern int count;
extern bool* pGameQuit;
extern SDL_Window* pWindow;
extern SDL_Surface* pSurfaceWindow;
extern SDL_Surface* pSurfacePacmanSpriteSheet;
extern SDL_Surface* pSurfacePlayButton;

/**
 * IMAGE : Spire-Sheets
**/
extern SDL_Rect imgMazeBlueCoins;
extern SDL_Rect imgMazeBlueCoinsZoom;

extern SDL_Rect ghostRedEyesRight;
extern SDL_Rect ghostRedEyesLeft;
extern SDL_Rect ghostRedEyesDown;
extern SDL_Rect ghostRedEyesUp;
extern SDL_Rect ghostRedZoom;

extern SDL_Rect imgPacmanTitle;
extern SDL_Rect imgPacmanTitleZoom;
extern SDL_Rect imgBlackBackground;

/**
 * IMAGE : Play button
**/
extern SDL_Rect imgPlayButton;
extern SDL_Rect imgPlayButtonZoom;
extern SDL_Rect imgPlayButtonHover;
extern SDL_Rect imgPlayButtonHoverZoom;


#endif // PACMAN_H