#include "game_window.h"

int count = 0;

bool pGameQuit = false;
MovementDirection actualPacmanMovementDirection = MOVEMENT_DIRECTION_RIGHT;

SDL_Rect imgMazeBlueCoins = {200, 3, 168, 216 };
SDL_Rect imgMazeBlueCoinsZoom = {4, 4, 672, 864 };

SDL_Rect ghostRedEyesRight = {3, 123, 16, 16 };
SDL_Rect ghostRedEyesLeft = {37, 123, 16, 16 };
SDL_Rect ghostRedEyesDown = {105, 123, 16, 16 };
SDL_Rect ghostRedEyesUp = {71, 123, 16, 16 };
SDL_Rect ghostRedZoom = {34, 34, 36, 36 };

void initLoadMaze()
{
    if(pacmanMazeArray == NULL)
    {
        if(!retrieveMazeFromFile())
        {
            ConsoleHandlerDisplayError("while retrieving maze from file.");
            pGameQuit = true;
        }
    }
}

void startGameLoop()
{
    initLoadMaze();

    while (!pGameQuit)
    {
        handleGameEvents();

        drawGame();

        SDL_Delay(20); // ~50 fps use SDL_GetTicks64() pour plus de precision

        SDL_UpdateWindowSurface(pWindow);
    }


    freeMaze();
}

MovementDirection getMovementDirectionFromKey(SDL_Keycode key)
{
    switch (key) {
        case SDLK_LEFT:
            return MOVEMENT_DIRECTION_LEFT;
        case SDLK_RIGHT:
            return MOVEMENT_DIRECTION_RIGHT;
        case SDLK_UP:
            return MOVEMENT_DIRECTION_UP;
        case SDLK_DOWN:
            return MOVEMENT_DIRECTION_DOWN;
        default:
            return -1;
    }
}

bool handleGameEvents()
{
    SDL_Event event;

    while (!pGameQuit && SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                pGameQuit = true;
                break;
        }
    }

    int numberOfKeyboardScancodes;
    const Uint8* keys = SDL_GetKeyboardState(&numberOfKeyboardScancodes);

    //actualPacmanMovementDirection = getMovementDirectionFromKey(event.key.keysym.sym);

    if (keys[SDL_SCANCODE_ESCAPE])
        pGameQuit = true;
    if (keys[SDL_SCANCODE_LEFT])
        SDL_Log("LEFT");
    if (keys[SDL_SCANCODE_RIGHT])
        SDL_Log("RIGHT");
    if (keys[SDL_SCANCODE_UP])
        SDL_Log("UP");
    if (keys[SDL_SCANCODE_DOWN])
        SDL_Log("DOWN");
}

SDL_Point getPacmanPosition(const SDL_Rect pacman)
{
    SDL_Point position;

    if (actualPacmanMovementDirection == MOVEMENT_DIRECTION_LEFT) {
        position.x = pacman.x - 1;
        position.y = pacman.y + pacman.h / 2;
    } else if (actualPacmanMovementDirection == MOVEMENT_DIRECTION_RIGHT) {
        position.x = pacman.x + pacman.w + 1;
        position.y = pacman.y + pacman.h / 2;
    } else if (actualPacmanMovementDirection == MOVEMENT_DIRECTION_UP) {
        position.x = pacman.x + pacman.w  / 2;
        position.y = pacman.y - 1;
    } else if (actualPacmanMovementDirection == MOVEMENT_DIRECTION_DOWN) {
        position.x = pacman.x + pacman.w  / 2;
        position.y = pacman.y + pacman.h + 1;
    }

    position.x = position.x / SQUARE_WIDTH;
    position.y = position.y / SQUARE_HEIGHT;

    return position;
}

void drawGame()
{
    SDL_SetColorKey(pSurfacePacmanSpriteSheet, false, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &imgMazeBlueCoins, pSurfaceWindow, &imgMazeBlueCoinsZoom);

    SDL_Rect* newGhost = NULL;
    switch (count/128)
    {
        case 0:
            newGhost = &(ghostRedEyesRight);
            actualPacmanMovementDirection = MOVEMENT_DIRECTION_RIGHT;
            ghostRedZoom.x++;
            break;
        case 1:
            newGhost = &(ghostRedEyesDown);
            actualPacmanMovementDirection = MOVEMENT_DIRECTION_DOWN;
            ghostRedZoom.y++;
            break;
        case 2:
            newGhost = &(ghostRedEyesLeft);
            actualPacmanMovementDirection = MOVEMENT_DIRECTION_LEFT;
            ghostRedZoom.x--;
            break;
        case 3:
            newGhost = &(ghostRedEyesUp);
            actualPacmanMovementDirection = MOVEMENT_DIRECTION_UP;
            ghostRedZoom.y--;
            break;
    }

    SDL_Rect ghost_in2 = *newGhost;

    SDL_Point pacmanPosition = getPacmanPosition(ghostRedZoom);
    MazeElement mazeElement = getCoordinateMazeElement(pacmanPosition.y, pacmanPosition.x);
    ConsoleHandlerDisplayMessage("row %d - col %d - maze '%c'", pacmanPosition.y, pacmanPosition.x, (char)mazeElement);

    SDL_SetColorKey(pSurfacePacmanSpriteSheet, true, 0);
    SDL_BlitScaled(pSurfacePacmanSpriteSheet, &ghost_in2, pSurfaceWindow, &ghostRedZoom);
}