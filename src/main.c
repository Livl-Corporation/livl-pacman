#include "utilities/sdl_functions.h"
#include "ui/menu_window.h"

int main(void)
{
    initSDL();
    initSDLMixer();

    loadMedia();
    loadSound();

    startMainMenuLoop();

    closeWindow();

    return 0;
}
