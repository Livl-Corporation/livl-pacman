#include "maze.h"

char **initialMaze = NULL;
char **gameMaze = NULL;

SDL_Rect imgMazeSmallCoin = {163, 96, 2, 2};
SDL_Rect imgMazeBigCoin = {177, 93, 7, 7};

void initMaze()
{

    if (initialMaze != NULL)
    {
        // TODO: segmentation fault here in the copy2DArray function when we restart a new game
        resetGameMaze();
        return;
    }

    if (!retrieveMazeFromFile())
    {
        ConsoleHandlerDisplayError("while retrieving maze from file.");
        pGameQuit = true;
    }
}

void resetGameMaze()
{
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

void blitRectWithOffset(SDL_Rect imgRect, struct Position positionOffsetInMaze, int offsetX, int offsetY, int width, int height)
{
    SDL_Rect destinationRect = {positionOffsetInMaze.x + offsetX, positionOffsetInMaze.y + offsetY, width, height};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgRect, pSurfaceWindow, &destinationRect);
}

void drawCoins(int frameCount)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position gridPos = {j, i};
            struct Position uiPos = gridPosToUiPos(gridPos);

            MazeElement mazeElement = getMazeElementAt(gridPos);

            switch (mazeElement)
            {
            case SMALL_COIN:
                blitRectWithOffset(imgMazeSmallCoin, uiPos, SMALL_COIN_OFFSET_X, SMALL_COIN_OFFSET_Y, SMALL_COIN_WIDTH, SMALL_COIN_HEIGHT);
                break;

            case BIG_COIN:
                if (frameCount % BIG_COIN_RATE)
                    blitRectWithOffset(imgMazeBigCoin, uiPos, BIG_COIN_OFFSET_X, BIG_COIN_OFFSET_Y, BIG_COIN_WIDTH, BIG_COIN_HEIGHT);
                break;

            default:
                break;
            }
        }
    }
}

void removeMazeElement(MazeElement elementToRemove)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position gridPos = {j, i};
            if (getMazeElementAt(gridPos) == elementToRemove)
                gameMaze[i][j] = EMPTY;
        }
    }
}

void setMazeElementAt(struct Position position, MazeElement element)
{
    if (!isInBounds(position))
        return;

    gameMaze[position.y][position.x] = element;
}

struct Position getInitialPositionOfElement(MazeElement element)
{
    return find2DArrayElement(initialMaze, MAP_HEIGHT, MAP_WIDTH, element);
}

MazeElement getMazeElementAt(struct Position position)
{
    if (!isInBounds(position))
        return WALL;

    return gameMaze[position.y][position.x];
}

MazeElement getInitialMazeElementAt(struct Position position)
{
    if (!isInBounds(position))
        return WALL;

    return initialMaze[position.y][position.x];
}

struct Position getPositionOfElement(MazeElement element)
{
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
    MazeElement element = (unsigned char)get2DArrayElement(gameMaze, position.y, position.x);
    return element == WALL || element == DOOR;
}

bool isInBounds(struct Position position)
{
    return position.x >= 0 && position.x < MAP_WIDTH && position.y >= 0 && position.y < MAP_HEIGHT;
}

bool hasCollision(struct Position position, int hitboxSize)
{

    for (int i = 0; i <= hitboxSize; i += hitboxSize)
    {
        for (int j = 0; j <= hitboxSize; j += hitboxSize)
        {
            if (isObstacle(uiPosToGridPos((struct Position) {
                    position.x + i,
                    position.y + j,
            })))
                return true;
        }
    }

    return false;
}

struct Position uiPosToGridPos(struct Position posInPx)
{
    struct Position position;

    posInPx.y -= HEADER_SCREEN_HEIGHT;

    // Get the position in the grid
    position.x = posInPx.x / CELL_SIZE;
    position.y = posInPx.y / CELL_SIZE;

    return position;
}

struct Position gridPosToUiPos(struct Position gridPos)
{
    struct Position position;

    position.x = gridPos.x * CELL_SIZE;
    position.y = gridPos.y * CELL_SIZE + HEADER_SCREEN_HEIGHT;

    return position;
}

int getInitialElementAmount(MazeElement element) {
    int amount = 0;

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position gridPos = {j, i};
            if (getMazeElementAt(gridPos) == element)
                amount++;
        }
    }

    return amount;
}

void refillCoins() {

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position position = {j, i};
            MazeElement element = getInitialMazeElementAt(position);

            if (element == SMALL_COIN || element == BIG_COIN)
                setMazeElementAt(position, element);
        }

    }

}