//
// Created by Franck GUTMANN on 15/02/2023.
//

#include "pacman.h"

SDL_Rect pacmanSprites[DIRECTION_COUNT];
SDL_Rect pacmanRoundSprite = {4, 90, PACMAN_SIZE, PACMAN_SIZE};

SDL_Rect pacmanDeathAnimation[PACMAN_DEATH_ANIMATION_FRAMES];

SDL_Rect arrowSprite = {4, 266, PACMAN_ARROW_SIZE, PACMAN_ARROW_SIZE};

SDL_Rect lastPacmanPosition = {0, 0, 0, 0};

struct Position pacmanSpawnPos = {1, 1};
struct Position pacmanUIPos = {0, 0};
struct Position pacmanGridPos = {0, 0};

Direction defaultDirection = DIRECTION_RIGHT;

Direction pacmanDirection;
Direction pacmanWishedDirection;

int arrowOffset = (PACMAN_SIZE / 2) - (PACMAN_ARROW_SIZE / 2);
float arrowDisplaySize = (float)PACMAN_ARROW_SIZE * ((float)CELL_SIZE / PACMAN_SIZE);

float pacmanSpeed = PACMAN_DEFAULT_SPEED;

void initPacmanSprites()
{

    SDL_Rect initialPacmanRect = (SDL_Rect){
        pacmanRoundSprite.x + PACMAN_SIZE + PACMAN_SPACING_X,
        pacmanRoundSprite.y,
        pacmanRoundSprite.w,
        pacmanRoundSprite.h};

    exportSprites(
        &initialPacmanRect,
        pacmanSprites,
        DIRECTION_COUNT,
        2 * (PACMAN_SIZE + PACMAN_SPACING_X),
        0);

    SDL_Rect initialPacmanDeathRect = (SDL_Rect){
        pacmanRoundSprite.x + PACMAN_SIZE + PACMAN_SPACING_X,
        pacmanRoundSprite.y + PACMAN_SIZE + PACMAN_SPACING_Y,
        PACMAN_SIZE,
        PACMAN_SIZE};

    exportSprites(
        &initialPacmanDeathRect,
        pacmanDeathAnimation,
        PACMAN_DEATH_ANIMATION_FRAMES,
        PACMAN_SIZE + PACMAN_SPACING_X,
        0);
}

void spawnPacman()
{
    pacmanSpawnPos = getMazePositionOfElement(PACMAN, initialMaze);

    pacmanGridPos = pacmanSpawnPos;
    pacmanUIPos = gridPosToUiPos(pacmanGridPos);

    pacmanDirection = defaultDirection;
    pacmanWishedDirection = defaultDirection;

    lastPacmanPosition = pacmanRoundSprite;

    // TODO : reset position in entityMaze
/*
    if (!arePositionEquals(
        getMazePositionOfElement(PACMAN, entityMaze),
        pacmanSpawnPos
    )) {
        removeMazeElement(PACMAN, &entityMaze);
        setMazeElementAt(pacmanGridPos, PACMAN, &entityMaze);
    }
*/

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
    if (shouldSkipPacmanDrawOnDeathTimer() || shouldSkipPacmanDrawOnGamePause())
        return;

    SDL_Rect newPacmanSpriteMouth;

    struct Position pacmanPosCopy = pacmanUIPos;

    if (shouldChangeDirection())
        pacmanDirection = pacmanWishedDirection;

    int pacmanAnimation = getPacmanAnimation();

    if (pacmanAnimation == PACMAN_SPRITE_MOUTHS_DIRECTION - 1)
        newPacmanSpriteMouth = pacmanRoundSprite;
    else
        newPacmanSpriteMouth = getPacmanSprite(pacmanAnimation);

    struct Position targetUiPosition = calculateTargetPosition(pacmanPosCopy);

    if (hasCollision(targetUiPosition, CELL_SIZE - 1))
    {
        pacmanBlit(lastPacmanPosition);
        return;
    }

    struct Position targetGridPosition = uiPosToGridPos(getCellCenter(targetUiPosition));

    if (hasPacmanMoved(targetGridPosition))
    {
        pacmanGridPos = targetGridPosition;
        pacmanSpeed = getPacmanSpeed(pacmanGridPos);
        targetUiPosition = onPacmanGridMove(&targetUiPosition);
    }

    pacmanUIPos = targetUiPosition;
    lastPacmanPosition = newPacmanSpriteMouth;

    pacmanBlit(newPacmanSpriteMouth);
}

