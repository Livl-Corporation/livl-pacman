//
// Created by Franck GUTMANN on 25/06/2023.
//

#include "mode_manager.h"

int modeDurationsLvl1[MODE_CHANGE_COUNT] = {
        MODE_SCATTER_1_DURATION_LVL1,
        MODE_CHASE_DURATION_LVL1,
        MODE_SCATTER_1_DURATION_LVL1,
        MODE_CHASE_DURATION_LVL1,
        MODE_SCATTER_3_DURATION_LVL1,
        MODE_CHASE_DURATION_LVL1,
        MODE_SCATTER_3_DURATION_LVL1,
        MODE_CHASE_4_DURATION
};

int modeDurationsLvl2[MODE_CHANGE_COUNT] = {
        MODE_SCATTER_1_DURATION_LVL2,
        MODE_CHASE_1_DURATION_LVL2,
        MODE_SCATTER_1_DURATION_LVL2,
        MODE_CHASE_1_DURATION_LVL2,
        MODE_SCATTER_3_DURATION_LVL_2,
        MODE_CHASE_2_DURATION_LVL2,
        MODE_SCATTER_4_DURATION_LVL2,
        MODE_CHASE_4_DURATION
};

int modeDurationsLvl5[MODE_CHANGE_COUNT] = {
        MODE_SCATTER_1_DURATION_LVL5,
        MODE_CHASE_1_DURATION_LVL5,
        MODE_SCATTER_1_DURATION_LVL5,
        MODE_CHASE_1_DURATION_LVL5,
        MODE_SCATTER_3_DURATION_LVL5,
        MODE_CHASE_2_DURATION_LVL5,
        MODE_SCATTER_4_DURATION_LVL5,
        MODE_CHASE_4_DURATION
};

int modeDurationsLevels[MODE_CHANGE_PRESETS_COUNTS] = {
        1, 2, 5
};

int *modeDurations[MODE_CHANGE_PRESETS_COUNTS] = {
        modeDurationsLvl1,
        modeDurationsLvl2,
        modeDurationsLvl5
};

GhostMode previousGhostMode = CHASE;
GhostMode ghostMode = CHASE;

int modeIndex = 0;

GhostMode getGhostMode() {
    return ghostMode;
}

void onGhostEatableTimerEnds()
{
    setGhostMode(previousGhostMode);
}

void setGhostMode(GhostMode mode) {

    if (ghostMode != FRIGHTENED) {
        // Ghost reverse direction when mode changes except when coming from frightened mode
        reverseGhostsDirections();
    }

    ghostMode = mode;

    if (mode == FRIGHTENED) {
        stopTimer(&ghostModeTimer);
        resetTimer(&eatableGhostTimer);
        setTimerCallback(&eatableGhostTimer, &onGhostEatableTimerEnds);
        startTimer(&eatableGhostTimer);
        resetGhostEatenCount();
        return;
    }

    startTimer(&ghostModeTimer);

    previousGhostMode = ghostMode;
}

int getPredeterminedModeDuration(int index) {

    int round = getRound();

    int durationsIndex = 0;
    for (int i = 1; i < MODE_CHANGE_PRESETS_COUNTS; i++) {
        if (modeDurationsLevels[i] <= round) {
            durationsIndex = i;
        } else {
            break;
        }
    }

    int *durations = modeDurations[durationsIndex];

    return durations[index];

}

GhostMode getPredeterminedGhostMode(int index) {
    if (index % 2 == 0) {
        return SCATTER;
    }

    return CHASE;
}

void onModeTimerEnd() {

    // get next timer duration & increment modeIndex
    int nextDuration = getPredeterminedModeDuration(++modeIndex);

    // setup next timer
    if (nextDuration>0) {
        // TODO : correct convertion to seconds :
        setDuration(&ghostModeTimer, nextDuration*MODE_DURATION_MULTIPLIER);
        resetTimer(&ghostModeTimer);
    }

    // go to next mode
    setGhostMode(getPredeterminedGhostMode(modeIndex));
}

void resetGhostModeTimer() {
    setTimerCallback(&ghostModeTimer, &onModeTimerEnd);
    modeIndex = -1;
    onModeTimerEnd();
}