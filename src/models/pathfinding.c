//
// Created by Franck GUTMANN on 27/06/2023.
//

#include "pathfinding.h"

Direction preferedDirectionOrder[DIRECTION_COUNT] = {
        DIRECTION_UP, DIRECTION_LEFT, DIRECTION_DOWN, DIRECTION_RIGHT
};

bool canMoveInDirection(struct Position position, Direction direction, bool allowDoors)
{
    struct Position posCopy = position;
    updatePosition(&posCopy, direction, DEFAULT_POSITION_DISTANCE, DEFAULT_SPEED);
    return !hasCollision(posCopy, CELL_SIZE-1, allowDoors);
}

bool hasCollision(struct Position position, int hitboxSize, bool allowDoors)
{

    for (int i = 0; i <= hitboxSize; i += hitboxSize)
    {
        for (int j = 0; j <= hitboxSize; j += hitboxSize)
        {
            if (isObstacle(uiPosToGridPos((struct Position) {
                    position.x + i,
                    position.y + j,
            }), allowDoors))
                return true;
        }
    }

    return false;
}


Direction getValidDirection(struct Position uiPos) {

    for (int i = 0; i<DIRECTION_COUNT; i++) {
        Direction direction = preferedDirectionOrder[i];
        if (canMoveInDirection(uiPos, direction, false)) {
            return direction;
        }
    }

    return -1;

}

Direction breakDirectionTie(int directionCount, Direction *directions) {
    for (int i = 0; i < DIRECTION_COUNT; i++) {
        Direction direction = preferedDirectionOrder[i];
        if (findIndexOf(directions, directionCount, directionCount) != -1)
            return direction;
    }
}