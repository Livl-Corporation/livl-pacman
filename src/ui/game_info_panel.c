#include "game_info_panel.h"

SDL_Rect imgNumbersSprite[10];
SDL_Rect imgNumberSprite = {4, 256, 7, 7};

SDL_Rect imgPacmanLeftSprite = {56, 90, 14, 14};
SDL_Rect imgHighScoreTextSprite = {3, 70, 80, 10};
SDL_Rect imgOneUpTextSprite = {4, 81, 22, 7};

SDL_Rect imgScoreUi = {68, 35, 20, 18};

int uiScoreMargin = 13;
int uiLivesMargin = 15;
int spriteNumberMargin = 8;

void initGameInfoPanel()
{
    initImgNumbersOnSprite();
}

void initImgNumbersOnSprite()
{
    for(int i=0; i<10; i++)
    {
        imgNumbersSprite[i].x = imgNumberSprite.x;
        imgNumbersSprite[i].y = imgNumberSprite.y;
        imgNumbersSprite[i].h = imgNumberSprite.h;
        imgNumbersSprite[i].w = imgNumberSprite.w;

        imgNumberSprite.x += spriteNumberMargin;
    }
}

void drawGameInfoPanel()
{
    drawHighScore();
    drawScore(getScore(), imgScoreUi);
    drawLives();
    drawUp();
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
    char scoreString[scoreStringLength]; // String to hold the score
    snprintf(scoreString, sizeof(scoreString), "%d", score);

    for (int i = 0; scoreString[i] != '\0'; i++)
    {
        int digit = scoreString[i] - '0';  // Convert character to integer

        // Blit the number sprite onto the window surface
        SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgNumbersSprite[digit], pSurfaceWindow, &imgUi);

        // Increment xPosition to position the next digit
        imgUi.x += imgNumbersSprite[digit].w + uiScoreMargin;
    }
}

void drawLives()
{
    SDL_Rect imgLivesUi = {15, TOTAL_SCREEN_HEIGHT - 33, 25, 25};
    for (int i = 0; i < getLives()-1; i++)
    {
        // Blit the number sprite onto the window surface
        SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPacmanLeftSprite, pSurfaceWindow, &imgLivesUi);

        // Increment xPosition to position the next digit
        imgLivesUi.x += imgPacmanLeftSprite.w + uiScoreMargin;
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

    return count+1; // +1 for the /0
}