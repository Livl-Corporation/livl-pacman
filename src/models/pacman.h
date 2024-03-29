//
// Created by Franck GUTMANN on 15/02/2023.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include <SDL.h>
#include "utilities/sdl_functions.h"
#include "ui/variables.h"
#include "models/position.h"
#include "constants.h"
#include "enums/direction.h"
#include "models/maze.h"
#include "models/game.h"
#include "models/ghosts/ghost.h"
#include "../ui/game_window.h"
#include "models/fruit.h"
#include "speed.h"
#include "models/audio.h"

extern struct Position pacmanUIPos;
extern Direction pacmanWishedDirection;
extern Direction pacmanDirection;

void initPacmanSprites();

/**
 * Initialize pacman position at his spawn point
 * <!> This function must be called at least once before any other pacman function
 */
void spawnPacman();

/**
 * Handle user input
 */
void handlePacmanEvents();

/**
 * Calculate, validate, update and draw pacman position
 */
void drawPacman();

bool shouldSkipPacmanDrawOnGamePause();

void drawPacmanDeathAnimation();

bool shouldSkipPacmanDrawOnDeathTimer();

bool shouldChangeDirection();

int getPacmanAnimation();

SDL_Rect getPacmanSprite(int pacmanAnimation);

void pacmanBlit(SDL_Rect srcRect);

int calculatePacmanDeathAnimationIndex();

/**
 * Perform action when pacman has moved in grid
 * @return pacman position in UI
 */
struct Position onPacmanGridMove(struct Position *pacmanUiPos);

/**
 * Do the logic by checking if pacman eat a ghost either a ghost ate the pacman
 * @param ghostElement : the ghost that enters in contact with the pacman
 */
void handleGhostCollision(MazeElement ghostElement);

void killPacman();

void pacmanBlit(SDL_Rect srcRect);

struct Position teleportPacman(MazeElement teleporter);

void startPacmanDeathAnimation();

void endPacmanDeathDelay();

void endPacmanDeathAnimation();

void afterPacmanDeath();

void handleCoinCollision();

#endif // PACMAN_PACMAN_H
