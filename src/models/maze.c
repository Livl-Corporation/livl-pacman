#include "maze.h"

char **pacmanMazeArray = NULL;

void allocateMemoryForMaze()
{
    pacmanMazeArray = NULL;
    pacmanMazeArray = malloc((MAP_HEIGHT) * sizeof(char *));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        pacmanMazeArray[i] = malloc((MAP_WIDTH+1) * sizeof(char));
    }
}

bool retrieveMazeFromFile()
{
    allocateMemoryForMaze();

    FILE *mazeFile = initFile(PATH_FILE_MAZE, 'r');

    if(mazeFile == NULL)
        return false;

    if(!fill2DArrayFromFile(mazeFile, pacmanMazeArray, MAP_HEIGHT, MAP_WIDTH, 3)) // 3 because of the \r\n\000
        return false;

    closeFile(mazeFile);

    return true;
}

void displayMaze()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            ConsoleHandlerDisplayMessage("%c", pacmanMazeArray[i][j]);
        }
        ConsoleHandlerDisplayMessage("\n");
    }
}

MazeElement getCoordinateMazeElement(int row, int col)
{
    char element = pacmanMazeArray[row][col];
    switch(element)
    {
        case WALL:
        case EMPTY:
        case COIN:
        case POINT:
        case PACMAN:
        case RED_GHOST:
        case PINK_GHOST:
        case BLUE_GHOST:
        case ORANGE_GHOST:
        case HOME:
        case CHERRY:
            return (MazeElement)element;
        default:
            return EMPTY;
    }
}

void freeMaze()
{
    ConsoleHandlerDisplayMessage("Freeing maze array.");
    if (pacmanMazeArray != NULL) {
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            free(pacmanMazeArray[i]);
        }
        free(pacmanMazeArray);
        pacmanMazeArray = NULL;
    }
}