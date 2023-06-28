//
// Created by Franck GUTMANN on 28/06/2023.
//

#include "chase.h"

struct Position pinkyChase() {
    struct Position pacmanPosition = getMazePositionOfElement(PACMAN, entityMaze);
    updatePosition(&pacmanPosition, pacmanDirection, DEFAULT_POSITION_DISTANCE, 4);

    return pacmanPosition;
}

struct Position blinkyChase() {
    return getMazePositionOfElement(PACMAN, entityMaze);
}

struct Position inkyChase() {
    struct Position pacmanPosition = getMazePositionOfElement(PACMAN, entityMaze);
    updatePosition(&pacmanPosition, pacmanDirection, DEFAULT_POSITION_DISTANCE, 2);

    struct Position blinkyPosition = getMazePositionOfElement(RED_GHOST, entityMaze);

    struct Position inkyPosition = pacmanPosition;
    updatePosition(&inkyPosition, getOppositeDirection(pacmanDirection), DEFAULT_POSITION_DISTANCE, 2);

    struct Position inkyTargetPosition = {
            pacmanPosition.x + (pacmanPosition.x - blinkyPosition.x),
            pacmanPosition.y + (pacmanPosition.y - blinkyPosition.y)
    };

    return inkyTargetPosition;
}

struct Position clydeChase() {
    struct Position pacmanPosition = getMazePositionOfElement(PACMAN, entityMaze);
    updatePosition(&pacmanPosition, pacmanDirection, DEFAULT_POSITION_DISTANCE, 8);

    struct Position clydePosition = getMazePositionOfElement(ORANGE_GHOST, entityMaze);

    if (getDistance(pacmanPosition, clydePosition) > 8) {
        return pacmanPosition;
    }

    return getMazePositionOfElement(PACMAN, entityMaze);
}
