#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "../common/utils_flat.h"
#include "../common/display_utils_flat.h"

#define MATRIX_DIMENTION 10
#define MAX_MATRIX_VALUE 1.0
#define MAX_ITERATION_COUNT 300
#define DRAW_FREQUENCY 10
#define USE_ABS_SCALE false

double *termodynamics(double *matrix)
{
    double *next_matrix = empty_matrix(MATRIX_DIMENTION);
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        for (int j = 0; j < MATRIX_DIMENTION; j++)
        {
            if (i == 0 || i == MATRIX_DIMENTION - 1 || j == 0 || j == MATRIX_DIMENTION - 1)
            {
                // assuming sides has constant value
                next_matrix[i * MATRIX_DIMENTION + j] = matrix[i * MATRIX_DIMENTION + j];
            }
            else
            {
                next_matrix[i * MATRIX_DIMENTION + j] =
                    (matrix[(i - 1) * MATRIX_DIMENTION + j] +
                     matrix[(i + 1) * MATRIX_DIMENTION + j] +
                     matrix[i * MATRIX_DIMENTION + j - 1] +
                     matrix[i * MATRIX_DIMENTION + j + 1]) /
                    4;
            }
        }
    }
    delete_matrix(matrix);
    return next_matrix;
}

int main()
{
    double *matrix = generate_matrix(MATRIX_DIMENTION, MAX_MATRIX_VALUE);
    save_to_file(matrix, MATRIX_DIMENTION, MAX_MATRIX_VALUE, 0, USE_ABS_SCALE);
    for (int i = 1; i < MAX_ITERATION_COUNT; i++)
    {
        matrix = termodynamics(matrix);
        if (i % DRAW_FREQUENCY == 0)
        {
            save_to_file(matrix, MATRIX_DIMENTION, MAX_MATRIX_VALUE, i, USE_ABS_SCALE);
        }
    }
}
