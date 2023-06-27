#include "utilities/sdl_functions.h"
#include "ui/menu_window.h"
#include "models/audio.h"

int main(void)
{
    initSDL();
    initSDL_Mixer();

    initAudio();
    loadMedia();

    startMenu();

    closeWindow();
    closeSDL_Mixer();

    return 0;
}
