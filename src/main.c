#include "utilities/sdl_functions.h"
#include "ui/menu_window.h"

int main(void)
{
    initSDL();

    loadMedia();

    startMainMenuLoop();

    closeWindow();

    return 0;
}
