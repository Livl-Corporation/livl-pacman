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


/** Use :
- entityMaze when handling pacman or ghosts positions
- propsMaze when handling coins & fruits
- initialMaze when looking for obstacles
*/

extern char **initialMaze;

/**
 * Entity maze containing for storing pacman & ghosts positions
 */
extern char **entityMaze;

/**
 * Props maze containing for storing coins & fruits positions
 */
extern char **propsMaze;

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
void setMazeElementAt(struct Position position, MazeElement element, char **maze);

/**
 * Get maze element at position
 * @param position
 * @return MazeElement
 */
MazeElement getMazeElementAt(struct Position position, char **maze);

/**
 * Find the position of a specific maze element
 * @param element
 * @return Position
 */
struct Position getMazePositionOfElement(MazeElement element, char **maze);

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
bool isObstacle(struct Position position, bool allowDoors);

/**
 * Check if the provided position has a collision with an obstacle
 * @param position
 * @param hitboxSize
 */
bool hasCollision(struct Position position, int hitboxSize, bool allowDoors);

/**
 * Convert a position in the grid to a position in pixels
 * @param gridPos
 * @return Position
 */
struct Position gridPosToUiPos(struct Position gridPos);

/**
 * Retrieve the maze from a file
 * @return true if the maze has been retrieved from the file, false otherwise
 */
bool retrieveMazeFromFile();

/**
 * Reset the game maze to the initial maze
 */
void resetMaze();

void removeMazeElement(MazeElement elementToRemove, char **maze);

int getElementAmount(MazeElement element);

void refillCoins();

bool canMoveInDirection(struct Position position, Direction direction, bool allowDoors);

MazeElement getMazeElementInCollisionWithEntity(struct Position position);

#endif // PACMAN_MAZE_H