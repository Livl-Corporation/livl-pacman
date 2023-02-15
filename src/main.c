#include "main.h"

int main(void)
{
    initSDL();

    loadMedia();

    startMainMenuLoop();

    closeWindow();

    return 0;
}
