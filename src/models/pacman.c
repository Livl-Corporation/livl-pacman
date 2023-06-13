//
// Created by Franck GUTMANN on 15/02/2023.
//

#include "pacman.h"

/**
 * IMAGE : Pacman Sprite-Sheet with 4 directions and 2 sprites per direction
 */
SDL_Rect pacmanSprites[DIRECTION_COUNT][PACMAN_SPRITE_MOUTHS_DIRECTION] = {
    {{4, 90, PACMAN_SIZE, PACMAN_SIZE}, {21, 90, PACMAN_SIZE, PACMAN_SIZE}, {36, 90, PACMAN_SIZE, PACMAN_SIZE}},  // full - Right1 - Right2
    {{4, 90, PACMAN_SIZE, PACMAN_SIZE}, {56, 90, PACMAN_SIZE, PACMAN_SIZE}, {75, 90, PACMAN_SIZE, PACMAN_SIZE}},  // full - Left1 - Left2
    {{4, 90, PACMAN_SIZE, PACMAN_SIZE}, {89, 90, PACMAN_SIZE, PACMAN_SIZE}, {106, 90, PACMAN_SIZE, PACMAN_SIZE}}, // full - Up1 - Up2
    {{4, 90, PACMAN_SIZE, PACMAN_SIZE}, {123, 90, PACMAN_SIZE, PACMAN_SIZE}, {140, 90, PACMAN_SIZE, PACMAN_SIZE}} // full - Down1 - Down2
};

SDL_Rect arrowSprite = {4, 266, PACMAN_ARROW_SIZE, PACMAN_ARROW_SIZE};

SDL_Rect lastPacmanDirection = {0, 0, 0, 0};

struct Position pacmanSpawnPos = {1, 1};
struct Position pacmanUIPos = {0, 0};
struct Position pacmanGridPos = {0, 0};

Direction defaultDirection = DIRECTION_RIGHT;

Direction pacmanDirection;
Direction pacmanWishedDirection;

// TODO : [sprite refactor] use sprite system for pacman

void spawnPacman()
{
    pacmanSpawnPos = getInitialPositionOfElement(PACMAN);

    pacmanGridPos = pacmanSpawnPos;
    pacmanUIPos = getGridPosToUiPos(pacmanGridPos);

    pacmanDirection = defaultDirection;
    pacmanWishedDirection = defaultDirection;

    lastPacmanDirection = pacmanSprites[defaultDirection][0];
}

void handlePacmanEvents()
{
    int numberOfKeyboardScancodes;
    const Uint8 *keys = SDL_GetKeyboardState(&numberOfKeyboardScancodes);

    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
        pacmanWishedDirection = DIRECTION_LEFT;
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
        pacmanWishedDirection = DIRECTION_RIGHT;
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
        pacmanWishedDirection = DIRECTION_UP;
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S])
        pacmanWishedDirection = DIRECTION_DOWN;
}

void drawPacman()
{
    if (isGamePause)
    {
        pacmanBlit(lastPacmanDirection);
        return;
    }

    SDL_Rect newPacman = {0, 0, 0, 0};

    int pacmanAnimation = (frameCount / ANIMATION_SPEED) % PACMAN_SPRITE_MOUTHS_DIRECTION;

    // Copy pacman position to a new
    struct Position pacmanPosCopy = pacmanUIPos;

    // Test is wished direction can be applied
    if (canMoveInDirection(pacmanWishedDirection))
        pacmanDirection = pacmanWishedDirection;

    // Then we can choose the sprite corresponding to direction
    newPacman = pacmanSprites[pacmanDirection][pacmanAnimation];

    // Calculate the target UI position
    updatePosition(&pacmanPosCopy, pacmanDirection, 1);

    // Get target pacman position in grid
    struct Position newPacmanGridPos = getUiPosToGridPos(pacmanPosCopy);

    if (!arePositionEquals(pacmanGridPos, newPacmanGridPos))
    {
        // If pacman ran into obstacle, just blit him at without updating his position
        if (isObstacle(newPacmanGridPos))
        {
            pacmanBlit(lastPacmanDirection);
            return;
        }

        // Pacman has moved in grid :
        pacmanGridPos = newPacmanGridPos;
        pacmanPosCopy = onPacmanGridMove(&pacmanPosCopy);
    }

    // Move is valid, update pacman position
    pacmanUIPos = pacmanPosCopy;
    lastPacmanDirection = newPacman;

    pacmanBlit(newPacman);
}

