//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "ghost.h"

struct Ghost *ghostList;

int ghostEaten = 0;
MazeElement ghostElementEaten = EMPTY;

SDL_Rect eatableGhostRect;

struct Position redGhostScatterTargetTile = {MAP_WIDTH, -1};
struct Position pinkGhostScatterTargetTile = {-1, -1};
struct Position blueGhostScatterTargetTile = {MAP_WIDTH+1, MAP_HEIGHT+1};
struct Position orangeGhostScatterTargetTile = {0, MAP_HEIGHT+1};

void initGhostList()
{

    ghostList = malloc(sizeof(struct Ghost) * GHOST_COUNT);

    for (int i = 0; i < GHOST_COUNT; i++)
    {
        ghostList[i].ghostElement = i + '0';

        ghostList[i].uiPosition.x = 0;
        ghostList[i].uiPosition.y = 0;

        ghostList[i].gridPosition.x = 0;
        ghostList[i].gridPosition.y = 0;

        ghostList[i].direction = DIRECTION_UP;
        ghostList[i].wishedDirection = DIRECTION_UP;
        ghostList[i].nextDirection = DIRECTION_UP;

        ghostList[i].targetTile.x = 0;
        ghostList[i].targetTile.y = 0;

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
    ghostList[ghostId].lastRect = ghostList[ghostId].rects[0];
    ghostList[ghostId].gridPosition = getMazePositionOfElement(ghostList[ghostId].ghostElement, initialMaze);
    ghostList[ghostId].uiPosition = gridPosToUiPos(ghostList[ghostId].gridPosition);

    // TODO : reset position in entityMaze
    /*
        if (!arePositionEquals(
        ghostList[ghostId].gridPosition,
        getMazePositionOfElement(ghostList[ghostId].ghostElement, &entityMaze)
        )) {
            removeMazeElement(ghostList[ghostId].ghostElement, entityMaze);
            setMazeElementAt(ghostList[ghostId].gridPosition, ghostList[ghostId].ghostElement, entityMaze);
        }
    */
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
    return ((isGamePause && !isScoreAnimationOnGhostEaten()) || (isScoreAnimationOnGhostEaten() && ghostList[ghostId].ghostElement != ghostElementEaten));
}

void updateGhost(struct Ghost *sprite)
{
    SDL_Rect ghost_in2;

    moveGhost(sprite);

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

    sprite->lastRect = ghost_in2;

    blitGhost(sprite, &ghost_in2);
}

void blitGhost(struct Ghost *sprite, SDL_Rect *spritePos)
{
    SDL_Rect rect = {sprite->uiPosition.x, sprite->uiPosition.y, CELL_SIZE, CELL_SIZE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, spritePos, pSurfaceWindow, &rect);
}

bool isGhostEatableRunningOut()
{
    return eatableGhostTimer.count < EATABLE_GHOST_DURATION / 4;
}

int getEatenGhostScore(int eatenGhostCount)
{
    return pow(2, eatenGhostCount) * 100;
}

void moveGhost(struct Ghost *sprite)
{
    float speed = getGhostSpeed(sprite);

    // check if next position will cause collision
    if (getGhostMode() != FRIGHTENED)
    {
        if (sprite->wishedDirection != sprite->direction && canMoveInDirection(sprite->uiPosition, sprite->wishedDirection))
            sprite->direction = sprite->wishedDirection;
    }

    bool isMoveValid = false;
    do
    {
        isMoveValid = canMoveInDirection(sprite->uiPosition, sprite->direction);
        if (!isMoveValid)
            sprite->direction = getNextDirection(sprite->direction);

    } while (!isMoveValid);

    // move the ghost in his current direction
    updatePosition(&sprite->uiPosition, sprite->direction, DEFAULT_POSITION_DISTANCE, speed);
    struct Position updatedGridPos = uiPosToGridPos(getCellCenter(sprite->uiPosition));

    if (arePositionEquals(sprite->gridPosition, updatedGridPos))
        return;

    sprite->gridPosition = updatedGridPos;
    onGhostGridPositionChanged(sprite);
}

void onGhostGridPositionChanged(struct Ghost *sprite)
{

    if (getGhostMode() != FRIGHTENED)
        sprite->wishedDirection = sprite->nextDirection;

    removeMazeElement(sprite->ghostElement, entityMaze);

    // check if ghost should perform an action
    MazeElement element = getMazeElementInCollisionWithEntity(sprite->gridPosition);
    switch (element)
    {
    case PACMAN:
        handleGhostCollision(sprite->ghostElement);
        break;
    case LEFT_TELEPORTER:
        teleportGhost(sprite, RIGHT_TELEPORTER);
        break;
    case RIGHT_TELEPORTER:
        teleportGhost(sprite, LEFT_TELEPORTER);
        break;
    }

    // update ghost position in maze
    setMazeElementAt(sprite->gridPosition, sprite->ghostElement, entityMaze);

    selectNextGhostDirection(sprite);
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

void setGhostScatterModeTargetTile()
{
    for(int i=0; i<GHOST_COUNT; i++)
    {
        switch(ghostList[i].ghostElement)
        {
            case RED_GHOST:
                setGhostTargetTile(&ghostList[i], redGhostScatterTargetTile);
                break;
            case PINK_GHOST:
                setGhostTargetTile(&ghostList[i], pinkGhostScatterTargetTile);
                break;
            case BLUE_GHOST:
                setGhostTargetTile(&ghostList[i], blueGhostScatterTargetTile);
                break;
            case ORANGE_GHOST:
                setGhostTargetTile(&ghostList[i], orangeGhostScatterTargetTile);
                break;
            default:
                break;
        }
    }
}

void setGhostTargetTile(struct Ghost *sprite, struct Position targetTile)
{
    sprite->targetTile = targetTile;
}

void selectNextGhostDirection(struct Ghost *sprite)
{
    struct Position nextPosition = sprite->gridPosition;
    updatePosition(&nextPosition, sprite->direction, DEFAULT_POSITION_DISTANCE, DEFAULT_SPEED);

    // Get possible directions
    Direction possibleDirections[DIRECTION_COUNT - 1] = {};
    int possibleDirectionsCount = 0;

    for (int i = 0; i < DIRECTION_COUNT; i++)
    {
        Direction direction = i;

        // if is opposite direction don't add
        if (direction == getOppositeDirection(sprite->direction))
            continue;

        struct Position cell = nextPosition;
        updatePosition(&cell, direction, DEFAULT_POSITION_DISTANCE, DEFAULT_SPEED);

        // if out of bounds don't add
        if (!isInBounds(cell))
            continue;

        // if is obstacle don't add
        if (isObstacle(cell))
            continue;

        // add direction if previous conditions passed
        possibleDirections[possibleDirectionsCount++] = direction;
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
        updatePosition(&cell, possibleDirections[i], DEFAULT_POSITION_DISTANCE, DEFAULT_SPEED);
        int distance = getDistance(cell, sprite->targetTile);
        if (distance < minimumDistance)
        {
            minimumDistance = distance;
            sprite->nextDirection = possibleDirections[i];
        }
    }
}

Direction getOppositeDirection(Direction direction)
{
    switch (direction)
    {
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
    struct Position teleporterPosition = getMazePositionOfElement(destination, initialMaze);
    sprite->uiPosition = gridPosToUiPos(teleporterPosition);
    sprite->gridPosition = teleporterPosition;
}

void eatGhost(MazeElement ghostElement)
{
    ghostEaten++;
    removeMazeElement(ghostElement, entityMaze);
    playAudioWithChannel(audioEatGhost, CHANNEL_EAT_GHOST);

    incrementScore(getEatenGhostScore(ghostEaten));

    setTimerCallback(&eatGhostAnimationTimer, endEatGhostAnimation);

    resetTimer(&eatGhostAnimationTimer);
    startTimer(&eatGhostAnimationTimer);

    isGamePause = true;
    ghostElementEaten = ghostElement;
}

int getGhostEatenCount()
{
    return ghostEaten;
}

void resetGhostEatenCount()
{
    ghostEaten = 0;
}

void reverseGhostsDirections()
{
    for (int i = 0; i < GHOST_COUNT; i++)
    {
        struct Ghost *ghost = &ghostList[i];
        Direction newDirection = getOppositeDirection(ghost->direction);
        ghost->nextDirection = newDirection;
        ghost->wishedDirection = newDirection;
    }
}

Direction getNextDirection(Direction direction)
{
    if (direction >= DIRECTION_COUNT - 1)
    {
        return 0;
    }

    return direction + 1;
}

Direction getRandomDirection()
{
    return rand() % DIRECTION_COUNT;
}