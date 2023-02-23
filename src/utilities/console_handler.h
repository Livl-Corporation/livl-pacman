#ifndef PACMAN_CONSOLE_HANDLER_H
#define PACMAN_CONSOLE_HANDLER_H

#include <stdbool.h>
#include <SDL_pixels.h>
#include <SDL_log.h>

/**
 * Display a message in the console
 * @param message
 * @param ...
 */
void ConsoleHandlerDisplayMessage(const char *message, ...);

/**
 * Display an error in the console
 * @param error
 * @param ...
 */
void ConsoleHandlerDisplayError(const char *error, ...);

#endif //PACMAN_CONSOLE_HANDLER_H
