//
// Created by Julien on 09/02/2023.
//

#ifndef PACMAN_GAME_WINDOW_H
#define PACMAN_GAME_WINDOW_H

#include <stdbool.h>
#include <time.h>
#include <SDL.h>
#include "../models/maze.h"
#include "../utilities/console_handler.h"
#include "variables.h"
#include "models/pacman.h"
#include "models/position.h"
#include "models/ghost.h"
#include "ui/game_info_panel.h"
#include "ui/menu_window.h"

extern int frameCount;
extern bool isGamePause;
extern SDL_Rect imgMazeOnSprite;
extern SDL_Rect imgMazeOnUi;

void startGameLoop();
void startReadyLoop();
void delayToMaintainFrameRate(clock_t before, Uint32 desiredDelayInMs);

void handleGameEvents();

void drawGame();
void drawMaze();
void drawHeader();
void drawReadyImg();

#endif // PACMAN_GAME_WINDOW_H
