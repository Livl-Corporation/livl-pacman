#ifndef PACMAN_MAZE_H
#define PACMAN_MAZE_H

#include "../utilities/file_functions.h"

#define MAP_WIDTH 21
#define MAP_HEIGHT 27
#define PATH_FILE_MAZE "../assets/text/maze.txt"

typedef enum {
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

extern char **pacmanMazeArray;

void allocateMemoryForMaze();
bool retrieveMazeFromFile();
void displayMaze();
MazeElement getCoordinateMazeElement(int row, int col);
void freeMaze();


#endif //PACMAN_MAZE_H