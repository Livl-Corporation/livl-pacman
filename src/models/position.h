#ifndef POSITION_H
#define POSITION_H

#include <stdbool.h>

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

#endif