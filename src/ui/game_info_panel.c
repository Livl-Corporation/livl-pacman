#include "game_info_panel.h"

SDL_Rect imgNumbersSprite[10];
SDL_Rect imgPacmanLeft = {56, 90, 14, 14};

int uiScoreOriginX = 15;
int uiScoreOriginY = HEADER_SCREEN_HEIGHT - 25;
int uiScoreHeight = 20;
int uiScoreWidth = 18;
int uiScoreMargin = 13;

int uiLivesOriginX = 15;
int uiLivesOriginY = TOTAL_SCREEN_HEIGHT - 75;
int uiLivesHeight = 25;
int uiLivesWidth = 25;
int uiLivesMargin = 15;

int spriteNumberOriginX = 4;
int spriteNumberOriginY = 256;
int spriteNumberMargin = 8;
int spriteNumberHeight = 7;
int spriteNumberWidth = 7;

void initGameInfoPanel()
{
    initImgNumbersOnSprite();
}

void initImgNumbersOnSprite()
{
    int xPosition = spriteNumberOriginX;
    for(int i=0; i<10; i++)
    {
        imgNumbersSprite[i].x = xPosition;
        imgNumbersSprite[i].y = spriteNumberOriginY;
        imgNumbersSprite[i].h = spriteNumberHeight;
        imgNumbersSprite[i].w = spriteNumberWidth;

        xPosition += spriteNumberMargin;
    }
}

void drawGameInfoPanel()
{
    drawScore();
    drawLives();
}

void drawScore()
{
    char scoreString[100]; // String to hold the score
    snprintf(scoreString, sizeof(scoreString), "%d", getScore());

    int xPosition = uiScoreOriginX;
    for (int i = 0; scoreString[i] != '\0'; i++)
    {
        int digit = scoreString[i] - '0';  // Convert character to integer

        // Blit the number sprite onto the window surface
        SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgNumbersSprite[digit], pSurfaceWindow, &(SDL_Rect){xPosition, uiScoreOriginY, uiScoreWidth, uiScoreHeight});

        // Increment xPosition to position the next digit
        xPosition += imgNumbersSprite[digit].w + uiScoreMargin;
    }
}

void drawLives()
{
    int xPosition = uiLivesOriginX;
    for (int i = 0; i < getLives()-1; i++)
    {
        // Blit the number sprite onto the window surface
        SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgPacmanLeft, pSurfaceWindow, &(SDL_Rect){xPosition, uiLivesOriginY + uiLivesHeight + uiLivesMargin, uiLivesWidth, uiLivesHeight});

        // Increment xPosition to position the next digit
        xPosition += imgPacmanLeft.w + uiScoreMargin;
    }
}