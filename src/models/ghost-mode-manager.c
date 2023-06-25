//
// Created by Franck GUTMANN on 25/06/2023.
//

#include "ghost-mode-manager.h"

GhostMode previousGhostMode = CHASE;
GhostMode ghostMode = CHASE;


GhostMode getGhostMode() {
    return ghostMode;
}

void onGhostEatableTimerEnds()
{
    setGhostMode(previousGhostMode);
}

void setGhostMode(GhostMode mode) {
    ghostMode = mode;

    if (mode == FRIGHTENED) {
        resetTimer(&eatableGhostTimer);
        setTimerCallback(&eatableGhostTimer, &onGhostEatableTimerEnds);
        startTimer(&eatableGhostTimer);
        resetGhostEatenCount();
        return;
    }

    previousGhostMode = ghostMode;
}
