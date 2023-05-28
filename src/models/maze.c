#include "maze.h"

char **initialMaze = NULL;
char **gameMaze = NULL;

SDL_Rect imgMazeSmallCoin = {5, 82, 2, 2};
SDL_Rect imgMazeBigCoin = {9, 79, 7, 7};

const int SMALL_COIN_OFFSET_X = 12;
const int SMALL_COIN_OFFSET_Y = 12;
const int SMALL_COIN_WIDTH = 14;
const int SMALL_COIN_HEIGHT = 14;

const int BIG_COIN_OFFSET_X = 2;
const int BIG_COIN_OFFSET_Y = 2;
const int BIG_COIN_WIDTH = 29;
const int BIG_COIN_HEIGHT = 28;

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

void blitRectWithOffset(SDL_Rect imgRect, struct Position positionOffsetInMaze, int offsetX, int offsetY, int width, int height)
{
    SDL_Rect destinationRect = { positionOffsetInMaze.x + offsetX , positionOffsetInMaze.y + offsetY, width, height};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgRect, pSurfaceWindow, &destinationRect);
}

void fillMazeWithCoins()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position position = getGridPosToUiPos((struct Position){j, i});
            MazeElement mazeElement = (unsigned char)gameMaze[i][j];

            switch (mazeElement)
            {
                case SMALL_COIN:
                    blitRectWithOffset(imgMazeSmallCoin, position, SMALL_COIN_OFFSET_X, SMALL_COIN_OFFSET_Y, SMALL_COIN_WIDTH, SMALL_COIN_HEIGHT);
                    break;

                case BIG_COIN:
                    blitRectWithOffset(imgMazeBigCoin, position, BIG_COIN_OFFSET_X, BIG_COIN_OFFSET_Y, BIG_COIN_WIDTH, BIG_COIN_HEIGHT);
                    break;

                default:
                    break;
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

bool isInBounds(struct Position position) {
    return position.x >= 0 && position.x < MAP_WIDTH && position.y >= 0 && position.y < MAP_HEIGHT;
}

struct Position getUiPosToGridPos(struct Position posInPx)
{
    struct Position position;

    posInPx.y -= HEADER_SCREEN_HEIGHT;

    // Get the center of the cell
    posInPx.x += (CELL_SIZE)/2;
    posInPx.y += (CELL_SIZE)/2;

    // Get the position in the grid
    position.x = posInPx.x / CELL_SIZE;
    position.y = posInPx.y / CELL_SIZE;

    return position;
}

struct Position getGridPosToUiPos(struct Position uiPos) {
    struct Position position;

    position.x = uiPos.x * CELL_SIZE;
    position.y = uiPos.y * CELL_SIZE + HEADER_SCREEN_HEIGHT;

    return position;
}
