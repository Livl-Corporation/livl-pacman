//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "sprite.h"

void moveSprintInDirection(struct Sprite *sprite)
{
    updatePosition(&sprite->uiPosition, sprite->direction, SPRITE_SPEED);
    sprite->gridPosition = getUiPosToGridPos(getCellCenter(sprite->uiPosition));
}

struct Position getCellCenter(struct Position position)
{
    struct Position center = {
        position.x + CELL_SIZE / 2,
        position.y + CELL_SIZE / 2,
    };
    return center;
}