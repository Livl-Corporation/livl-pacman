#include "sdl_functions.h"

SDL_Window *pWindow = NULL;
SDL_Surface *pSurfaceWindow = NULL;
SDL_Surface *pSurfacePacmanSpriteSheet = NULL;
SDL_Surface *pSurfacePlayButton = NULL;

Mix_Chunk *soundMenu = NULL;

void initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation of the SDL");

    pWindow = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TOTAL_SCREEN_WIDTH, TOTAL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (pWindow == NULL)
        SDL_ExitWithError("Creation of the SDL window");

    pSurfaceWindow = SDL_GetWindowSurface(pWindow);
    if (pSurfaceWindow == NULL)
        SDL_ExitWithError("Creation of the SDL window surface");
}

void loadMedia()
{
    pSurfacePacmanSpriteSheet = SDL_LoadBMP(PATH_SPRITE_SHEET_PACMAN);
    if (pSurfacePacmanSpriteSheet == NULL)
        SDL_ExitWithError("Loading of the sprite-sheet");

    pSurfacePlayButton = SDL_LoadBMP(PATH_SPRITE_SHEET_PLAY_BTN);
    if (pSurfacePlayButton == NULL)
        SDL_ExitWithError("Loading of the button play");
}

void initSDLMixer()
{
    int audioFlags = MIX_INIT_MP3;  // Choose the audio format you want to use (e.g., OGG)

    // Initialize SDL_mixer
    if (Mix_Init(audioFlags) != audioFlags)
    {
        printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
    }

    // Open the audio device
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        printf("Failed to open audio: %s\n", Mix_GetError());
    }

}

void loadSound()
{
    soundMenu = Mix_LoadWAV(PATH_SOUND_WII);
    if (soundMenu == NULL)
    {
        char message[100];
        sprintf(message, "Failed to load sound: %s\n", Mix_GetError());
        SDL_ExitWithError(message);
    }
}

void playSound(Mix_Chunk *sound)
{
    Mix_PlayChannel(-1, sound, 0);  // Play the sound on any available channel
}

void SDL_ExitWithError(const char *message)
{
    ConsoleHandlerDisplayError("%s > %s", message, SDL_GetError());
    closeWindow();
    exit(EXIT_FAILURE);
}

void SDLMixer_FreeAudio(Mix_Chunk *sound)
{
    Mix_FreeChunk(sound);
}

void SDLMixer_CleanupAudio()
{
    Mix_CloseAudio();
    Mix_Quit();
}

void closeWindow()
{
    ConsoleHandlerDisplayMessage("Freeing SDL Surfaces and Window.");
    SDL_FreeSurface(pSurfacePacmanSpriteSheet);
    SDL_FreeSurface(pSurfacePlayButton);
    SDL_FreeSurface(pSurfaceWindow);
    SDL_DestroyWindow(pWindow);
    SDLMixer_CleanupAudio();
    SDL_Quit();
}