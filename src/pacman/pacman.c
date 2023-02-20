//
// Created by Franck GUTMANN on 15/02/2023.
//

#include "pacman.h"

SDL_Rect pacmanRight1 = {20, 90, 14, 14};
SDL_Rect pacmanRight2 = {34, 90, 14, 14};
SDL_Rect pacmanLeft1 = {48, 90, 14, 14};
SDL_Rect pacmanLeft2 = {62, 90, 14, 14};
SDL_Rect pacmanUp1 = {76, 90, 14, 14};
SDL_Rect pacmanUp2 = {93, 90, 14, 14};
SDL_Rect pacmanDown1 = {110, 90, 14, 14};
SDL_Rect pacmanDown2 = {127, 90, 14, 14};

void drawPacman(struct Position position)
{
    SDL_Rect rect = {position.x, position.y, CELL_SIZE, CELL_SIZE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);

    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &pacmanLeft1, pSurfaceWindow, &rect);
}