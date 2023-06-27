#ifndef DIRECTION_H
#define DIRECTION_H

#define DIRECTION_COUNT 4

#include <stdlib.h>

typedef enum
{
    DIRECTION_RIGHT = 0,
    DIRECTION_LEFT = 1,
    DIRECTION_UP = 2,
    DIRECTION_DOWN = 3,
} Direction;

Direction getNextDirection(Direction direction);

Direction getRandomDirection();

Direction getOppositeDirection(Direction direction);

#endif