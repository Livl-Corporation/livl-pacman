#ifndef PACMAN_MAZE_H
#define PACMAN_MAZE_H

#include "../utilities/file_functions.h"
#include "models/position.h"
#include "constants.h"
#include "ui/variables.h"
#include "utilities/array_utils.h"
#include "enums/maze-element.h"

extern char **initialMaze;
extern char **gameMaze;
extern SDL_Rect imgMazeSmallCoin;
extern SDL_Rect imgMazeBigCoin;

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
void setElementAtPositionOnMazeAs(struct Position position, MazeElement element);

/**
 * Display maze in console
 * For debug usage only
 */
void displayMaze();

/**
 * Get maze element at position in the current game maze
 * @param position
 * @return MazeElement
 */
MazeElement getMazeElementAt(struct Position position);

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
 * @param uiPos
 * @return Position
 */
struct Position getUiPosToGridPos(struct Position uiPos);

/**
 * Fill the maze with coins
 */
void fillMazeWithCoins();

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
 * Convert a position in the grid to a position in pixels
 * @param uiPos
 * @return Position
 */
struct Position getGridPosToUiPos(struct Position uiPos);

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

#endif // PACMAN_MAZE_H