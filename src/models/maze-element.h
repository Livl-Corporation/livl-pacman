//
// Created by Franck GUTMANN on 23/02/2023.
//

#ifndef PACMAN_MAZE_ELEMENT_H
#define PACMAN_MAZE_ELEMENT_H

typedef enum
{
    WALL = 'x',
    EMPTY = ' ',
    COIN = 'o',
    POINT = '.',
    PACMAN = 'p',
    RED_GHOST = '1',
    PINK_GHOST = '2',
    BLUE_GHOST = '3',
    ORANGE_GHOST = '4',
    HOME = 'h',
    CHERRY = 'c',
} MazeElement;

#endif //PACMAN_MAZE_ELEMENT_H
