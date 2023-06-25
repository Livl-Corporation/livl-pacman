//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "ghost.h"

struct Ghost *ghostList;

int ghostEaten = 0;
MazeElement ghostElementEaten = EMPTY;

SDL_Rect eatableGhostRect;

void initGhostList()
{

    ghostList = malloc(sizeof(struct Ghost) * GHOST_COUNT);

    for (int i = 0; i < GHOST_COUNT; i++)
    {
        ghostList[i].number = i;
        ghostList[i].uiPosition.x = 0;
        ghostList[i].uiPosition.y = 0;
        ghostList[i].gridPosition.x = 0;
        ghostList[i].gridPosition.y = 0;
        ghostList[i].ghostElement = i + '0';
        ghostList[i].direction = DIRECTION_RIGHT;

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

    eatableGhostRect = (SDL_Rect){
        GHOST_INITIAL_POS_X,
        GHOST_INITIAL_POS_Y + 4 * (GHOST_SIZE + GHOST_SPACING_Y),
        GHOST_SIZE,
        GHOST_SIZE};
}

void spawnGhosts() {
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
    ghostList[ghostId].lastRect = ghostList[ghostId].rects[0];
    ghostList[ghostId].gridPosition = getInitialPositionOfElement(ghostList[ghostId].ghostElement);
    setMazeElementAt(ghostList[ghostId].gridPosition, ghostList[ghostId].ghostElement);
    ghostList[ghostId].uiPosition = gridPosToUiPos(ghostList[ghostId].gridPosition);
}

void drawGhosts()
{
    // Don't draw ghosts during delay after Pacman death animation
    if(pacmanDeathAnimationTimer.isRunning || (pacmanDeathAnimationTimer.isFinished && pacmanDeathAnimationDelayTimer.isRunning)) return;

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
    return ((isGamePause && !isScoreAnimationOnGhostEaten()) || (isScoreAnimationOnGhostEaten() && ghostList[ghostId].ghostElement != ghostElementEaten));
}

void updateGhost(struct Ghost *sprite)
{
    SDL_Rect ghost_in2;

    moveGhost(sprite);

    if (isGhostEatable())
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

    sprite->lastRect = ghost_in2;

    blitGhost(sprite, &ghost_in2);
}

void blitGhost(struct Ghost *sprite, SDL_Rect *spritePos)
{
    SDL_Rect rect = {sprite->uiPosition.x, sprite->uiPosition.y, CELL_SIZE, CELL_SIZE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, spritePos, pSurfaceWindow, &rect);
}

void makeGhostsEatable()
{
    resetTimer(&eatableGhostTimer);
    startTimer(&eatableGhostTimer);
    ghostEaten = 0;
}

bool isGhostEatable()
{
    return eatableGhostTimer.isRunning;
}

bool isGhostEatableRunningOut()
{
    return eatableGhostTimer.count < EATABLE_GHOST_DURATION / 4;
}

int getEatenGhostScore(int ghostEaten)
{
    return pow(2, ghostEaten) * 100;
}

void moveGhost(struct Ghost *sprite)
{

    float speed = SPRITE_SPEED;

    // check if next position will cause collision
    if (sprite->nextDirection != sprite->direction && canMoveInDirection(sprite->uiPosition, sprite->nextDirection))
        sprite->direction = sprite->nextDirection;

    // move the ghost in his current direction
    updatePosition(&sprite->uiPosition, sprite->direction, speed);
    struct Position updatedGridPos = uiPosToGridPos(getCellCenter(sprite->uiPosition));

    if (arePositionEquals(sprite->gridPosition, updatedGridPos))
        return;

    sprite->gridPosition = updatedGridPos;
    onGhostGridPositionChanged(sprite);

}

void onGhostGridPositionChanged(struct Ghost *sprite)
{
    // check if ghost should perform an action
    MazeElement element = getMazeElementAt(sprite->gridPosition);
    switch (element) {
        case PACMAN:

            break;
        case LEFT_TELEPORTER:
            teleportGhost(sprite, RIGHT_TELEPORTER);
            break;
        case RIGHT_TELEPORTER:
            teleportGhost(sprite, LEFT_TELEPORTER);
            break;
    }

    // select his next direction
    selectNextGhostDirection(sprite);
}

void setGhostTargetTile(struct Ghost *sprite, struct Position targetTile)
{
    sprite->targetTile = targetTile;
}

void selectNextGhostDirection(struct Ghost *sprite)
{
    struct Position nextPosition = sprite->gridPosition;
    updatePosition(&nextPosition, sprite->direction, 1);

    // Get possible directions
    Direction possibleDirections[DIRECTION_COUNT-1];
    int possibleDirectionsCount = 0;

    for (int i = 0; i < DIRECTION_COUNT; i++)
    {
        Direction direction = i;

        // if is opposite direction don't att
        if (direction == getOppositeDirection(sprite->direction))
            continue;

        struct Position cell = sprite->gridPosition;
        updatePosition(&cell, direction, 1);

        // if out of bounds don't add
        if (!isInBounds(cell))
            continue;

        // if is obstacle don't add
        if (isObstacle(cell))
            continue;

        // add direction if previous conditions passed
        possibleDirections[possibleDirectionsCount] = direction;
        possibleDirectionsCount++;
    }

    // if 1 direction possible, select it
    if (possibleDirectionsCount == 1)
    {
        sprite->nextDirection = possibleDirections[0];
        return;
    }

    // else if 2 directions possible, select the one that is the closest to the target tile
    int minimumDistance = 1000000;
    for (int i = 0; i < possibleDirectionsCount; i++)
    {
        struct Position cell = sprite->gridPosition;
        updatePosition(&cell, possibleDirections[i], 1);
        int distance = getDistance(cell, sprite->targetTile);
        if (distance < minimumDistance)
        {
            minimumDistance = distance;
            sprite->nextDirection = possibleDirections[i];
        }
    }

}

Direction getOppositeDirection(Direction direction) {
    switch (direction) {
        case DIRECTION_UP:
            return DIRECTION_DOWN;
        case DIRECTION_DOWN:
            return DIRECTION_UP;
        case DIRECTION_LEFT:
            return DIRECTION_RIGHT;
        case DIRECTION_RIGHT:
            return DIRECTION_LEFT;
        default:
            return DIRECTION_UP;
    }
}

int getDistance(struct Position pos1, struct Position pos2)
{
    return abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y);
}

void teleportGhost(struct Ghost *sprite, MazeElement destination)
{
    struct Position teleporterPosition = getInitialPositionOfElement(destination);
    sprite->uiPosition = gridPosToUiPos(teleporterPosition);
    sprite->gridPosition = teleporterPosition;
}