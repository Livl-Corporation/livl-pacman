#include "utilities/sdl_functions.h"
#include "ui/menu_window.h"

int main(void)
{
    initSDL();

    loadMedia();

    startMenu();

    closeWindow();

    return 0;
}
