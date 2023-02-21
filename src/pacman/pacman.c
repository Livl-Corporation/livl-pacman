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

struct Position pacmanPos = {34, 50};

Direction pacmanDirection = DIRECTION_RIGHT;

void handlePacmanEvents()
{

    int numberOfKeyboardScancodes;
    const Uint8 *keys = SDL_GetKeyboardState(&numberOfKeyboardScancodes);

    if (keys[SDL_SCANCODE_LEFT])
        pacmanDirection = DIRECTION_LEFT;
    if (keys[SDL_SCANCODE_RIGHT])
        pacmanDirection = DIRECTION_RIGHT;
    if (keys[SDL_SCANCODE_UP])
        pacmanDirection = DIRECTION_UP;
    if (keys[SDL_SCANCODE_DOWN])
        pacmanDirection = DIRECTION_DOWN;
}

void drawPacman(int count)
{

    SDL_Rect *newPacman = NULL;

    int pacmanAnimation = (count / 4) % 2;

    switch (pacmanDirection)
    {
    case DIRECTION_RIGHT:
        newPacman = (pacmanAnimation == 0) ? &pacmanRight1 : &pacmanRight2;
        pacmanPos.x++;
        break;
    case DIRECTION_LEFT:
        newPacman = (pacmanAnimation == 0) ? &pacmanLeft1 : &pacmanLeft2;
        pacmanPos.x--;
        break;
    case DIRECTION_UP:
        newPacman = (pacmanAnimation == 0) ? &pacmanUp1 : &pacmanUp2;
        pacmanPos.y--;
        break;
    case DIRECTION_DOWN:
        newPacman = (pacmanAnimation == 0) ? &pacmanDown1 : &pacmanDown2;
        pacmanPos.y++;
        break;
    }

    SDL_Rect rect = {pacmanPos.x, pacmanPos.y, CELL_SIZE, CELL_SIZE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, newPacman, pSurfaceWindow, &rect);
}