#include "console_handler.h"

void ConsoleHandlerDisplayMessage(const char *message, ...) {
    va_list args;
    va_start(args, message);
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, message, args);
    va_end(args);
}

void ConsoleHandlerDisplayError(const char *error, ...) {
    va_list args;
    va_start(args, error);
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, error, args);
    va_end(args);
}