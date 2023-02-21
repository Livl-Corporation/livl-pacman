//
// Created by Franck GUTMANN on 15/02/2023.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include <SDL.h>
#include "utilities/sdl_functions.h"
#include "ui/variables.h"
#include "models/position.h"
#include "constants.h"
#include "models/direction.h"

void handlePacmanEvents();

void drawPacman(int count);

#endif // PACMAN_PACMAN_H
