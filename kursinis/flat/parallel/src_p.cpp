#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <mpi.h>

#include "../common/utils_flat.h"
#include "../common/display_utils_flat.h"

#define MATRIX_DIMENTION 10
#define MAX_MATRIX_VALUE 1.0
#define MAX_ITERATION_COUNT 10
#define INTERATION_DRAW_INTERVAL 1
#define USE_ABS_SCALE true

double *termodynamics(double *matrix)
{
    double *next_matrix = empty_matrix(MATRIX_DIMENTION);
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        for (int j = 0; j < MATRIX_DIMENTION; j++)
        {
            // first or last column or row
            if (i == 0 || i == MATRIX_DIMENTION - 1 || j == 0 || j == MATRIX_DIMENTION - 1)
            {
                // assuming sides has constant value
                next_matrix[i * MATRIX_DIMENTION + j] = matrix[i * MATRIX_DIMENTION + j];
            }
            else
            {
                next_matrix[i * MATRIX_DIMENTION + j] = (matrix[(i - 1) * MATRIX_DIMENTION + j - 1] +
                                                         matrix[(i - 1) * MATRIX_DIMENTION + j + 1] +
                                                         matrix[(i + 1) * MATRIX_DIMENTION + j - 1] +
                                                         matrix[(i + 1) * MATRIX_DIMENTION + j + 1]) /
                                                        4;
            }
        }
    }
    delete_matrix(matrix);
    return next_matrix;
}

int main(int argc, char *argv[])
{
    double *matrix = generate_matrix(MATRIX_DIMENTION, MAX_MATRIX_VALUE);
    double *work_matrix = empty_matrix(MATRIX_DIMENTION);
    int id, proc_count;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_count);

    int blocksize = MATRIX_DIMENTION * MATRIX_DIMENTION / proc_count;

    save_to_file(matrix, MATRIX_DIMENTION, MAX_MATRIX_VALUE, 0, USE_ABS_SCALE);
    for (int i = 1; i < MAX_ITERATION_COUNT; i++)
    {
        // MPI_Scatter(matrix + N * M / blockCount * i, M * oneBlockSize, MPI_INT, workMatrix, M * oneBlockSize, MPI_INT, 0, MPI_COMM_WORLD);
        // MPI_Scatter(
        //     matrix,blocksize, MPI_INT, work_matrix, blocksize, MPI_INT, 0, MPI_COMM_WORLD
        // )
        matrix = termodynamics(matrix);
        // MPI_Gather(median, oneBlockSize, MPI_DOUBLE, median + N / blockCount * i, oneBlockSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        if (i % INTERATION_DRAW_INTERVAL == 0)
        {
            save_to_file(matrix, MATRIX_DIMENTION, MAX_MATRIX_VALUE, i, USE_ABS_SCALE);
        }
    }
    MPI_Finalize();
}
