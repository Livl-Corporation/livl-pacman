//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "ghost.h"

struct Ghost *ghostList;

SDL_Rect eatableGhostRect = {
        GHOST_INITIAL_POS_X,
        GHOST_INITIAL_POS_Y + 4 * (GHOST_SIZE + GHOST_SPACING_Y),
        GHOST_SIZE,
        GHOST_SIZE};

SDL_Rect deadGhostRect = {72, 196, GHOST_SIZE, GHOST_SIZE};

int dotLimit[GHOST_COUNT] = {0, 0, 30, 60};

GhostChaseFunction chaseFunctions[GHOST_COUNT] = {
        &blinkyChase,
        &pinkyChase,
        &inkyChase,
        &clydeChase
};

struct Position ghostSpawnPoint;
struct Position ghostForceExitHome;

struct Position scatterPositions[GHOST_COUNT] = {
        {MAP_WIDTH, -1},            // RED
        {-1, -1},                   // PINK
        {MAP_WIDTH+1, MAP_HEIGHT+1},// BLUE
        {0, MAP_HEIGHT+1}           // ORANGE
};

void initGhostList()
{

    ghostSpawnPoint = getMazePositionOfElement(HOME, initialMaze);
    ghostForceExitHome = getMazePositionOfElement(RED_GHOST, initialMaze);

    ghostList = malloc(sizeof(struct Ghost) * GHOST_COUNT);

    for (int i = 0; i < GHOST_COUNT; i++)
    {
        ghostList[i].ghostElement = i + '0';

        ghostList[i].uiPosition.x = 0;
        ghostList[i].uiPosition.y = 0;

        ghostList[i].gridPosition.x = 0;
        ghostList[i].gridPosition.y = 0;

        ghostList[i].direction = DIRECTION_UP;
        ghostList[i].nextDirection = DIRECTION_UP;

        ghostList[i].scatterTile.x = 0;
        ghostList[i].scatterTile.y = 0;

        ghostList[i].isDead = false;
        ghostList[i].hasMoved = false;

        ghostList[i].dotLimit = dotLimit[i];
        ghostList[i].dotCount = 0;

        ghostList[i].isLocked = true;

        ghostList[i].scatterTile = scatterPositions[i];

        ghostList[i].chaseFunction = chaseFunctions[i];

        // Sprites :
        ghostList[i].rects = malloc(sizeof(SDL_Rect) * DIRECTION_COUNT);

        SDL_Rect initialGhost = {
            GHOST_INITIAL_POS_X,
            GHOST_INITIAL_POS_Y + i * (GHOST_SIZE + GHOST_SPACING_Y),
            GHOST_SIZE, GHOST_SIZE};

        exportSprites(
            &initialGhost,
            ghostList[i].rects,
            DIRECTION_COUNT,
            2 * (GHOST_SIZE + GHOST_SPACING_X),
            0);
    }

}

void spawnGhosts()
{
    for (int i = 0; i < GHOST_COUNT; i++)
    {
        spawnGhost(i);
    }
}

void freeGhosts()
{
    for (int i = 0; i < GHOST_COUNT; i++)
    {
        free(ghostList[i].rects);
    }
    free(ghostList);
}

void spawnGhost(int ghostId)
{
    struct Ghost *ghost = &ghostList[ghostId];

    ghost->lastRect = ghostList[ghostId].rects[0];
    ghost->gridPosition = getMazePositionOfElement(ghostList[ghostId].ghostElement, initialMaze);
    ghost->uiPosition = gridPosToUiPos(ghostList[ghostId].gridPosition);

    // ghost should select his first direction
    ghost->direction = selectGhostDirection(ghost->gridPosition, ghost);

    // ghost select his next direction
    ghost->nextDirection = selectNextGhostDirection(ghost);

    ghost->isDead = false;
    ghost->hasMoved = true;

    if (getEatenDotsCount() == 0)
        ghost->dotCount = 0;

    ghost->isLocked = ghost->dotCount < ghost->dotLimit;

}

void drawGhosts()
{
    // Don't draw ghosts during delay after Pacman death animation
    if (pacmanDeathAnimationTimer.isRunning || (pacmanDeathAnimationTimer.isFinished && pacmanDeathAnimationDelayTimer.isRunning))
        return;

    for (int i = 0; i < GHOST_COUNT; i++)
    {
        if (canBlitGhostInPausedGame(i))
            blitGhost(&ghostList[i], &ghostList[i].lastRect);
        else if (!isGamePause)
            updateGhost(&ghostList[i]);
    }
}

bool canBlitGhostInPausedGame(int ghostId)
{
    return ((isGamePause && !isScoreAnimationOnGhostEaten()) || (isScoreAnimationOnGhostEaten() && ghostList[ghostId].ghostElement != getLastGhostEaten()));
}

void updateGhost(struct Ghost *sprite)
{

    moveGhost(sprite);

    SDL_Rect ghost_in2 = getGhostSpriteAnimation(sprite);
    sprite->lastRect = ghost_in2;

    blitGhost(sprite, &ghost_in2);
}

