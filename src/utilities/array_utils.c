//
// Created by Franck GUTMANN on 23/02/2023.
//

#include "array_utils.h"

void allocate2DArray(char ***array, int rows, int columns) {

        *array = (char **) malloc(rows * sizeof(char *));

        for (int i = 0; i < rows; i++) {
            (*array)[i] = (char *) malloc(columns * sizeof(char));
        }
}

void free2DArray(char **array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

void copy2DArray(char **source, char **destination, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

char get2DArrayElement(char **array, int row, int column) {
    return array[row][column];
}

struct Position find2DArrayElement(char **array, int rows, int columns, char element) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (array[i][j] == element) {
                struct Position position;
                position.x = j;
                position.y = i;
                return position;
            }
        }
    }

    struct Position position;
    position.x = -1;
    position.y = -1;
    return position;
}

int countArrayElementEqualsTo(int *array, int size, int value) {
    int counter = 0;
    for (int i = 0; i<size; i++) {
        if (array[i] == value)
            counter++;
    }
    return counter;
}

int findIndexOf(int *array, int size, int value) {
    for(int i = 0; i < size; i++) {
        if (array[i] == value) return i;
    }

    return -1;
}

int arrayMinimumValue(int *array, int size) {
    int min = array[0];
    for(int i = 1; i < size; i++) {
        if (array[i] < min) min = array[i];
    }

    return min;
}