//
// Created by Franck GUTMANN on 15/02/2023.
//

#ifndef PACMAN_VARIABLES_H
#define PACMAN_VARIABLES_H

#include <SDL.h>
#include <stdbool.h>

extern SDL_Window *pWindow;
extern SDL_Surface *pSurfaceWindow;
extern SDL_Surface *pSurfacePacmanSpriteSheet;
extern SDL_Surface *pSurfacePlayButton;

extern bool pGameQuit;

/**
 * IMAGE : Spire-Sheets
 **/
extern SDL_Rect imgMazeBlueCoins;
extern SDL_Rect imgMazeBlueCoinsZoom; // we zoom the maze x4 to fit the window

extern SDL_Rect imgPacmanTitle;
extern SDL_Rect imgPacmanTitlePosition;
extern SDL_Rect imgBlackBackground;

/**
 * IMAGE : Play button
 **/
extern SDL_Rect imgPlayButton;
extern SDL_Rect imgPlayButtonPosition;
extern SDL_Rect imgPlayButtonHover;

#endif // PACMAN_VARIABLES_H
