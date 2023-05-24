#include "maze.h"

char **initialMaze = NULL;
char **gameMaze = NULL;

SDL_Rect imgMazeSmallCoin = {5, 82, 2, 2};
SDL_Rect imgMazBigCoin = {9, 79, 7, 7};

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

    fillMazeWithCoins();
    return true;
}

void fillMazeWithCoins()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position pos = getGridPosToUiPos((struct Position){j,i});
            SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);

            if (gameMaze[i][j] == SMALL_COIN)
            {
                SDL_Rect destinationRect = {pos.x+12, pos.y+12, 14, 14};
                SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgMazeSmallCoin, pSurfaceWindow, &destinationRect);
            } else if (gameMaze[i][j] == BIG_COIN) {
                SDL_Rect destinationRect = {pos.x+2, pos.y+2, 29, 28};
                SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgMazBigCoin, pSurfaceWindow, &destinationRect);
            }
        }
    }
}

void setElementAtPositionOnMazeAs(struct Position position, MazeElement element)
{
    if (!isInBounds(position))
        return;

    gameMaze[position.y][position.x] = element;
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

bool isPositionContainsMazeElement(struct Position position, MazeElement mazeElementToCheck)
{
    MazeElement element = (unsigned char)get2DArrayElement(gameMaze, position.y, position.x);
    return element == mazeElementToCheck;
}

bool isInBounds(struct Position position) {
    return position.x >= 0 && position.x < MAP_WIDTH && position.y >= 0 && position.y < MAP_HEIGHT;
}

struct Position getUiPosToGridPos(struct Position posInPx)
{
    struct Position position;

    // Get the center of the sprite
    posInPx.x += CELL_SIZE/2;
    posInPx.y += CELL_SIZE/2;

    // Get the position in the grid
    position.x = posInPx.x / CELL_SIZE;
    position.y = posInPx.y / CELL_SIZE;

    return position;
}

struct Position getGridPosToUiPos(struct Position uiPos) {
    struct Position position;

    position.x = uiPos.x * CELL_SIZE;
    position.y = uiPos.y * CELL_SIZE;

    return position;
}
