//
// Created by Franck GUTMANN on 27/06/2023.
//

#ifndef PACMAN_GHOST_PATHFINDING_H
#define PACMAN_GHOST_PATHFINDING_H

#include "models/ghosts/ghost.h"

Direction selectNextGhostDirection(struct Ghost *sprite);

Direction selectGhostDirection(struct Position cell, struct Ghost *sprite);

int testDirections(struct Position cell, Direction currentDirection, Direction *directions);

Direction getMinimumDistanceDirection(struct Position cell, int directionCount, Direction *directions, struct Position targetPosition);

#endif //PACMAN_GHOST_PATHFINDING_H
