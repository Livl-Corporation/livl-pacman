#ifndef PACMAN_FILE_FUNCTIONS_H
#define PACMAN_FILE_FUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include "console_handler.h"

FILE *initFile(const char *filename, char mode);
bool fill2DArrayFromFile(FILE *file, char **array, int row, int col, int amountCharToSkip);
void closeFile(FILE *file);

#endif // PACMAN_FILE_FUNCTIONS_H
