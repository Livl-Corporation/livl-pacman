#ifndef POSITION_H
#define POSITION_H

#include <stdbool.h>
#include "enums/direction.h"

struct Position
{
    int x;
    int y;
};

/**
 * Check if two positions are equals
 * @param position1
 * @param position2
 * @return
 */
bool arePositionEquals(struct Position position1, struct Position position2);

/**
 * Update position according to direction and step
 * @param position
 * @param direction
 * @param step
 */
void updatePosition(struct Position *position, Direction direction, int step);

#endif