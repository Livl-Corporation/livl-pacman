#ifndef POSITION_H
#define POSITION_H

#include <stdbool.h>
#include "enums/direction.h"
#include "constants.h"
#include "math.h"

struct Position
{
    float x;
    float y;
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
 * @param distance in pixel (per default equal to DEFAULT_POSITION_DISTANCE)
 * @param speed in percentage (per default equal to DEFAULT_SPEED)
 */
void updatePosition(struct Position *position, Direction direction, float distance, float speed);

struct Position getCellCenter(struct Position position);

int getDistance(struct Position pos1, struct Position pos2);

struct Position addPosition(struct Position pos1, struct Position pos2);

#endif