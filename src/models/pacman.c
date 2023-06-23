//
// Created by Franck GUTMANN on 15/02/2023.
//

#include "pacman.h"

SDL_Rect pacmanSprites[DIRECTION_COUNT];
SDL_Rect pacmanRoundSprite = {4, 90, PACMAN_SIZE, PACMAN_SIZE};

SDL_Rect pacmanDeathAnimation[PACMAN_DEATH_ANIMATION_FRAMES];

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
    pacmanSpawnPos = getInitialPositionOfElement(PACMAN);

    pacmanGridPos = pacmanSpawnPos;
    pacmanUIPos = gridPosToUiPos(pacmanGridPos);

    pacmanDirection = defaultDirection;
    pacmanWishedDirection = defaultDirection;

    lastPacmanDirection = pacmanRoundSprite;
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
    // Don't draw Pacman if he is dead and the death animation is finished
    if(pacmanDeathAnimationTimer.isFinished && pacmanDeathAnimationDelayTimer.isRunning) return;

    if (isGamePause)
    {

        if (pacmanDeathAnimationTimer.isRunning) {

            int pacmanDeathAnimationIndex = (1 - ((float)pacmanDeathAnimationTimer.count / (float)pacmanDeathAnimationTimer.initialCount)) * PACMAN_DEATH_ANIMATION_FRAMES;
            pacmanBlit(pacmanDeathAnimation[pacmanDeathAnimationIndex]);
            return;
        }

        if (isScoreAnimationOnGhostEaten())
            return;

        pacmanBlit(lastPacmanDirection);
        return;
    }

    SDL_Rect newPacman = {0, 0, 0, 0};

    // Copy pacman position to a new
    struct Position pacmanPosCopy = pacmanUIPos;

    // Test is wished direction can be applied
    if (pacmanDirection != pacmanWishedDirection && canMoveInDirection(pacmanWishedDirection))
        pacmanDirection = pacmanWishedDirection;

    int pacmanAnimation = (frameCount / ANIMATION_SPEED) % PACMAN_SPRITE_MOUTHS_DIRECTION;

    // Then we can choose the sprite corresponding to direction
    if (pacmanAnimation == PACMAN_SPRITE_MOUTHS_DIRECTION - 1)
    {
        newPacman = pacmanRoundSprite;
    }
    else
    {
        newPacman = pacmanSprites[pacmanDirection];
        newPacman.x += pacmanAnimation * (PACMAN_SIZE + PACMAN_SPACING_X);
    }

    // Calculate the target UI position
    updatePosition(&pacmanPosCopy, pacmanDirection, 1);

    if (hasCollision(pacmanPosCopy, CELL_SIZE - 1))
    {
        // If pacman ran into obstacle, just blit him at without updating his position
        pacmanBlit(lastPacmanDirection);
        return;
    }

    // Get target pacman position in grid
    struct Position newPacmanGridPos = uiPosToGridPos(getCellCenter(pacmanPosCopy));

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
    removeMazeElement(PACMAN);
    MazeElement element = getMazeElementAt(pacmanGridPos);

    switch (element)
    {
    case LEFT_TELEPORTER:
        return teleportPacman(RIGHT_TELEPORTER);
    case RIGHT_TELEPORTER:
        return teleportPacman(LEFT_TELEPORTER);
    case SMALL_COIN:
        playDotSound();
        incrementScore(10);
        setMazeElementAt(pacmanGridPos, EMPTY);
        handleCoinCollision();
        break;
    case BIG_COIN:
        incrementScore(50);
        makeGhostsEatable();
        setMazeElementAt(pacmanGridPos, EMPTY);
        handleCoinCollision();
        break;
    case RED_GHOST:
        handleGhostCollision(RED_GHOST);
        break;
    case PINK_GHOST:
        handleGhostCollision(PINK_GHOST);
        break;
    case BLUE_GHOST:
        handleGhostCollision(BLUE_GHOST);
        break;
    case ORANGE_GHOST:
        handleGhostCollision(ORANGE_GHOST);
        break;
    case FRUIT:
        handleFruitCollision();
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

bool isScoreAnimationOnGhostEaten()
{
    return eatGhostAnimationTimer.isRunning;
}

struct Position teleportPacman(MazeElement teleporter)
{
    pacmanGridPos = getInitialPositionOfElement(teleporter);
    return gridPosToUiPos(pacmanGridPos);
}

struct SDL_Rect getArrow(Direction direction)
{
    SDL_Rect arrow = arrowSprite;
    arrow.x += direction * arrow.w;
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
    removeMazeElement(PACMAN);
    decrementLives();
    isGamePause = true;
    startPacmanDeathAnimation();
}

void pacmanEatGhost(MazeElement ghostElement)
{
    removeMazeElement(ghostElement);
    setMazeElementAt(pacmanGridPos, PACMAN);
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
