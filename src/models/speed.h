//
// Created by Julien on 19/06/2023.
//

#ifndef PACMAN_SPEED_H
#define PACMAN_SPEED_H

#include "game.h"
#include "maze.h"

enum PacmanSpeed
{
    PACMAN_NORM_SPEED,
    PACMAN_NORM_DOTS_SPEED,
    PACMAN_FRIGHT_SPEED,
    PACMAN_FRIGHT_DOTS_SPEED
};

enum GhostSpeed
{
    GHOST_NORM_SPEED,
    GHOST_FRIGHT_SPEED,
    TUNNEL_SPEED
};

typedef struct
{
    int minRound;
    float normSpeed;
    float normDotsSpeed;
    float frightSpeed;
    float frightDotsSpeed;
} PacmanSpeedLevel;

typedef struct
{
    int minRound;
    float normSpeed;
    float frightSpeed;
    float tunnelSpeed;
} GhostSpeedLevel;

#define PACMAN_DEFAULT_SPEED 1.0
#define GHOST_DEFAULT_SPEED 1.0

/*
 * PACMAN SPEED
 */
#define PACMAN_LEVEL1_NORM_SPEED 0.8
#define PACMAN_LEVEL1_NORM_DOTS_SPEED 0.71
#define PACMAN_LEVEL1_FRIGHT_SPEED 0.9
#define PACMAN_LEVEL1_FRIGHT_DOTS_SPEED 0.79

#define PACMAN_LEVEL2_4_NORM_SPEED 0.9
#define PACMAN_LEVEL2_4_NORM_DOTS_SPEED 0.79
#define PACMAN_LEVEL2_4_FRIGHT_SPEED 0.95
#define PACMAN_LEVEL2_4_FRIGHT_DOTS_SPEED 0.83

#define PACMAN_LEVEL5_20_NORM_SPEED 1
#define PACMAN_LEVEL5_20_NORM_DOTS_SPEED 0.87
#define PACMAN_LEVEL5_20_FRIGHT_SPEED 1
#define PACMAN_LEVEL5_20_FRIGHT_DOTS_SPEED 0.87

#define PACMAN_LEVEL21_MORE_NORM_SPEED 0.9
#define PACMAN_LEVEL21_MORE_NORM_DOTS_SPEED 0.79
#define PACMAN_LEVEL21_MORE_FRIGHT_SPEED 1
#define PACMAN_LEVEL21_MORE_FRIGHT_DOTS_SPEED 1

/*
 * GHOST SPEED
 */
#define GHOST_LEVEL1_NORM_SPEED 0.75
#define GHOST_LEVEL1_FRIGHT_SPEED 0.5
#define GHOST_LEVEL1_TUNNEL_SPEED 0.4

#define GHOST_LEVEL2_4_NORM_SPEED 0.85
#define GHOST_LEVEL2_4_FRIGHT_SPEED 0.55
#define GHOST_LEVEL2_4_TUNNEL_SPEED 0.45

#define GHOST_LEVEL5_20_NORM_SPEED 0.95
#define GHOST_LEVEL5_20_FRIGHT_SPEED 0.6
#define GHOST_LEVEL5_20_TUNNEL_SPEED 0.5

#define GHOST_LEVEL21_MORE_NORM_SPEED 0.95
#define GHOST_LEVEL21_MORE_FRIGHT_SPEED 1
#define GHOST_LEVEL21_MORE_TUNNEL_SPEED 0.5

float getPacmanSpeed(struct Position pacmanGridPos);
//float getGhostSpeed(struct Position ghostGridPos);

#endif //PACMAN_SPEED_H
