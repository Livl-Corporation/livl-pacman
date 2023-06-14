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
#include "models/sprite.h"
#include "../ui/game_window.h"

extern int ghostEaten;
/**
 * The ghost that has been eaten by pacman
 */
extern MazeElement ghostElementEaten;

/**
 * Initialize the ghost list
 * <!> Must be called before any other ghost function
 */
void initGhostList();

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
void freeGhostList();

/**
 * Make all ghost eatable
 */
void makeGhostsEatable();

int isGhostEatable();

int isGhostEatableRunningOut();

void decreaseEatableGhostTimer();

/**
 * Check if the ghost can be blit in paused game and when a pacman is eaten we only blit all the ghosts except the one who ate the pacman
 * @param ghostId : the ghost id
 * @return true if the ghost can be blit
 */
bool canBlitGhostInPausedGame(int ghostId);

int getEatenGhostScore(int ghostEaten);

// Private
void updateGhost(struct Sprite *sprite);
void blitGhost(struct Sprite *sprite, SDL_Rect *spritePos);

#endif // PACMAN_GHOST_H
