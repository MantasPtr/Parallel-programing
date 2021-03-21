#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <cstring>
#include <algorithm>

#define debug
// #ifdef debug
// #define D(a) a
// #else
// #define D(a)
// #endif
#define MATRIX_DIMENTION 200
#define MAX_MATRIX_VALUE 1.0
#define MAX_ITERATION_COUNT 10000
#define INTERATION_DRAW_INTERVAL 50
#define USE_ABS_SCALE true

int sqr(int x)
{
    return x * x;
}

double **empty_matrix()
{
    // Innitiate
    double **matrix = new double *[MATRIX_DIMENTION];
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        matrix[i] = new double[MATRIX_DIMENTION];
    }
    // Clean matrix
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        for (int j = 0; j < MATRIX_DIMENTION; j++)
            matrix[i][j] = 0.0;
    }
    return matrix;
}

void delete_matrix(double **matrix)
{
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        delete matrix[i];
    }
    delete matrix;
}

double **gen_matrix()
{
    double **matrix = empty_matrix();

    // // fill donut

    // int center_x = (int)(MATRIX_DIMENTION / 2);
    // int center_y = (int)(MATRIX_DIMENTION / 2);
    // int radius1 = (int)((center_x + MATRIX_DIMENTION) / 5);
    // int radius2 = (int)((center_x + MATRIX_DIMENTION) / 6);
    // printf("center x,y, radius %d %d %d \n", center_x, center_y, radius1);

    // for (int i = 0; i < MATRIX_DIMENTION; i++)
    // {
    //     for (int j = 0; j < MATRIX_DIMENTION; j++)
    //     {
    //         bool is_inside_outer = sqr(i - center_x) + sqr(j - center_y) <= sqr(radius1);
    //         bool is_inside_inner = sqr(i - center_x) + sqr(j - center_y) <= sqr(radius2);
    //         matrix[i][j] = is_inside_outer && !is_inside_inner ? MAX_MATRIX_VALUE : 0.0;
    //     }
    // }

    // // fill corner

    // int center = (int)(MATRIX_DIMENTION / 2);
    // for (int i = 0; i < center; i++)
    // {
    //     for (int j = center; j < MATRIX_DIMENTION; j++)
    //     {
    //         matrix[i][j] = MAX_MATRIX_VALUE;
    //     }
    // }

    // fill corner L shape

    int center = (int)(MATRIX_DIMENTION / 2);
    // for (int i = 0; i < center; i++)
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        if (i % 4 >= 2)
            matrix[i][MATRIX_DIMENTION - 1] = MAX_MATRIX_VALUE;
    }
    // for (int j = center; j < MATRIX_DIMENTION; j++)
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        if (i % 4 <= 1)
            matrix[0][i] = MAX_MATRIX_VALUE;
    }

    // other corner L shape

    // for (int i = center; i < MATRIX_DIMENTION; i++)
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        if (i % 4 <= 1)
            matrix[i][0] = MAX_MATRIX_VALUE;
    }
    // for (int j = 0; j < center; j++)
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        if (i % 4 >= 2)
            matrix[MATRIX_DIMENTION - 1][i] = MAX_MATRIX_VALUE;
    }

    return matrix;
}

void write_matrix_to_file(double **matrix, char const *filename_postfix)
{
    // burrowed from
    // https://stackoverflow.com/questions/22580812/writing-a-png-in-c/22580958#22580958
    FILE *imageFile;
    int x, y, height = MATRIX_DIMENTION, width = MATRIX_DIMENTION, MAX_PGM_SUPPORTED_VALUE = 255;
    // WTF c++, why string iterpolation is only in c++20?
    char filename[100];
    strcpy(filename, "images/image_");
    strcat(filename, filename_postfix);
    strcat(filename, ".pgm");
    imageFile = fopen(filename, "wb");
    if (imageFile == NULL)
    {
        perror("ERROR: Cannot open output file");
        exit(EXIT_FAILURE);
    }
    double max_value = MAX_MATRIX_VALUE;
    if (!USE_ABS_SCALE)
    {
        max_value = 0.00001; // does not support lower value
        int max_x = 0, max_y = 0;
        for (int i = 0; i < MATRIX_DIMENTION; i++)
        {
            for (int j = 0; j < MATRIX_DIMENTION; j++)
            {
                if (matrix[i][j] > max_value)
                {
                    max_value = matrix[i][j];
                    max_x = i;
                    max_y = j;
                }
            }
        }
        printf("MAX VALUE %.4f in %d %d\n", max_value, max_x, max_y);
    }
    max_value = std::max(max_value, 0.00001);

    fprintf(imageFile, "P5\n");                          // P5 filetype
    fprintf(imageFile, "%d %d\n", width, height);        // dimensions
    fprintf(imageFile, "%d\n", MAX_PGM_SUPPORTED_VALUE); // Max pixel

    for (x = 0; x < height; x++)
    {
        for (y = 0; y < width; y++)
        {
            double pixel = matrix[x][y];
            int pixel_value = (int)(pixel / max_value * MAX_PGM_SUPPORTED_VALUE);
            fputc(pixel_value, imageFile);
        }
    }

    fclose(imageFile);
}

void print_matrix(double **matrix)
{
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        for (int j = 0; j < MATRIX_DIMENTION; j++)
        {
            printf(" %.2f", matrix[i][j]);
        }
        printf("\n");
    }
}

double **termodynamics(double **matrix)
{
    double **next_matrix = empty_matrix();
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
    delete_matrix(matrix);
    return next_matrix;
}

int main()
{
    double **matrix = gen_matrix();
    // print_matrix(matrix);
    write_matrix_to_file(matrix, "0");
    for (int i = 0; i < MAX_ITERATION_COUNT; i++)
    {
        matrix = termodynamics(matrix);
        if (i % INTERATION_DRAW_INTERVAL == 0)
        {
            // printf("------------------------\n");
            // print_matrix(matrix);
            char index_str[5];
            snprintf(index_str, 6, "%05d", i);
            write_matrix_to_file(matrix, index_str);
        }
    }

    // printf("------------------------\n");
    // print_matrix(matrix);
}
