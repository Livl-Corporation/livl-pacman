//
// Created by Franck GUTMANN on 25/06/2023.
//

#ifndef PACMAN_GHOST_MODE_MANAGER_H
#define PACMAN_GHOST_MODE_MANAGER_H

#define MODE_CHANGE_COUNT 8
#define MODE_CHANGE_PRESETS_COUNTS 3

#define MODE_SCATTER_1_DURATION_LVL1 7
#define MODE_SCATTER_3_DURATION_LVL1 5
#define MODE_CHASE_DURATION_LVL1 20

#define MODE_SCATTER_1_DURATION_LVL2 7
#define MODE_SCATTER_3_DURATION_LVL_2 5
#define MODE_SCATTER_4_DURATION_LVL2 0
#define MODE_CHASE_1_DURATION_LVL2 20
#define MODE_CHASE_2_DURATION_LVL2 1033

#define MODE_SCATTER_1_DURATION_LVL5 5
#define MODE_SCATTER_3_DURATION_LVL5 5
#define MODE_SCATTER_4_DURATION_LVL5 0
#define MODE_CHASE_1_DURATION_LVL5 20
#define MODE_CHASE_2_DURATION_LVL5 1037

#define MODE_CHASE_4_DURATION -1

#include "enums/ghost-mode.h"
#include "ghost.h"
#include "game.h"

void setGhostMode(GhostMode mode);

GhostMode getGhostMode();

void onGhostEatableTimerEnds();

int getPredeterminedModeDuration(int index);

GhostMode getPredeterminedGhostMode(int index);

void onModeTimerEnd();

void resetGhostModeTimer();

#endif //PACMAN_GHOST_MODE_MANAGER_H