bool shouldSkipPacmanDrawOnGamePause()
{
    if (isGamePause)
    {
        if (pacmanDeathAnimationTimer.isRunning)
        {
            drawPacmanDeathAnimation();
            return true;
        }

        if (isScoreAnimationOnGhostEaten())
            return true;

        pacmanBlit(lastPacmanPosition);
        return true;
    }

    return false;
}

void drawPacmanDeathAnimation()
{
    int pacmanDeathAnimationIndex = calculatePacmanDeathAnimationIndex();
    pacmanBlit(pacmanDeathAnimation[pacmanDeathAnimationIndex]);
}

bool shouldSkipPacmanDrawOnDeathTimer()
{
    return pacmanDeathAnimationTimer.isFinished && pacmanDeathAnimationDelayTimer.isRunning;
}

bool shouldChangeDirection()
{
    return pacmanDirection != pacmanWishedDirection && canMoveInDirection(pacmanWishedDirection);
}

int getPacmanAnimation()
{
    return (frameCount / ANIMATION_SPEED) % PACMAN_SPRITE_MOUTHS_DIRECTION;
}

SDL_Rect getPacmanSprite(int pacmanAnimation)
{
    SDL_Rect sprite = pacmanSprites[pacmanDirection];
    sprite.x += pacmanAnimation * (PACMAN_SIZE + PACMAN_SPACING_X);
    return sprite;
}

struct Position calculateTargetPosition(struct Position pacmanPosCopy)
{
    updatePosition(&pacmanPosCopy, pacmanDirection, DEFAULT_POSITION_DISTANCE, pacmanSpeed);
    return pacmanPosCopy;
}

bool hasPacmanMoved(struct Position newPacmanGridPos)
{
    return !arePositionEquals(pacmanGridPos, newPacmanGridPos);
}

void pacmanBlit(SDL_Rect srcRect)
{
    SDL_Rect rect = {(int)pacmanUIPos.x, (int)pacmanUIPos.y, CELL_SIZE, CELL_SIZE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, 1, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &srcRect, pSurfaceWindow, &rect);
}

int calculatePacmanDeathAnimationIndex()
{
    float animationIndex = (1 - ((float)pacmanDeathAnimationTimer.count / (float)pacmanDeathAnimationTimer.initialCount)) * PACMAN_DEATH_ANIMATION_FRAMES;
    return (int)animationIndex;
}

void drawPacmanArrow()
{

    if (isGamePause)
        return;

    SDL_Rect newArrowSprite = getArrow(pacmanWishedDirection);

    struct Position arrowPos = {
        pacmanUIPos.x + (float)arrowOffset,
        pacmanUIPos.y + (float)arrowOffset,
    };

    updatePosition(&arrowPos, pacmanWishedDirection, PACMAN_ARROW_SPACING, DEFAULT_SPEED);

    struct SDL_Rect arrowPosSDL = {
        (int)arrowPos.x,
        (int)arrowPos.y,
        (int)arrowDisplaySize,
        (int)arrowDisplaySize,
    };

    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &newArrowSprite, pSurfaceWindow, &arrowPosSDL);
}


struct Position onPacmanGridMove(struct Position *pacmanUiPos)
{
    removeMazeElement(PACMAN, entityMaze);
    MazeElement entityElement = getMazeElementAt(pacmanGridPos, entityMaze);

    switch (entityElement) {
        case RED_GHOST:
            handleGhostCollision(RED_GHOST);
            return *pacmanUiPos;
        case PINK_GHOST:
            handleGhostCollision(PINK_GHOST);
            return *pacmanUiPos;
        case BLUE_GHOST:
            handleGhostCollision(BLUE_GHOST);
            return *pacmanUiPos;
        case ORANGE_GHOST:
            handleGhostCollision(ORANGE_GHOST);
            return *pacmanUiPos;
    }

