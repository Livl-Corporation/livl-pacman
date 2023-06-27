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
    Direction possibleDirections[DIRECTION_COUNT - 1] = {};
    int possibleDirectionsCount = testDirections(cell, sprite->direction, &possibleDirections);

    // if >1 direction possible, select minimum distance one
    if (possibleDirectionsCount > 1)
        return getMinimumDistanceDirection(cell, possibleDirectionsCount, &possibleDirections, sprite->targetTile);

    // if 1 direction possible, return it
    return possibleDirections[0];

}

int testDirections(struct Position cell, Direction currentDirection, Direction *possibleDirections) {
    int possibleDirectionsCount = 0;

    for (int i = 0; i < DIRECTION_COUNT; i++)
    {
        Direction direction = i;

        // if is opposite direction don't add
        if (direction == getOppositeDirection(currentDirection))
            continue;

        // get cell corresponding to move in tested direction
        struct Position cell = cell;
        updatePosition(&cell, direction, DEFAULT_POSITION_DISTANCE, DEFAULT_SPEED);

        // if out of bounds don't add
        if (!isInBounds(cell))
            continue;

        // if is obstacle don't add
        if (isObstacle(cell, true))
            continue;

        // add direction if previous conditions passed
        possibleDirections[possibleDirectionsCount++] = direction;
    }

    return possibleDirectionsCount;
}

Direction getMinimumDistanceDirection(struct Position cell, int directionCount, Direction *possibleDirections, struct Position targetPosition) {
    //select the one that is the closest to the target tile
    int minimumDistance = 1000000;
    int qualifiedDirectionCount = 0;
    Direction qualifiedDirections[DIRECTION_COUNT-1];
    for (int i = 0; i < directionCount; i++)
    {
        updatePosition(&cell, possibleDirections[i], DEFAULT_POSITION_DISTANCE, DEFAULT_SPEED);
        int distance = getDistance(cell, targetPosition);
        if (distance < minimumDistance)
        {
            minimumDistance = distance;
            qualifiedDirections[qualifiedDirectionCount++] = i;
        }
    }

    if (countArrayElementEqualsTo(&qualifiedDirections, qualifiedDirectionCount, minimumDistance) > 1) {
        // break tie
        return breakDirectionTie(qualifiedDirectionCount, &qualifiedDirections);
    }

    return qualifiedDirections[0];

}