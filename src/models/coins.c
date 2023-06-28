//
// Created by Franck GUTMANN on 27/06/2023.
//

#include "coins.h"

SDL_Rect imgSmallCoinSprite = {163, 96, 2, 2};
SDL_Rect imgBigCoinSprite = {177, 93, 7, 7};

void refillCoins() {

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position position = {j, i};
            MazeElement element = getMazeElementAt(position, initialMaze);

            if (element == SMALL_COIN || element == BIG_COIN)
                setMazeElementAt(position, element, propsMaze);
        }

    }

}

void drawCoins(int frameCount)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Position gridPos = {j, i};
            struct Position uiPos = gridPosToUiPos(gridPos);

            MazeElement mazeElement = getMazeElementAt(gridPos, propsMaze);

            switch (mazeElement)
            {
                case SMALL_COIN:
                    blitRectWithOffset(imgSmallCoinSprite, uiPos, SMALL_COIN_OFFSET_X, SMALL_COIN_OFFSET_Y, SMALL_COIN_WIDTH, SMALL_COIN_HEIGHT);
                    break;

                case BIG_COIN:
                    if (frameCount % BIG_COIN_RATE)
                        blitRectWithOffset(imgBigCoinSprite, uiPos, BIG_COIN_OFFSET_X, BIG_COIN_OFFSET_Y, BIG_COIN_WIDTH, BIG_COIN_HEIGHT);
                    break;

                default:
                    break;
            }
        }
    }
}