    MazeElement propsElement = getMazeElementAt(pacmanGridPos, propsMaze);
    switch (propsElement)
    {
    case LEFT_TELEPORTER:
        return teleportPacman(RIGHT_TELEPORTER);
    case RIGHT_TELEPORTER:
        return teleportPacman(LEFT_TELEPORTER);
    case SMALL_COIN:
        playDotSound();
        incrementScore(10);
        setMazeElementAt(pacmanGridPos, EMPTY, propsMaze);
        handleCoinCollision();
        break;
    case BIG_COIN:
        incrementScore(50);
        makeGhostsEatable();
        setMazeElementAt(pacmanGridPos, EMPTY, propsMaze);
        handleCoinCollision();
        break;
    case FRUIT:
        handleFruitCollision();
    default:
        break;
    }

    setMazeElementAt(pacmanGridPos, PACMAN, entityMaze);

    return *pacmanUiPos;
}

bool isScoreAnimationOnGhostEaten()
{
    return eatGhostAnimationTimer.isRunning;
}

struct Position teleportPacman(MazeElement teleporter)
{
    pacmanGridPos = getMazePositionOfElement(teleporter, initialMaze);
    return gridPosToUiPos(pacmanGridPos);
}

struct SDL_Rect getArrow(Direction direction)
{
    SDL_Rect arrow = arrowSprite;
    arrow.x += (int)direction * arrow.w;
    return arrow;
}

void endEatGhostAnimation() {
    isGamePause = false;
}

void handleGhostCollision(MazeElement ghostElement)
{
    if (isGhostEatable()) pacmanEatGhost(ghostElement);
    else killPacman();
}

void killPacman()
{
    removeMazeElement(PACMAN, entityMaze);
    decrementLives();
    isGamePause = true;
    startPacmanDeathAnimation();
}

void pacmanEatGhost(MazeElement ghostElement)
{
    removeMazeElement(ghostElement, entityMaze);
    setMazeElementAt(pacmanGridPos, PACMAN, entityMaze);
    ghostEaten++;

    playAudioWithChannel(audioEatGhost, CHANNEL_EAT_GHOST);

    incrementScore(getEatenGhostScore(ghostEaten));

    setTimerCallback(&eatGhostAnimationTimer, endEatGhostAnimation);

    resetTimer(&eatGhostAnimationTimer);
    startTimer(&eatGhostAnimationTimer);

    isGamePause = true;
    ghostElementEaten = ghostElement;
}

void startPacmanDeathAnimation() {

    setTimerCallback(&pacmanDeathAnimationDelayTimer, endPacmanDeathDelay);
    setTimerCallback(&pacmanDeathAnimationTimer, endPacmanDeathAnimation);

    stopSirenOrPowerUpSound();
    playAudioWithChannel(audioDeath, CHANNEL_DEATH);

    isGamePause = true;

    resetTimer(&pacmanDeathAnimationTimer);
    resetTimer(&pacmanDeathAnimationDelayTimer);
    startTimer(&pacmanDeathAnimationDelayTimer);
}

void endPacmanDeathDelay() {
    if (pacmanDeathAnimationTimer.isFinished) {
        // After animation delay end
        afterPacmanDeath();

    } else {
        // Before animation delay end
        startTimer(&pacmanDeathAnimationTimer);
    }
}

void endPacmanDeathAnimation() {
    resetTimer(&pacmanDeathAnimationDelayTimer);
    startTimer(&pacmanDeathAnimationDelayTimer);
}

void afterPacmanDeath() {
    isGamePause = false;

    if (getLives() <= 0)
    {
        setTimerCallback(&gameOverTimer, afterGameOverAnimation);
        resetTimer(&gameOverTimer);
        startTimer(&gameOverTimer);
        return;
    }

    resetFruit();
    spawnPacman();
    spawnGhosts();
    startReady(READY_DURATION);

}

void handleCoinCollision() {

    incrementEatenDotsCount();

    int eatenDotsCount = getEatenDotsCount();
    if (eatenDotsCount == getInitialDotsCount()) nextRound();
    if (eatenDotsCount == FRUIT_SPAWN_1 || eatenDotsCount == FRUIT_SPAWN_2) spawnFruit();
}
