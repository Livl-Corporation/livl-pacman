//
// Created by Julien on 19/06/2023.
//

#include "speed.h"

PacmanSpeedLevel pacmanSpeedLevels[] = {
        {1, PACMAN_LEVEL1_NORM_SPEED, PACMAN_LEVEL1_NORM_DOTS_SPEED, PACMAN_LEVEL1_FRIGHT_SPEED, PACMAN_LEVEL1_FRIGHT_DOTS_SPEED},
        {2, PACMAN_LEVEL2_4_NORM_SPEED, PACMAN_LEVEL2_4_NORM_DOTS_SPEED, PACMAN_LEVEL2_4_FRIGHT_SPEED, PACMAN_LEVEL2_4_FRIGHT_DOTS_SPEED},
        {5, PACMAN_LEVEL5_20_NORM_SPEED, PACMAN_LEVEL5_20_NORM_DOTS_SPEED, PACMAN_LEVEL5_20_FRIGHT_SPEED, PACMAN_LEVEL5_20_FRIGHT_DOTS_SPEED},
        {21, PACMAN_LEVEL21_MORE_NORM_SPEED, PACMAN_LEVEL21_MORE_NORM_DOTS_SPEED, PACMAN_LEVEL21_MORE_FRIGHT_SPEED, PACMAN_LEVEL21_MORE_FRIGHT_DOTS_SPEED}
};

GhostSpeedLevel ghostSpeedLevels[] = {
        {1, GHOST_LEVEL1_NORM_SPEED, GHOST_LEVEL1_FRIGHT_SPEED, GHOST_LEVEL1_TUNNEL_SPEED},
        {2, GHOST_LEVEL2_4_NORM_SPEED, GHOST_LEVEL2_4_FRIGHT_SPEED, GHOST_LEVEL2_4_TUNNEL_SPEED},
        {5, GHOST_LEVEL5_20_NORM_SPEED, GHOST_LEVEL5_20_FRIGHT_SPEED, GHOST_LEVEL5_20_TUNNEL_SPEED},
        {21, GHOST_LEVEL21_MORE_NORM_SPEED, GHOST_LEVEL21_MORE_FRIGHT_SPEED, GHOST_LEVEL21_MORE_TUNNEL_SPEED}
};

float getPacmanSpeed(struct Position pacmanGridPos)
{
    MazeElement element = getMazeElementAt(pacmanGridPos);
    enum PacmanSpeed pacmanSpeed;

    switch (element)
    {
        case SMALL_COIN:
            pacmanSpeed = PACMAN_NORM_DOTS_SPEED;
            break;
        case BIG_COIN:
            pacmanSpeed = PACMAN_FRIGHT_DOTS_SPEED;
            break;
        default:
            pacmanSpeed = PACMAN_NORM_SPEED;
            break;
    }

    if (isGhostEatable()) pacmanSpeed = PACMAN_FRIGHT_SPEED;

    int round = getRound();
    float speedPercentage = PACMAN_DEFAULT_SPEED;

    int i = 0;
    while (pacmanSpeedLevels[i].minRound <= round) {
        switch (pacmanSpeed)
        {
            case PACMAN_NORM_SPEED:
                speedPercentage = pacmanSpeedLevels[i].normSpeed;
                break;
            case PACMAN_NORM_DOTS_SPEED:
                speedPercentage = pacmanSpeedLevels[i].normDotsSpeed;
                break;
            case PACMAN_FRIGHT_SPEED:
                speedPercentage = pacmanSpeedLevels[i].frightSpeed;
                break;
            case PACMAN_FRIGHT_DOTS_SPEED:
                speedPercentage = pacmanSpeedLevels[i].frightDotsSpeed;
                break;
        }
        i++;
    }

    return PACMAN_DEFAULT_SPEED * speedPercentage;
}

float getGhostSpeed(struct Position ghostGridPos __attribute__((unused)))
{
    int round = getRound();
    float speedPercentage = PACMAN_DEFAULT_SPEED;

    int i = 0;
    while (ghostSpeedLevels[i].minRound <= round) {
        // TODO: check if ghost is in Tunnel
        //if (isGhostInTunnel(ghostGridPos))
        //{
        //    speedPercentage = ghostSpeedLevels[i].tunnelSpeed;
        //}
        if (isGhostEatable())
        {
            speedPercentage = ghostSpeedLevels[i].frightSpeed;
        }
        else
        {
            speedPercentage = ghostSpeedLevels[i].normSpeed;
        }
        i++;
    }

    return GHOST_DEFAULT_SPEED * speedPercentage;
}