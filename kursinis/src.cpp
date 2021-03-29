#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <cstring>

#include "utils.h"
#include "display_utils.h"

#define MATRIX_DIMENTION 200
#define MAX_MATRIX_VALUE 1.0
#define MAX_ITERATION_COUNT 10000
#define INTERATION_DRAW_INTERVAL 50
#define USE_ABS_SCALE true

char *generate_filename(char const *filename_postfix)
{
    char *filename = (char *)malloc(100 * sizeof(char));
    strcpy(filename, "images/image_");
    strcat(filename, filename_postfix);
    strcat(filename, ".pgm");
    return filename;
}

double **termodynamics(double **matrix)
{
    double **next_matrix = empty_matrix(MATRIX_DIMENTION);
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        for (int j = 0; j < MATRIX_DIMENTION; j++)
        {
            if (i == 0 || i == MATRIX_DIMENTION - 1 || j == 0 || j == MATRIX_DIMENTION - 1)
            {
                // assuming sides has constant value
                next_matrix[i][j] = matrix[i][j];
            }
            else
            {
                next_matrix[i][j] = (matrix[i - 1][j - 1] + matrix[i - 1][j + 1] + matrix[i + 1][j - 1] + matrix[i + 1][j + 1]) / 4;
            }
        }
    }
    delete_matrix(matrix, MATRIX_DIMENTION);
    return next_matrix;
}

int main()
{
    double **matrix = generate_matrix(MATRIX_DIMENTION, MAX_MATRIX_VALUE);
    // print_matrix(matrix);
    char *filename = generate_filename("00000");
    write_matrix_to_file(matrix, MATRIX_DIMENTION, MAX_MATRIX_VALUE, filename, USE_ABS_SCALE);
    free(filename);
    for (int i = 1; i < MAX_ITERATION_COUNT; i++)
    {
        matrix = termodynamics(matrix);
        if (i % INTERATION_DRAW_INTERVAL == 0)
        {
            char index_str[5];
            snprintf(index_str, 6, "%05d", i);
            char *filename = generate_filename(index_str);
            write_matrix_to_file(matrix, MATRIX_DIMENTION, MAX_MATRIX_VALUE, generate_filename(index_str), USE_ABS_SCALE);
            free(filename);
        }
    }
}
