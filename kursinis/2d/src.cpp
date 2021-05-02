#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "utils.h"
#include "display_utils.h"

#define MATRIX_DIMENTION 100
#define MAX_MATRIX_VALUE 1.0
#define MAX_ITERATION_COUNT 10000
#define INTERATION_DRAW_INTERVAL 50
#define USE_ABS_SCALE false

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
    save_to_file(matrix, MATRIX_DIMENTION, MAX_MATRIX_VALUE, 0, USE_ABS_SCALE);
    for (int i = 1; i < MAX_ITERATION_COUNT; i++)
    {
        matrix = termodynamics(matrix);
        if (i % INTERATION_DRAW_INTERVAL == 0)
        {
            save_to_file(matrix, MATRIX_DIMENTION, MAX_MATRIX_VALUE, i, USE_ABS_SCALE);
        }
    }
}
