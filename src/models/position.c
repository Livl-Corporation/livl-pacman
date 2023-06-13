//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "position.h"

bool arePositionEquals(struct Position position1, struct Position position2)
{
    return position1.x == position2.x && position1.y == position2.y;
}

void updatePosition(struct Position *position, Direction direction, int step)
{
    switch (direction)
    {
    case DIRECTION_RIGHT:
        position->x += step;
        break;
    case DIRECTION_LEFT:
        position->x -= step;
        break;
    case DIRECTION_UP:
        position->y -= step;
        break;
    case DIRECTION_DOWN:
        position->y += step;
        break;
    }
}
