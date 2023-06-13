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

int arrowOffset = (PACMAN_SIZE / 2) - (PACMAN_ARROW_SIZE / 2);
int arrowDisplaySize = PACMAN_ARROW_SIZE * (float)CELL_SIZE / (float)PACMAN_SIZE;

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
    if (pacmanDirection != pacmanWishedDirection && canMoveInDirection(pacmanWishedDirection))
        pacmanDirection = pacmanWishedDirection;

    // Then we can choose the sprite corresponding to direction
    newPacman = pacmanSprites[pacmanDirection][pacmanAnimation];

    // Calculate the target UI position
    updatePosition(&pacmanPosCopy, pacmanDirection, 1);

    if (hasCollision(pacmanPosCopy, CELL_SIZE - 1))
    {
        // If pacman ran into obstacle, just blit him at without updating his position
        pacmanBlit(lastPacmanDirection);
        return;
    }

    // Get target pacman position in grid
    struct Position newPacmanGridPos = getUiPosToGridPos(getCellCenter(pacmanPosCopy));

    if (!arePositionEquals(pacmanGridPos, newPacmanGridPos))
    {
        // Pacman has moved in grid
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

    struct Position arrowPos = {
        pacmanUIPos.x + arrowOffset,
        pacmanUIPos.y + arrowOffset,
    };

    updatePosition(&arrowPos, pacmanWishedDirection, PACMAN_ARROW_SPACING);

    struct SDL_Rect arrowPosSDL = {
        arrowPos.x,
        arrowPos.y,
        arrowDisplaySize,
        arrowDisplaySize,
    };

    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &arrowSprite, pSurfaceWindow, &arrowPosSDL);
}

int canMoveInDirection(Direction direction)
{
    struct Position pacmanPosCopy = pacmanUIPos;
    updatePosition(&pacmanPosCopy, direction, 1);
    return !hasCollision(pacmanPosCopy, CELL_SIZE - 1);
}

struct Position onPacmanGridMove(struct Position *pacmanUiPos)
{
    MazeElement element = getMazeElementAt(pacmanGridPos);

    switch (element)
    {
    case LEFT_TELEPORTER:
        return teleportPacman(RIGHT_TELEPORTER);
    case RIGHT_TELEPORTER:
        return teleportPacman(LEFT_TELEPORTER);
    case SMALL_COIN:
        setElementAtPositionOnMazeAs(pacmanGridPos, EMPTY);
        incrementScore(10);
        break;
    case BIG_COIN:
        setElementAtPositionOnMazeAs(pacmanGridPos, EMPTY);
        incrementScore(50);
        makeGhostsEatable();
        break;
    default:
        break;
    }

    return *pacmanUiPos;
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
