//
// Created by Franck GUTMANN on 27/06/2023.
//

#ifndef PACMAN_ARROW_H
#define PACMAN_ARROW_H

#include <SDL.h>
#include "enums/direction.h"
#include "ui/variables.h"
#include "models/game.h"
#include "models/pacman.h"

#define PACMAN_ARROW_SIZE 7
#define PACMAN_ARROW_SPACING 20

#define ARROW_OFFSET ((PACMAN_SIZE / 2) - (PACMAN_ARROW_SIZE / 2))
#define ARROW_DISPLAY_SIZE ((float)PACMAN_ARROW_SIZE * ((float)CELL_SIZE / PACMAN_SIZE))

void drawPacmanArrow();

struct SDL_Rect getArrow(Direction direction);

#endif //PACMAN_ARROW_H
