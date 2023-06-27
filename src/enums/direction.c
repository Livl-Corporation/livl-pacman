//
// Created by Franck GUTMANN on 27/06/2023.
//

#include "enums/direction.h"

Direction getNextDirection(Direction direction)
{
    if (direction >= DIRECTION_COUNT - 1)
    {
        return 0;
    }

    return direction + 1;
}

Direction getRandomDirection()
{
    return rand() % DIRECTION_COUNT;
}

Direction getOppositeDirection(Direction direction)
{
    switch (direction)
    {
        case DIRECTION_UP:
            return DIRECTION_DOWN;
        case DIRECTION_DOWN:
            return DIRECTION_UP;
        case DIRECTION_LEFT:
            return DIRECTION_RIGHT;
        case DIRECTION_RIGHT:
            return DIRECTION_LEFT;
        default:
            return DIRECTION_UP;
    }
}