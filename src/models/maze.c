#include "maze.h"

char **initialMaze = NULL;
char **entityMaze = NULL;
char **propsMaze = NULL;

SDL_Rect imgSmallCoinSprite = {163, 96, 2, 2};
SDL_Rect imgBigCoinSprite = {177, 93, 7, 7};

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

void blitRectWithOffset(SDL_Rect imgRect, struct Position positionOffsetInMaze, int offsetX, int offsetY, int width, int height)
{
    SDL_Rect destinationRect = {(int)positionOffsetInMaze.x + offsetX, (int)positionOffsetInMaze.y + offsetY, width, height};
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

            MazeElement mazeElement = getMazeElementAt(gridPos, propsMaze);

            switch (mazeElement)
            {
            case SMALL_COIN:
                blitRectWithOffset(imgSmallCoinSprite, uiPos, SMALL_COIN_OFFSET_X, SMALL_COIN_OFFSET_Y, SMALL_COIN_WIDTH, SMALL_COIN_HEIGHT);
                break;

            case BIG_COIN:
                if (frameCount % BIG_COIN_RATE)
                    blitRectWithOffset(imgBigCoinSprite, uiPos, BIG_COIN_OFFSET_X, BIG_COIN_OFFSET_Y, BIG_COIN_WIDTH, BIG_COIN_HEIGHT);
                break;

            default:
                break;
            }
        }
    }
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

bool isObstacle(struct Position position)
{
    MazeElement element = getMazeElementAt(position, initialMaze);
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

void refillCoins() {

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position position = {j, i};
            MazeElement element = getMazeElementAt(position, initialMaze);

            if (element == SMALL_COIN || element == BIG_COIN)
                setMazeElementAt(position, element, propsMaze);
        }

    }

}

bool canMoveInDirection(struct Position position, Direction direction)
{
    updatePosition(&position, direction, DEFAULT_POSITION_DISTANCE, DEFAULT_SPEED);
    return !hasCollision(position, CELL_SIZE-1);
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

    // priority 2 : teleporters
    MazeElement teleporterElement = getMazeElementAt(position, initialMaze);
    switch (teleporterElement) {
        case LEFT_TELEPORTER:
        case RIGHT_TELEPORTER:
            return teleporterElement;
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