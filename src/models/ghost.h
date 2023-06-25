//
// Created by Franck GUTMANN on 23/02/2023.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <SDL.h>
#include "models/position.h"
#include "enums/direction.h"
#include "enums/ghost-mode.h"
#include "constants.h"
#include "maze.h"
#include "models/game.h"
#include "models/timer.h"
#include "../ui/game_window.h"

struct Ghost
{
    struct Position uiPosition;
    struct Position gridPosition;
    Direction direction;
    Direction nextDirection;
    SDL_Rect *rects;
    SDL_Rect lastRect;
    MazeElement ghostElement;
    struct Position targetTile;
};

void moveGhost(struct Ghost *sprite);

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

bool isGhostEatableRunningOut();

/**
 * Check if the ghost can be blit in paused game and when a pacman is eaten we only blit all the ghosts except the one who ate the pacman
 * @param ghostId : the ghost id
 * @return true if the ghost can be blit
 */
bool canBlitGhostInPausedGame(int ghostId);

int getEatenGhostScore(int ghostEaten);

void updateGhost(struct Ghost *sprite);

void blitGhost(struct Ghost *sprite, SDL_Rect *spritePos);

void onGhostGridPositionChanged(struct Ghost *sprite);

void setGhostTargetTile(struct Ghost *sprite, struct Position targetTile);

void selectNextGhostDirection(struct Ghost *sprite);

Direction getOppositeDirection(Direction direction);

int getDistance(struct Position pos1, struct Position pos2);

void teleportGhost(struct Ghost *sprite, MazeElement destination);

void setGhostMode(GhostMode mode);

GhostMode getGhostMode();

void eatGhost(MazeElement ghostElement);

int getGhostEatenCount();

void onGhostEatableTimerEnds();

#endif // PACMAN_GHOST_H
