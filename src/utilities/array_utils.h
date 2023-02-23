//
// Created by Franck GUTMANN on 23/02/2023.
//

#ifndef PACMAN_ARRAY_UTILS_H
#define PACMAN_ARRAY_UTILS_H

#include <stdlib.h>
#include "models/position.h"

/**
 * Allocate a 2D array
 * @param array
 * @param rows
 * @param columns
 */
void allocate2DArray(char ***array, int rows, int columns);

/**
 * Free a 2D array
 * @param array 
 * @param rows
 */
void free2DArray(char **array, int rows);

/**
 * Copy a 2D array
 * @param source
 * @param destination
 * @param rows
 * @param columns
 */
void copy2DArray(char **source, char **destination, int rows, int columns);

/**
 * Print a 2D array
 * @param array
 * @param rows
 * @param columns
 */
void print2DArray(char **array, int rows, int columns);

/**
 * Get the element at a specific position in the array
 * @param array
 * @param row
 * @param column
 * @return the element
 */
char get2DArrayElement(char **array, int row, int column);

/**
 * Find an element in the array
 * @param array
 * @param rows
 * @param columns
 * @param element
 * @return Position of the element, (-1, -1) if not found
 */
struct Position find2DArrayElement(char **array, int rows, int columns, char element);

#endif //PACMAN_ARRAY_UTILS_H
