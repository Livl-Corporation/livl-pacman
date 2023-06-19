//
// Created by Julien on 19/06/2023.
//

#include "speed.h"

PacmanSpeedLevel pacmanSpeedLevels[] = {
        {1, 1, PACMAN_LEVEL1_NORM_SPEED, PACMAN_LEVEL1_NORM_DOTS_SPEED, PACMAN_LEVEL1_FRIGHT_SPEED, PACMAN_LEVEL1_FRIGHT_DOTS_SPEED},
        {2, 4, PACMAN_LEVEL2_4_NORM_SPEED, PACMAN_LEVEL2_4_NORM_DOTS_SPEED, PACMAN_LEVEL2_4_FRIGHT_SPEED, PACMAN_LEVEL2_4_FRIGHT_DOTS_SPEED},
        {5, 20, PACMAN_LEVEL5_20_NORM_SPEED, PACMAN_LEVEL5_20_NORM_DOTS_SPEED, PACMAN_LEVEL5_20_FRIGHT_SPEED, PACMAN_LEVEL5_20_FRIGHT_DOTS_SPEED},
        {21, INT_MAX, PACMAN_LEVEL21_MORE_NORM_SPEED, PACMAN_LEVEL21_MORE_NORM_DOTS_SPEED, PACMAN_LEVEL21_MORE_FRIGHT_SPEED, PACMAN_LEVEL21_MORE_FRIGHT_DOTS_SPEED}
};

GhostSpeedLevel ghostSpeedLevels[] = {
        {1, 1, GHOST_LEVEL1_NORM_SPEED, GHOST_LEVEL1_FRIGHT_SPEED, GHOST_LEVEL1_TUNNEL_SPEED},
        {2, 4, GHOST_LEVEL2_4_NORM_SPEED, GHOST_LEVEL2_4_FRIGHT_SPEED, GHOST_LEVEL2_4_TUNNEL_SPEED},
        {5, 20, GHOST_LEVEL5_20_NORM_SPEED, GHOST_LEVEL5_20_FRIGHT_SPEED, GHOST_LEVEL5_20_TUNNEL_SPEED},
        {21, INT_MAX, GHOST_LEVEL21_MORE_NORM_SPEED, GHOST_LEVEL21_MORE_FRIGHT_SPEED, GHOST_LEVEL21_MORE_TUNNEL_SPEED}
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
    float speed = DEFAULT_SPEED;

    for (int i = 0; i < sizeof(pacmanSpeedLevels) / sizeof(PacmanSpeedLevel); i++)
    {
        if (round >= pacmanSpeedLevels[i].minRound && round <= pacmanSpeedLevels[i].maxRound)
        {
            switch (pacmanSpeed)
            {
                case PACMAN_NORM_SPEED:
                    speed = pacmanSpeedLevels[i].normSpeed;
                    break;
                case PACMAN_NORM_DOTS_SPEED:
                    speed = pacmanSpeedLevels[i].normDotsSpeed;
                    break;
                case PACMAN_FRIGHT_SPEED:
                    speed = pacmanSpeedLevels[i].frightSpeed;
                    break;
                case PACMAN_FRIGHT_DOTS_SPEED:
                    speed = pacmanSpeedLevels[i].frightDotsSpeed;
                    break;
            }
            break;
        }
    }

    return speed;
}

float getGhostSpeed(struct Position ghostGridPos)
{
    int round = getRound();
    float speed = DEFAULT_SPEED;

    for (int i = 0; i < sizeof(ghostSpeedLevels) / sizeof(GhostSpeedLevel); i++)
    {
        if (round >= ghostSpeedLevels[i].minRound && round <= ghostSpeedLevels[i].maxRound)
        {
            // TODO: check if ghost is in Tunnel
            //if (isGhostInTunnel(ghostGridPos))
            //{
            //    speed = ghostSpeedLevels[i].tunnelSpeed;
            //}
            if (isGhostEatable())
            {
                speed = ghostSpeedLevels[i].frightSpeed;
            }
            else
            {
                speed = ghostSpeedLevels[i].normSpeed;
            }
            break;
        }
    }

    return speed;
}