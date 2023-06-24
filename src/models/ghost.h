//
// Created by Franck GUTMANN on 23/02/2023.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <SDL.h>
#include "models/position.h"
#include "enums/direction.h"
#include "constants.h"
#include "maze.h"
#include "models/game.h"
#include "models/timer.h"
#include "../ui/game_window.h"

extern int ghostEaten;
/**
 * The ghost that has been eaten by pacman
 */
extern MazeElement ghostElementEaten;

struct Ghost
{
    int number;
    struct Position uiPosition;
    struct Position gridPosition;
    Direction direction;
    SDL_Rect *rects;
    SDL_Rect lastRect;
    MazeElement ghostElement;
};

void moveGhostInDirection(struct Ghost *sprite);


/**
 * Initialize the ghost list
 * <!> Must be called before any other ghost function
 */
void initGhostList();

void spawnGhosts();

/**
 * Place a ghost on his spawn point
 * @param ghostId
 */
void spawnGhost(int ghostId);

/**
 * Make all ghost movesafare
 */
void drawGhosts();

/**
 * Free the ghost list
 * <!> Must be called at the end of the game
 */
void freeGhosts();

/**
 * Make all ghost eatable
 */
void makeGhostsEatable();

bool isGhostEatable();

bool isGhostEatableRunningOut();

/**
 * Check if the ghost can be blit in paused game and when a pacman is eaten we only blit all the ghosts except the one who ate the pacman
 * @param ghostId : the ghost id
 * @return true if the ghost can be blit
 */
bool canBlitGhostInPausedGame(int ghostId);

int getEatenGhostScore(int ghostEaten);

// Private
void updateGhost(struct Ghost *sprite);
void blitGhost(struct Ghost *sprite, SDL_Rect *spritePos);

#endif // PACMAN_GHOST_H