void drawPacmanArrow()
{

    if (isGamePause)
        return;

    SDL_Rect arrowSprite = getArrow(pacmanWishedDirection);

    int offset = (PACMAN_SIZE / 2) - (PACMAN_ARROW_SIZE / 2);

    struct Position arrowPos = {
        pacmanUIPos.x + offset,
        pacmanUIPos.y + offset,
    };

    updatePosition(&arrowPos, pacmanWishedDirection, PACMAN_ARROW_SPACING);

    float scaleRatio = (float)CELL_SIZE / (float)PACMAN_SIZE;
    int scaledPacmanArrowSize = PACMAN_ARROW_SIZE * scaleRatio;

    struct SDL_Rect arrowPosSDL = {
        arrowPos.x,
        arrowPos.y,
        scaledPacmanArrowSize,
        scaledPacmanArrowSize,
    };

    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &arrowSprite, pSurfaceWindow, &arrowPosSDL);
}

int canMoveInDirection(Direction direction)
{

    // Copy pacman position to a new
    struct Position pacmanPosCopy = pacmanUIPos;

    updatePosition(&pacmanPosCopy, direction, 1);

    // Get new pacman position in grid
    struct Position newPacmanGridPos = getUiPosToGridPos(pacmanPosCopy);

    return arePositionEquals(pacmanGridPos, newPacmanGridPos) || !isObstacle(newPacmanGridPos);
}

void updatePosition(struct Position *position, Direction direction, int step)
{
    switch (direction)
    {
    case DIRECTION_RIGHT:
        position->x += step;
        break;
    case DIRECTION_LEFT:
        position->x -= step;
        break;
    case DIRECTION_UP:
        position->y -= step;
        break;
    case DIRECTION_DOWN:
        position->y += step;
        break;
    }
}

struct Position onPacmanGridMove(struct Position *pacmanUiPos)
{
    removeMazeElement(PACMAN);
    MazeElement element = getMazeElementAt(pacmanGridPos);

    switch (element)
    {
    case LEFT_TELEPORTER:
        return teleportPacman(RIGHT_TELEPORTER);
    case RIGHT_TELEPORTER:
        return teleportPacman(LEFT_TELEPORTER);
    case SMALL_COIN:
        incrementScore(10);
        setElementAtPositionOnMazeAs(pacmanGridPos, PACMAN);
        break;
    case BIG_COIN:
        incrementScore(50);
        makeGhostsEatable();
        setElementAtPositionOnMazeAs(pacmanGridPos, PACMAN);
        break;
    case RED_GHOST:
        pacmanAndGhostOnSamePosition(pacmanGridPos, RED_GHOST);
        break;
    case PINK_GHOST:
        pacmanAndGhostOnSamePosition(pacmanGridPos, PINK_GHOST);
        break;
    case BLUE_GHOST:
        pacmanAndGhostOnSamePosition(pacmanGridPos, BLUE_GHOST);
        break;
    case ORANGE_GHOST:
        pacmanAndGhostOnSamePosition(pacmanGridPos, ORANGE_GHOST);
        break;
    default:
        setElementAtPositionOnMazeAs(pacmanGridPos, PACMAN);
        break;
    }

    return *pacmanUiPos;
}

void pacmanAndGhostOnSamePosition(struct Position position, MazeElement ghostElement)
{
    ConsoleHandlerDisplayMessage("You touched the ghost");

    if(isGhostEatable(ghostElement)) {
        removeMazeElement(ghostElement);
        incrementScore(200);
    }
    else {
        removeMazeElement(PACMAN);
        decrementLives();
    }
}

void pacmanBlit(SDL_Rect srcRect)
{
    SDL_Rect rect = {pacmanUIPos.x, pacmanUIPos.y, CELL_SIZE, CELL_SIZE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &srcRect, pSurfaceWindow, &rect);
}

struct Position teleportPacman(MazeElement teleporter)
{
    pacmanGridPos = getInitialPositionOfElement(teleporter);
    return getGridPosToUiPos(pacmanGridPos);
}

struct SDL_Rect getArrow(Direction direction)
{
    SDL_Rect arrow = arrowSprite;
    arrow.x += direction * arrow.w;
    return arrow;
}