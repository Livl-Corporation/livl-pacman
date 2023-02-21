#ifndef PACMAN_CONSOLE_HANDLER_H
#define PACMAN_CONSOLE_HANDLER_H

#include <stdbool.h>
#include <SDL_pixels.h>
#include <SDL_log.h>

void ConsoleHandlerDisplayMessage(const char *message, ...);
void ConsoleHandlerDisplayError(const char *error, ...);


#endif //PACMAN_CONSOLE_HANDLER_H
