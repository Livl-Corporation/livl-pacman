//
// Created by Franck GUTMANN on 23/02/2023.
//

#ifndef PACMAN_MAZE_ELEMENT_H
#define PACMAN_MAZE_ELEMENT_H

typedef enum
{
    WALL = 'x',
    EMPTY = ' ',
    BIG_COIN = 'o',
    SMALL_COIN = '.',
    PACMAN = 'p',
    RED_GHOST = '0',
    PINK_GHOST = '1',
    BLUE_GHOST = '2',
    ORANGE_GHOST = '3',
    HOME = 'h',
    CHERRY = 'c',
    DOOR = 'd',
    LEFT_TELEPORTER = 'l',
    RIGHT_TELEPORTER = 'r',
} MazeElement;

#endif //PACMAN_MAZE_ELEMENT_H
