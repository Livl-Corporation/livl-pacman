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
extern SDL_Rect imgMazBigCoin;

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
 * Check if a position is an obstacle
 * @param position
 * @return true if the position is an obstacle, false otherwise
 */
bool isObstacle(struct Position position);

/**
 * Convert a position in pixels to a position in the grid
 * @param uiPos
 * @return Position
 */
struct Position uiPosToGridPos(struct Position uiPos);

void fillMazeWithCoins();

/**
 * Convert a position in the grid to a position in pixels
 * @param uiPos
 * @return Position
 */
struct Position gridPosToUiPos(struct Position uiPos);

// Private
bool retrieveMazeFromFile();
void resetGameMaze();

#endif // PACMAN_MAZE_H