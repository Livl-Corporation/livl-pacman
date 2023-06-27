#include "maze.h"

char **initialMaze = NULL;
char **entityMaze = NULL;
char **propsMaze = NULL;

SDL_Rect imgMazeSprite = {BLUE_MAZE_X, 4, 166, 214};
SDL_Rect mazeUi = {0, HEADER_SCREEN_HEIGHT, TOTAL_SCREEN_WIDTH, MAZE_SCREEN_HEIGHT};

void initMaze()
{

    allocate2DArray(&initialMaze, MAP_HEIGHT, MAP_WIDTH);
    allocate2DArray(&entityMaze, MAP_HEIGHT, MAP_WIDTH);
    allocate2DArray(&propsMaze, MAP_HEIGHT, MAP_WIDTH);

    if (!retrieveMazeFromFile())
    {
        ConsoleHandlerDisplayError("while retrieving maze from file.");
        pGameQuit = true;
    }
}

void resetMaze()
{
    copy2DArray(initialMaze, entityMaze, MAP_HEIGHT, MAP_WIDTH);
    copy2DArray(initialMaze, propsMaze, MAP_HEIGHT, MAP_WIDTH);
}

bool retrieveMazeFromFile()
{

    FILE *mazeFile = initFile(PATH_FILE_MAZE, 'r');

    if (mazeFile == NULL)
        return false;

    if (!fill2DArrayFromFile(mazeFile, initialMaze, MAP_HEIGHT, MAP_WIDTH, 3)) // 3 because of the \r\n\000
        return false;

    closeFile(mazeFile);

    resetMaze();

    return true;
}

void drawMaze(bool applyWhiteMazeOffset)
{
    if(applyWhiteMazeOffset) imgMazeSprite.x = BLUE_MAZE_X+WHITE_MAZE_OFFSET_X;
    else imgMazeSprite.x = BLUE_MAZE_X;
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, false, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgMazeSprite, pSurfaceWindow, &mazeUi);

}

void removeMazeElement(MazeElement elementToRemove, char **maze)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position gridPos = {j, i};
            if (getMazeElementAt(gridPos, maze) == elementToRemove)
                setMazeElementAt(gridPos, EMPTY, maze);
        }
    }
}

void setMazeElementAt(struct Position position, MazeElement element, char **maze)
{
    if (maze == initialMaze) {
        ConsoleHandlerDisplayError("Trying to edit initial maze.");
        return;
    }

    if (!isInBounds(position)) return;

    maze[(int)position.y][(int)position.x] = element;
}

struct Position getMazePositionOfElement(MazeElement element, char **maze)
{
    return find2DArrayElement(maze, MAP_HEIGHT, MAP_WIDTH, element);
}

MazeElement getMazeElementAt(struct Position position, char **maze)
{
    if (!isInBounds(position)) return WALL;
    return maze[(int)position.y][(int)position.x];
}

void freeMaze()
{
    ConsoleHandlerDisplayMessage("Freeing maze array.");
    free2DArray(initialMaze, MAP_HEIGHT);
    free2DArray(entityMaze, MAP_HEIGHT);
}

bool isObstacle(struct Position position, bool allowDoors)
{
    MazeElement element = getMazeElementAt(position, initialMaze);

    if (allowDoors) return element == WALL;

    return element == WALL || element == DOOR;
}

bool isInBounds(struct Position position)
{
    return position.x >= 0 && position.x < MAP_WIDTH && position.y >= 0 && position.y < MAP_HEIGHT;
}

struct Position uiPosToGridPos(struct Position posInPx)
{
    struct Position position;

    posInPx.y -= HEADER_SCREEN_HEIGHT;

    // Get position in the grid
    position.x = (int)posInPx.x / CELL_SIZE;
    position.y = (int)posInPx.y / CELL_SIZE;

    return position;
}

struct Position gridPosToUiPos(struct Position gridPos)
{
    struct Position position;

    position.x = gridPos.x * CELL_SIZE;
    position.y = gridPos.y * CELL_SIZE + HEADER_SCREEN_HEIGHT;

    return position;
}

int getElementAmount(MazeElement element) {
    int amount = 0;

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position gridPos = {j, i};
            if (getMazeElementAt(gridPos, initialMaze) == element)
                amount++;
        }
    }

    return amount;
}

MazeElement getMazeElementInCollisionWithEntity(struct Position position) {

    // Priority 1 : entities
    MazeElement entityElement = getMazeElementAt(position, entityMaze);
    switch (entityElement) {
        case RED_GHOST:
        case PINK_GHOST:
        case BLUE_GHOST:
        case ORANGE_GHOST:
        case PACMAN:
            return entityElement;
    }

    // priority 2 : teleporters & home
    MazeElement initialElement = getMazeElementAt(position, initialMaze);
    switch (initialElement) {
        case LEFT_TELEPORTER:
        case RIGHT_TELEPORTER:
            return initialElement;
        case HOME:
            return HOME;
    }

    // Priority 3 : props
    MazeElement propsElement = getMazeElementAt(position, propsMaze);
    switch (propsElement) {
        case SMALL_COIN:
        case BIG_COIN:
        case FRUIT:
            return propsElement;
    }

    return EMPTY;

}