#include "game_info_panel.h"

/**
 * @brief Get the img Numbers On Sprite image from number 0 to 9
 */
SDL_Rect imgNumbersSprite[10];
SDL_Rect imgNumberSprite = {4, 256, 7, 7};

SDL_Rect imgPacmanLeftSprite = {56, 90, 14, 14};
SDL_Rect imgHighScoreTextSprite = {3, 70, 80, 10};
SDL_Rect imgOneUpTextSprite = {140, 124, 22, 7};

SDL_Rect imgScoreUi = {68, 35, 20, 18};

/**
 * @brief Get the img Numbers On Sprite image from number 200, 400, 800, 1600
 */
SDL_Rect imgNumbersEatGhostSprite[GHOST_COUNT];
SDL_Rect imgEatGhostTextSprite = {154, 176, GHOST_SCORE_W, GHOST_SCORE_H};

bool isOneUpVisible = true;

void initGameInfoPanel()
{
    initImgNumbersOnSprite();
    initImgNumbersEatGhostSprite();
}

void initImgNumbersOnSprite()
{
    for (int i = 0; i < 10; i++)
    {
        imgNumbersSprite[i].x = imgNumberSprite.x;
        imgNumbersSprite[i].y = imgNumberSprite.y;
        imgNumbersSprite[i].h = imgNumberSprite.h;
        imgNumbersSprite[i].w = imgNumberSprite.w;

        imgNumberSprite.x += NUMBER_SPRITES_SPACING;
    }
}

void initImgNumbersEatGhostSprite()
{
    for (int i = 0; i < GHOST_COUNT; i++)
    {
        imgNumbersEatGhostSprite[i].x = imgEatGhostTextSprite.x;
        imgNumbersEatGhostSprite[i].y = imgEatGhostTextSprite.y;
        imgNumbersEatGhostSprite[i].h = imgEatGhostTextSprite.h;
        imgNumbersEatGhostSprite[i].w = imgEatGhostTextSprite.w;

        imgEatGhostTextSprite.y += GHOST_SCORES_SPACING;
    }
}

void drawGameInfoPanel()
{
    drawHighScore();
    drawScore(getScore(), imgScoreUi);
    drawLives();
    if (frameCount % TEXT_UP_RATE)
        drawUp();

    if (isScoreAnimationOnGhostEaten())
    {
        decreaseScoreAnimationOnGhostEaten();
        drawEatGhostScore(
            getEatenGhostScore(ghostEaten),
            ghostEaten,
            (SDL_Rect){
                pacmanUIPos.x - GHOST_SCORE_W,
                pacmanUIPos.y + GHOST_SCORE_H,
                GHOST_SCORE_W * GHOST_SCORE_UI_SCALE,
                GHOST_SCORE_H * GHOST_SCORE_UI_SCALE,
            });
    }
}

void drawHighScore()
{
    SDL_Rect imgHighScoreTextUi = {170, 8, 202, 26};
    SDL_Rect imgHighScoreValueUi = {250, 35, 20, 18};
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

void drawEatGhostScore(int score, int ghostEaten, SDL_Rect imgUi)
{
    int scoreSpriteIndex = fmin(ghostEaten, SCORE_GHOST_MAX_COMBO) - 1;
    SDL_Rect rectScoreToDisplay = imgNumbersEatGhostSprite[scoreSpriteIndex];
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &rectScoreToDisplay, pSurfaceWindow, &imgUi);
}

void drawLives()
{
    SDL_Rect imgLivesUi = {15, TOTAL_SCREEN_HEIGHT - 33, 25, 25};
    for (int i = 0; i < getLives() - 1; i++)
    {
        // Blit the number sprite onto the window surface
        SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPacmanLeftSprite, pSurfaceWindow, &imgLivesUi);

        // Increment xPosition to position the next digit
        imgLivesUi.x += imgPacmanLeftSprite.w + NUMBER_UI_SPACING;
    }
}

void drawUp()
{
    SDL_Rect imgOneUpUi = {40, 13, 50, 18};
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgOneUpTextSprite, pSurfaceWindow, &imgOneUpUi);
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