//
// Created by Franck GUTMANN on 25/06/2023.
//

#ifndef PACMAN_GHOST_MODE_MANAGER_H
#define PACMAN_GHOST_MODE_MANAGER_H

#include "enums/ghost-mode.h"
#include "game.h"

void setGhostMode(GhostMode mode);

GhostMode getGhostMode();

void onGhostEatableTimerEnds();

#endif //PACMAN_GHOST_MODE_MANAGER_H
