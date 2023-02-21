//
// Created by Julien on 15/02/2023.
//

#include "file_functions.h"

FILE* initFile(const char *filename, char mode)
{
    FILE *file = fopen(filename, &mode);

    if (file == NULL)
        ConsoleHandlerDisplayError("opening the file: '%s'.", filename);

    return file;
}

bool fill2DArrayFromFile(FILE *file, char **array, int row, int col, int amountCharToSkip)
{
    char line[col+amountCharToSkip];
    for(int i = 0; i < row; i++)
    {
        if (fgets(line, col+amountCharToSkip, file) == NULL) {
            ConsoleHandlerDisplayError(" reading the file.");
            return false;
        }

        for(int j = 0; j < col; j++)
        {
            array[i][j] = line[j];
        }
    }
    return true;
}


void closeFile(FILE *file)
{
    fclose(file);
}
