#include "main.h"
#include "pacman.h"

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv)
{
    initSDL();

    loadMedia();

    displayMainMenu();

    closeWindow();

    return 0;
}
