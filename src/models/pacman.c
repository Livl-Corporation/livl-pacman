//
// Created by Franck GUTMANN on 15/02/2023.
//

#include "pacman.h"

SDL_Rect pacmanRight1 = {21, 90, 14, 14};
SDL_Rect pacmanRight2 = {36, 90, 14, 14};
SDL_Rect pacmanLeft1 = {56, 90, 14, 14};
SDL_Rect pacmanLeft2 = {75, 90, 14, 14};
SDL_Rect pacmanUp1 = {89, 90, 14, 14};
SDL_Rect pacmanUp2 = {106, 90, 14, 14};
SDL_Rect pacmanDown1 = {123, 90, 14, 14};
SDL_Rect pacmanDown2 = {140, 90, 14, 14};

struct Position pacmanSpawnPos = {1, 1};

struct Position pacmanUIPos = {0, 0};
struct Position pacmanGridPos = {0, 0};

Direction pacmanDirection = DIRECTION_RIGHT;

// TODO : [sprite refactor] use sprite system for pacman

void spawnPacman()
{
    pacmanSpawnPos = getInitialPositionOfElement(PACMAN);

    pacmanGridPos = pacmanSpawnPos;
    pacmanUIPos = getGridPosToUiPos(pacmanGridPos);

    pacmanDirection = DIRECTION_RIGHT;
}

void handlePacmanEvents()
{
    int numberOfKeyboardScancodes;
    const Uint8 *keys = SDL_GetKeyboardState(&numberOfKeyboardScancodes);

    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
        pacmanDirection = DIRECTION_LEFT;
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
        pacmanDirection = DIRECTION_RIGHT;
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
        pacmanDirection = DIRECTION_UP;
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S])
        pacmanDirection = DIRECTION_DOWN;
}

void drawPacman(int count)
{
    SDL_Rect *newPacman = NULL;

    int pacmanAnimation = (count / ANIMATION_SPEED) % 2;

    // Copy pacman position to a new
    struct Position pacmanPosCopy = pacmanUIPos;

    switch (pacmanDirection)
    {
    case DIRECTION_RIGHT:
        newPacman = (pacmanAnimation == 0) ? &pacmanRight1 : &pacmanRight2;
        pacmanPosCopy.x++;
        break;
    case DIRECTION_LEFT:
        newPacman = (pacmanAnimation == 0) ? &pacmanLeft1 : &pacmanLeft2;
        pacmanPosCopy.x--;
        break;
    case DIRECTION_UP:
        newPacman = (pacmanAnimation == 0) ? &pacmanUp1 : &pacmanUp2;
        pacmanPosCopy.y--;
        break;
    case DIRECTION_DOWN:
        newPacman = (pacmanAnimation == 0) ? &pacmanDown1 : &pacmanDown2;
        pacmanPosCopy.y++;
        break;
    }

    // Get new pacman position in grid
    struct Position newPacmanGridPos = getUiPosToGridPos(pacmanPosCopy);

    if (!arePositionEquals(pacmanGridPos, newPacmanGridPos))
    {
        // If pacman, just blit him at without updating his position
        if (isObstacle(newPacmanGridPos))
        {
            pacmanBlit(newPacman);
            return;
        }

        // Pacman has moved in grid :
        pacmanGridPos = newPacmanGridPos;
        pacmanPosCopy = onPacmanGridMove(&pacmanPosCopy);
    }

    // Move is valid, update pacman position
    pacmanUIPos = pacmanPosCopy;

    pacmanBlit(newPacman);
}

struct Position onPacmanGridMove(struct Position *pacmanUiPos)
{
    MazeElement element = getMazeElementAt(pacmanGridPos);

    switch (element) {
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
            // TODO: make pacman invincible to eat ghosts
            break;
        default:
            break;
    }

    return *pacmanUiPos;
}

void pacmanBlit(SDL_Rect *srcRect)
{
    SDL_Rect rect = {pacmanUIPos.x, pacmanUIPos.y, CELL_SIZE, CELL_SIZE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, srcRect, pSurfaceWindow, &rect);
}

struct Position teleportPacman(MazeElement teleporter)
{
    pacmanGridPos = getInitialPositionOfElement(teleporter);
    return getGridPosToUiPos(pacmanGridPos);
}