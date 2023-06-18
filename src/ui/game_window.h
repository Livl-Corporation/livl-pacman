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
#include "models/game.h"
#include "ui/game_info_panel.h"
#include "ui/menu_window.h"
#include "ui/pause_menu.h"
#include "models/fruit.h"
#include "models/audio.h"

#define READY_W 46
#define READY_H 7
#define READY_UI_SCALE 3

#define DELAY_MS 1.0 / GAME_SPEED * 1000

extern int frameCount;
extern bool isGamePause;
extern bool isPauseMenuOpen;
extern SDL_Rect imgMazeOnSprite;
extern SDL_Rect imgMazeOnUi;

void startGame();

void resetGameWindow();

void endReady();

void startReady(int initialCount);

void delayToMaintainFrameRate(clock_t before, Uint32 desiredDelayInMs);

void handleGameEvents();

void drawGame();

void drawHeader();

void setPause(int isPaused);

#endif // PACMAN_GAME_WINDOW_H
