//
// Created by Franck GUTMANN on 27/06/2023.
//

#include "ghost_pathfinding.h"

Direction selectNextGhostDirection(struct Ghost *sprite)
{

    // Get the next ghost cell that we will check
    struct Position nextPosition = sprite->gridPosition;
    updatePosition(&nextPosition, sprite->direction, DEFAULT_POSITION_DISTANCE, DEFAULT_SPEED);

    return selectGhostDirection(nextPosition, sprite);

}

Direction selectGhostDirection(struct Position cell, struct Ghost *sprite) {
    // Get possible directions
    Direction directions[DIRECTION_COUNT-1] = {};
    int possibleDirectionsCount = testDirections(cell, sprite, directions);

    if (possibleDirectionsCount > 1) {

        // if frightened, select random direction
        if (getGhostMode() == FRIGHTENED) {
            return directions[rand() % possibleDirectionsCount];
        }

        // if dead, target ghost spawn point
        struct Position targetPosition;

        if (sprite->isDead) {
            // ghost id dead, go to home
            targetPosition = ghostSpawnPoint;
        } else if (!sprite->isLocked) {
            // ghost should exit house
            targetPosition = ghostForceExitHome;
        } else if (getGhostMode() == SCATTER) {
            // go to scatter position
            targetPosition = sprite->scatterTile;
        } else {
            // go to chase position
            targetPosition = sprite->chaseFunction();
        }

        // if >1 direction possible, select minimum distance one
        return getMinimumDistanceDirection(cell, possibleDirectionsCount, directions, targetPosition);
    }

    // if 1 direction possible, return it
    return directions[0];

}

int testDirections(struct Position cell, struct Ghost *sprite, Direction *directions) {
    int possibleDirectionsCount = 0;

    for (int i = 0; i < DIRECTION_COUNT; i++)
    {
        Direction direction = i;

        // if is opposite direction don't add
        if (direction == getOppositeDirection(sprite->direction))
            continue;

        // get cell corresponding to move in tested direction
        struct Position testedTile = cell;
        updatePosition(&testedTile, direction, DEFAULT_POSITION_DISTANCE, DEFAULT_SPEED);

        // if out of bounds don't add
        if (!isInBounds(testedTile))
            continue;

        // if is obstacle don't add
        if (isObstacle(testedTile, sprite->isDead || !sprite->isLocked))
            continue;

        // add direction if previous conditions passed
        directions[possibleDirectionsCount++] = direction;
    }

    return possibleDirectionsCount;
}

Direction getMinimumDistanceDirection(struct Position cell, int directionCount, Direction *directions, struct Position targetPosition) {
    //select the one that is the closest to the target tile
    int distances[DIRECTION_COUNT-1] = {0};
    for (int i = 0; i < directionCount; i++)
    {
        updatePosition(&cell, directions[i], DEFAULT_POSITION_DISTANCE, DEFAULT_SPEED);
        distances[i] = getDistance(cell, targetPosition);
    }

    int minimumDistance = arrayMinimumValue(distances, directionCount);

    if (countArrayElementEqualsTo(directions, directionCount, minimumDistance) > 1) {
        // break tie
        return breakDirectionTie(directionCount, directions);
    }

    return directions[findIndexOf(distances, directionCount, minimumDistance)];

}