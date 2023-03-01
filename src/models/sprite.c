//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "sprite.h"

void moveSprintInDirection(struct Sprite *sprite) {
    switch (sprite->direction) {
        case DIRECTION_UP:
            sprite->uiPosition.y -= SPRITE_SPEED;
            break;
        case DIRECTION_DOWN:
            sprite->uiPosition.y += SPRITE_SPEED;
            break;
        case DIRECTION_LEFT:
            sprite->uiPosition.x -= SPRITE_SPEED;
            break;
        case DIRECTION_RIGHT:
            sprite->uiPosition.x += SPRITE_SPEED;
            break;
    }

    sprite->gridPosition = uiPosToGridPos(sprite->uiPosition);

}