SDL_Rect getGhostSpriteAnimation(struct Ghost *sprite) {

    if (sprite->isDead) {
        return (SDL_Rect){
                deadGhostRect.x + sprite->direction * (GHOST_SIZE + GHOST_SPACING_X),
                deadGhostRect.y,
                GHOST_SIZE,
                GHOST_SIZE
        };
    }

    SDL_Rect ghost_in2 = {};

    if (getGhostMode() == FRIGHTENED)
    {
        ghost_in2 = eatableGhostRect;

        if (isGhostEatableRunningOut() && (frameCount / ANIMATION_SPEED / 2) % 2)
            ghost_in2.x += 2 * (GHOST_SIZE + GHOST_SPACING_X);
    }
    else
    {
        ghost_in2 = sprite->rects[sprite->direction];
    }

    // Animation
    if ((frameCount / ANIMATION_SPEED) % 2)
        ghost_in2.x += (GHOST_SIZE + GHOST_SPACING_X);

    return ghost_in2;

}

void blitGhost(struct Ghost *sprite, SDL_Rect *spritePos)
{
    SDL_Rect rect = {sprite->uiPosition.x, sprite->uiPosition.y, CELL_SIZE, CELL_SIZE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, spritePos, pSurfaceWindow, &rect);
}

void onGhostGridPositionChanged(struct Ghost *sprite)
{

    removeMazeElement(sprite->ghostElement, entityMaze);

    MazeElement initialElement  = getMazeElementAt(sprite->gridPosition, initialMaze);
    if (initialElement == RED_GHOST) {
        sprite->isLocked = true;
    }

    // check if ghost should perform an action
    MazeElement element = getMazeElementInCollisionWithEntity(sprite->gridPosition);
    switch (element)
    {
    case PACMAN:

        if (sprite->isDead) return;

        handleGhostCollision(sprite->ghostElement);
        break;
    case LEFT_TELEPORTER:
        teleportGhost(sprite, RIGHT_TELEPORTER);
        break;
    case RIGHT_TELEPORTER:
        teleportGhost(sprite, LEFT_TELEPORTER);
        break;
    case HOME:
        if (sprite->isDead) {
            sprite->isDead = false;
            sprite->isLocked = sprite->dotCount < sprite->dotLimit;
            // TODO : stop sound when all ghost are home
            stopEyeSound();
        }
        break;
    }

    // update ghost position in maze
    setMazeElementAt(sprite->gridPosition, sprite->ghostElement, entityMaze);

}

void onGhostReachCellCenter(struct Ghost *sprite) {
    sprite->direction = sprite->nextDirection;
    sprite->nextDirection = selectNextGhostDirection(sprite);
}


bool isGhostInTunnel(struct Ghost *sprite)
{
    bool isGhostInTunnel = false;

    if (sprite->gridPosition.y == TUNNEL_POSITION_Y)
    {
        if ((sprite->gridPosition.x >= 0 && sprite->gridPosition.x <= TUNNEL_LENGTH) ||
            (sprite->gridPosition.x <= MAP_WIDTH && sprite->gridPosition.x >= MAP_WIDTH - TUNNEL_LENGTH))
        {
            isGhostInTunnel = true;
        }
    }

    return isGhostInTunnel;
}

void teleportGhost(struct Ghost *sprite, MazeElement destination)
{
    struct Position teleporterPosition = getMazePositionOfElement(destination, initialMaze);
    sprite->uiPosition = gridPosToUiPos(teleporterPosition);
    sprite->gridPosition = teleporterPosition;
}

void reverseGhostsDirections()
{
    for (int i = 0; i < GHOST_COUNT; i++)
    {
        struct Ghost *ghost = &ghostList[i];

        if (ghost->isDead) continue;

        if (isGhostInTunnel(ghost)) continue;

        Direction newDirection = getOppositeDirection(ghost->direction);

        // test new direction
        if (canMoveInDirection(ghost->uiPosition, newDirection, ghost->isDead)) {
            ghost->nextDirection = newDirection;
        }

    }
}


struct Ghost *getGhostByElement(MazeElement element) {
    for(int i=0; i<GHOST_COUNT; i++) {
        if(ghostList[i].ghostElement == element) {
            return &ghostList[i];
        }
    }

    return NULL;
}

void moveGhost(struct Ghost *sprite)
{

    float speed = getGhostSpeed(sprite);

    // move the ghost in his current direction
    updatePosition(&sprite->uiPosition, sprite->direction, DEFAULT_POSITION_DISTANCE, speed);

    struct Position centeredGhostUiPos = getCellCenter(sprite->uiPosition);

    // update grid position if changed
    struct Position updatedGridPos = uiPosToGridPos(centeredGhostUiPos);
    if (!arePositionEquals(sprite->gridPosition, updatedGridPos)) {
        sprite->gridPosition = updatedGridPos;
        sprite->hasMoved = false;
        onGhostGridPositionChanged(sprite);
    }

    onGhostUiPositionChanged(sprite);

}

void onGhostUiPositionChanged(struct Ghost *sprite) {
    if (!sprite->hasMoved) {

        struct Position lastCenteredGhostUiPos = gridPosToUiPos(sprite->gridPosition);
        updatePosition(&lastCenteredGhostUiPos, getOppositeDirection(sprite->direction), CELL_SIZE/2, 1);

        if (getDistance(sprite->uiPosition, lastCenteredGhostUiPos) >= CELL_SIZE/2) {
            sprite->hasMoved = true;
            onGhostReachCellCenter(sprite);
        }
    }
}

void onDotEaten() {
    for (int i = 0; i < GHOST_COUNT; i++) {
        struct Ghost *ghost = &ghostList[i];
        if (ghost->dotCount < ghost->dotLimit) {
            ghost->dotCount++;

            if (ghost->dotCount >= ghost->dotLimit) {
                ghost->isLocked = false;
            }

        }
    }
}
