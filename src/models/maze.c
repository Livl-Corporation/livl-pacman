#include "maze.h"

char **initialMaze = NULL;
char **gameMaze = NULL;

void initMaze()
{

    if (initialMaze != NULL)
    {
        resetGameMaze();
        return;
    }

    if (!retrieveMazeFromFile())
    {
        ConsoleHandlerDisplayError("while retrieving maze from file.");
        pGameQuit = true;
    }

}

void resetGameMaze() {
    copy2DArray(initialMaze, gameMaze, MAP_HEIGHT, MAP_WIDTH);
}

bool retrieveMazeFromFile()
{
    allocate2DArray(&initialMaze, MAP_HEIGHT, MAP_WIDTH);
    allocate2DArray(&gameMaze, MAP_HEIGHT, MAP_WIDTH);

    FILE *mazeFile = initFile(PATH_FILE_MAZE, 'r');

    if (mazeFile == NULL)
        return false;

    if (!fill2DArrayFromFile(mazeFile, initialMaze, MAP_HEIGHT, MAP_WIDTH, 3)) // 3 because of the \r\n\000
        return false;

    closeFile(mazeFile);

    resetGameMaze();

    return true;
}

void displayMaze()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            ConsoleHandlerDisplayMessage("%c", gameMaze[i][j]);
        }
        ConsoleHandlerDisplayMessage("\n");
    }
}

struct Position getInitialPositionOfElement(MazeElement element) {
    return find2DArrayElement(initialMaze, MAP_HEIGHT, MAP_WIDTH, element);
}

MazeElement getMazeElementAt(struct Position position)
{
    if (!isInBounds(position))
        return WALL;

    return get2DArrayElement(gameMaze, position.y, position.x);
}

struct Position getPositionOfElement(MazeElement element) {
    return find2DArrayElement(gameMaze, MAP_HEIGHT, MAP_WIDTH, element);
}

void freeMaze()
{
    ConsoleHandlerDisplayMessage("Freeing maze array.");
    free2DArray(initialMaze, MAP_HEIGHT);
    free2DArray(gameMaze, MAP_HEIGHT);
}

bool isObstacle(struct Position position)
{
    MazeElement element = get2DArrayElement(gameMaze, position.y, position.x);
    return element == WALL;
}

bool isInBounds(struct Position position) {
    return position.x >= 0 && position.x < MAP_WIDTH && position.y >= 0 && position.y < MAP_HEIGHT;
}

struct Position uiPosToGridPos(struct Position posInPx)
{
    struct Position position;

    // Get the center of the sprite
    position.x += CELL_SIZE/2;
    position.y += CELL_SIZE/2;

    // Get the position in the grid
    position.x = posInPx.x / CELL_SIZE;
    position.y = posInPx.y / CELL_SIZE;

    return position;
}

struct Position gridPosToUiPos(struct Position uiPos) {
    struct Position position;

    position.x = uiPos.x * CELL_SIZE;
    position.y = uiPos.y * CELL_SIZE;

    return position;
}
