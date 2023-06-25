//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "position.h"

bool arePositionEquals(struct Position position1, struct Position position2)
{
    return (int)position1.x == (int)position2.x && (int)position1.y == (int)position2.y;
}

void updatePosition(struct Position *position, Direction direction, float distance, float speed)
{
    switch (direction)
    {
        case DIRECTION_LEFT:
            position->x -= speed * distance;
            break;
        case DIRECTION_RIGHT:
            position->x += speed * distance;
            break;
        case DIRECTION_UP:
            position->y -= speed * distance;
            break;
        case DIRECTION_DOWN:
            position->y += speed * distance;
            break;
    }
}

struct Position getCellCenter(struct Position position)
{
    struct Position center = {
            position.x + CELL_SIZE / 2,
            position.y + CELL_SIZE / 2,
    };
    return center;
}
