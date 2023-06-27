//
// Created by Franck GUTMANN on 27/06/2023.
//

#ifndef PACMAN_PATHFINDING_H
#define PACMAN_PATHFINDING_H

#include "enums/direction.h"
#include <stdbool.h>
#include "constants.h"
#include "models/position.h"
#include "models/maze.h"

bool canMoveInDirection(struct Position position, Direction direction, bool allowDoors);

/**
 * Check if the provided position has a collision with an obstacle
 * @param position
 * @param hitboxSize
 */
bool hasCollision(struct Position position, int hitboxSize, bool allowDoors);

Direction getValidDirection(struct Position uiPos);

Direction breakDirectionTie(int directionCount, Direction *directions);

#endif //PACMAN_PATHFINDING_H
