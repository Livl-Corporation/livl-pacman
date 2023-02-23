//
// Created by Franck GUTMANN on 23/02/2023.
//

#ifndef PACMAN_SPRITE_H
#define PACMAN_SPRITE_H

#include <SDL.h>
#include "position.h"
#include "enums/direction.h"
#include "constants.h"
#include "models/maze.h"

struct Sprite {
    int number;
    struct Position uiPosition;
    struct Position gridPosition;
    Direction direction;
    SDL_Rect *spritePos;
};

void moveSprintInDirection(struct Sprite *sprite);

#endif //PACMAN_SPRITE_H
