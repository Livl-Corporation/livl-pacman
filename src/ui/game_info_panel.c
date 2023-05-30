#include "game_info_panel.h"

SDL_Rect imgNumbersSprite[10];

int uiScoreOriginX = 10;
int uiScoreOriginY = 50;
int uiScoreHeight = 20;
int uiScoreWidth = 18;
int uiScoreMargin = 15;

int spriteNumberOriginX = 11;
int spriteNumberOriginY = 53;
int spriteNumberMargin = 8;
int spriteNumberHeight = 7;
int spriteNumberWidth = 7;

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

void drawScore()
{
    char scoreString[100]; // String to hold the score
    snprintf(scoreString, sizeof(scoreString), "%d", 1023);

    int xPosition = uiScoreOriginX;
    for (int i = 0; scoreString[i] != '\0'; i++)
    {
        int digit = scoreString[i] - '0';  // Convert character to integer

        // Blit the number sprite onto the window surface
        SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgNumbersSprite[digit-1], pSurfaceWindow, &(SDL_Rect){xPosition, uiScoreOriginY, uiScoreWidth, uiScoreHeight});

        // Increment xPosition to position the next digit
        xPosition += imgNumbersSprite[digit].w + uiScoreMargin;
    }
}