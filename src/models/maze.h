#ifndef PACMAN_MAZE_H
#define PACMAN_MAZE_H

#include "../utilities/file_functions.h"
#include "models/position.h"
#include "constants.h"
#include "ui/variables.h"
#include "utilities/array_utils.h"
#include "enums/maze-element.h"

#define SMALL_COIN_OFFSET_X 12
#define SMALL_COIN_OFFSET_Y 12
#define SMALL_COIN_WIDTH 7
#define SMALL_COIN_HEIGHT 7

#define BIG_COIN_OFFSET_X 2
#define BIG_COIN_OFFSET_Y 3
#define BIG_COIN_WIDTH 20
#define BIG_COIN_HEIGHT 20

#define BLUE_MAZE_X 201
#define WHITE_MAZE_OFFSET_X 169

extern char **initialMaze;
extern char **gameMaze;

/**
 * Initialize maze
 * <!> This function must be called at least once before any other maze function
 */
void initMaze();

/**
 * Free maze
 * <!> This function must be called before the program ends
 */
void freeMaze();

/**
 * Set at a specific position in the maze a specific element from the maze element enum
 * @param position the position to set as one of the maze element enum
 * @param element the element to set at the position
 */
void setMazeElementAt(struct Position position, MazeElement element);

/**
 * Get maze element at position in the current game maze
 * @param position
 * @return MazeElement
 */
MazeElement getMazeElementAt(struct Position position);

MazeElement getInitialMazeElementAt(struct Position position);

/**
 * Find the position of a specific maze element in the current game maze
 * @param element
 * @return Position
 */
struct Position getMazePositionOfElement(MazeElement element);

/**
 * Find the initial position of a specific maze element in the initial maze
 * @param element
 * @return Position
 */
struct Position getInitialPositionOfElement(MazeElement element);


/**
 * Check if a position is in the maze bounds
 * @param position
 * @return true if the position is in the maze bounds, false otherwise
 */
bool isInBounds(struct Position position);

/**
 * Convert a position in pixels to a position in the grid
 * @param posInPx
 * @return Position
 */
struct Position uiPosToGridPos(struct Position posInPx);

/**
 * Fill the maze with coins
 */
void drawCoins(int frameCount);

/**
 * Draw the maze
 * @param applyWhiteMazeOffset : if true, the maze will be drawn with an offset to display the white maze
 */
void drawMaze(bool applyWhiteMazeOffset);

/**
 * Blit a rect with an offset
 * @param imgRect : the image rect to display
 * @param positionOffsetInMaze : the position where to display the image rect in the maze
 * @param offsetX
 * @param offsetY
 * @param width
 * @param height
 */
void blitRectWithOffset(SDL_Rect imgRect, struct Position positionOffsetInMaze, int offsetX, int offsetY, int width, int height);

/**
 * Check if a position is an obstacle
 * @param position
 * @return true if the position is an obstacle, false otherwise
 */
bool isObstacle(struct Position position);

/**
 * Check if the provided position has a collision with an obstacle
 * @param position
 * @param hitboxSize
 */
bool hasCollision(struct Position position, int hitboxSize);

/**
 * Convert a position in the grid to a position in pixels
 * @param gridPos
 * @return Position
 */
struct Position gridPosToUiPos(struct Position gridPos);

// Private

/**
 * Retrieve the maze from a file
 * @return true if the maze has been retrieved from the file, false otherwise
 */
bool retrieveMazeFromFile();

/**
 * Reset the game maze to the initial maze
 */
void resetGameMaze();

void removeMazeElement(MazeElement elementToRemove);

int getInitialElementAmount(MazeElement element);

void refillCoins();

#endif // PACMAN_MAZE_H