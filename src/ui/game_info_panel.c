#include "game_info_panel.h"

SDL_Rect imgPacmanLeftSprite = {56, 90, 14, 14};
SDL_Rect imgHighScoreTextSprite = {3, 70, 80, 10};
SDL_Rect imgOneUpTextSprite = {140, 124, 22, 7};

SDL_Rect imgGameOverUi = {185, 458, GAME_OVER_W *GAME_OVER_UI_SCALE, GAME_OVER_H *GAME_OVER_UI_SCALE};
SDL_Rect imgGameOverSprite = {4, 54, GAME_OVER_W, GAME_OVER_H};

SDL_Rect imgReadyOnSprite = {4, 63, READY_W, READY_H};

/**
 * @brief Get the img Numbers On Sprite image from number 0 to 9
 */
SDL_Rect imgNumbersSprite[10];
SDL_Rect imgNumberSprite = {4, 256, 7, 7};

/**
 * @brief Place where the main score is displayed on the UI
 */
SDL_Rect imgScoreUi = {68, 35, 20, 18};

/**
 * @brief Ghost score numbers on sprite (200, 400, 800, 1600)
 */
SDL_Rect imgNumbersEatGhostSprite[GHOST_COUNT];
SDL_Rect imgEatGhostTextSprite = {154, 176, GHOST_SCORE_W, GHOST_SCORE_H};

// UI positions

SDL_Rect imgHighScoreTextUi = {170, 8, 202, 26};
SDL_Rect imgHighScoreValueUi = {250, 35, 20, 18};

SDL_Rect imgOneUpUi = {40, 13, 50, 18};

SDL_Rect imgLivesUi = {15, TOTAL_SCREEN_HEIGHT - BOTTOM_BAR_SPACING, 25, 25};

SDL_Rect fruitBarPos = {
    TOTAL_SCREEN_WIDTH - FRUIT_BAR_RIGHT_MARGIN,
    TOTAL_SCREEN_HEIGHT - BOTTOM_BAR_SPACING,
    FRUIT_SIZE *FRUIT_BAR_UI_SCALE,
    FRUIT_SIZE *FRUIT_BAR_UI_SCALE,
};

void initGameInfoPanel()
{
    exportSprites(&imgNumberSprite, imgNumbersSprite, 10, NUMBER_SPRITES_SPACING, 0);
    exportSprites(&imgEatGhostTextSprite, imgNumbersEatGhostSprite, GHOST_COUNT, 0, GHOST_SCORES_SPACING);
}

void drawGameInfoPanel()
{
    drawHighScore();
    drawScore(getScore(), imgScoreUi);
    drawLives();
    drawFruitBar();
    if (frameCount % TEXT_UP_RATE)
        drawUp();

    if (isScoreAnimationOnGhostEaten())
    {
        drawEatGhostScore(
            ghostEaten,
            (SDL_Rect){
                pacmanUIPos.x - GHOST_SCORE_W,
                pacmanUIPos.y + GHOST_SCORE_H,
                GHOST_SCORE_W * GHOST_SCORE_UI_SCALE,
                GHOST_SCORE_H * GHOST_SCORE_UI_SCALE,
            });
    }

    if (gameOverTimer.isRunning)
        drawGameOver();
}

void drawHighScore()
{
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgHighScoreTextSprite, pSurfaceWindow, &imgHighScoreTextUi);
    drawScore(getHighScore(), imgHighScoreValueUi);
}

void drawScore(int score, SDL_Rect imgUi)
{
    int scoreStringLength = getNumDigits(score); // Include space for null terminator
    char scoreString[scoreStringLength];         // String to hold the score
    snprintf(scoreString, sizeof(scoreString), "%d", score);

    for (int i = 0; scoreString[i] != '\0'; i++)
    {
        int digit = scoreString[i] - '0'; // Convert character to integer

        // Blit the number sprite onto the window surface
        SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgNumbersSprite[digit], pSurfaceWindow, &imgUi);

        // Increment xPosition to position the next digit
        imgUi.x += imgNumbersSprite[digit].w + NUMBER_UI_SPACING;
    }
}

void drawEatGhostScore(int eatenGhostCount, SDL_Rect imgUi)
{
    int scoreSpriteIndex = fmin(eatenGhostCount, SCORE_GHOST_MAX_COMBO) - 1;
    SDL_Rect rectScoreToDisplay = imgNumbersEatGhostSprite[scoreSpriteIndex];
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &rectScoreToDisplay, pSurfaceWindow, &imgUi);
}

void drawLives()
{
    SDL_Rect livePos = imgLivesUi;
    for (int i = 0; i < getLives() - 1; i++)
    {
        // Blit the number sprite onto the window surface
        SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPacmanLeftSprite, pSurfaceWindow, &livePos);

        // Increment xPosition to position the next digit
        livePos.x += imgPacmanLeftSprite.w + NUMBER_UI_SPACING;
    }
}

void drawUp()
{
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgOneUpTextSprite, pSurfaceWindow, &imgOneUpUi);
}

void drawGameOver()
{
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgGameOverSprite, pSurfaceWindow, &imgGameOverUi);
}

void drawReady()
{
    struct Position position = gridPosToUiPos((struct Position){8, 15});
    SDL_Rect imgReadyOnUi = {position.x, position.y, READY_W * READY_UI_SCALE, READY_H * READY_UI_SCALE};
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, false, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgReadyOnSprite, pSurfaceWindow, &imgReadyOnUi);
}

int getNumDigits(int score)
{
    if (score == 0)
        return 2;

    int count = 0;
    while (score != 0)
    {
        score /= 10;
        count++;
    }

    return count + 1; // +1 for the /0
}

void drawFruitBar()
{
    int displayedFruits = fmin(getRound(), FRUIT_BAR_MAX_FRUITS);
    for (int i = 0; i < displayedFruits; i++)
    {

        int fruitLevel = getFruitLevel(getRound() - i);

        SDL_Rect fruitUiPos = {
            fruitBarPos.x - (i * (FRUIT_SIZE * FRUIT_BAR_UI_SCALE) + FRUIT_BAR_SPACING),
            fruitBarPos.y,
            fruitBarPos.w,
            fruitBarPos.h,
        };
        SDL_BlitScaled(pSurfacePacmanSpriteSheet, &fruitsRects[fruitLevel], pSurfaceWindow, &fruitUiPos);
    }
}