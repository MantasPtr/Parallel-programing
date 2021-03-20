#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define debug
// #ifdef debug
// #define D(a) a
// #else
// #define D(a)
// #endif
#define MATRIX_DIMENTION 1000
#define MAX_MATRIX_VALUE 255
#define MAX_ITERATION_COUNT 500
#define USE_ABS_SCALE false

int sqr(int x)
{
    return x * x;
}

int **empty_matrix()
{
    // Innitiate
    int **matrix = new int *[MATRIX_DIMENTION];
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        matrix[i] = new int[MATRIX_DIMENTION];
    }
    // Clean matrix
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        for (int j = 0; j < MATRIX_DIMENTION; j++)
            matrix[i][j] = 0;
    }
    return matrix;
}

void delete_matrix(int **matrix)
{
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        delete matrix[i];
    }
    delete matrix;
}

int **gen_matrix()
{
    int **matrix = empty_matrix();
    // fill donut
    int center_x = (int)(MATRIX_DIMENTION / 2);
    int center_y = (int)(MATRIX_DIMENTION / 2);
    int radius1 = (int)((center_x + MATRIX_DIMENTION) / 5);
    int radius2 = (int)((center_x + MATRIX_DIMENTION) / 6);
    printf("center x,y, radius %d %d %d \n", center_x, center_y, radius1);

    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        for (int j = 0; j < MATRIX_DIMENTION; j++)
        {
            bool is_inside_outer = sqr(i - center_x) + sqr(j - center_y) <= sqr(radius1);
            bool is_inside_inner = sqr(i - center_x) + sqr(j - center_y) <= sqr(radius2);
            matrix[i][j] = is_inside_outer && !is_inside_inner ? MAX_MATRIX_VALUE : 0;
        }
    }

    return matrix;
}

void write_matrix_to_file(int **matrix)
{
    // burrowed from
    // https://stackoverflow.com/questions/22580812/writing-a-png-in-c/22580958#22580958
    FILE *imageFile;
    int x, y, pixel, height = MATRIX_DIMENTION, width = MATRIX_DIMENTION;

    imageFile = fopen("image.pgm", "wb");
    if (imageFile == NULL)
    {
        perror("ERROR: Cannot open output file");
        exit(EXIT_FAILURE);
    }
    int max_value = MAX_MATRIX_VALUE;
    if (!USE_ABS_SCALE)
    {
        max_value = 1; // does not support lower value
        for (int i = 0; i < MATRIX_DIMENTION; i++)
        {
            for (int j = 0; j < MATRIX_DIMENTION; j++)
            {
                if (matrix[i][j] > max_value)
                {
                    max_value = matrix[i][j];
                }
            }
        }
    }
    printf("MAX VALUE %d\n", max_value);
    fprintf(imageFile, "P5\n");                   // P5 filetype
    fprintf(imageFile, "%d %d\n", width, height); // dimensions
    fprintf(imageFile, "%d\n", max_value);        // Max pixel

    /* Now write a greyscale ramp */
    for (x = 0; x < height; x++)
    {
        for (y = 0; y < width; y++)
        {
            pixel = matrix[x][y];
            fputc(pixel, imageFile);
        }
    }

    fclose(imageFile);
}

void print_matrix(int **matrix)
{
    for (int i = 0; i < MATRIX_DIMENTION; i++)
    {
        for (int j = 0; j < MATRIX_DIMENTION; j++)
        {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}

int **termodynamics(int **matrix)
{
    int **next_matrix = empty_matrix();
    for (int i = 1; i < MATRIX_DIMENTION - 1; i++)
    {
        for (int j = 1; j < MATRIX_DIMENTION - 1; j++)
        {
            next_matrix[i][j] = (int)(matrix[i - 1][j - 1] + matrix[i - 1][j + 1] + matrix[i + 1][j - 1] + matrix[i + 1][j + 1]) / 4;
        }
    }
    delete_matrix(matrix);
    return next_matrix;
}

int main()
{
    int **matrix = gen_matrix();
    // print_matrix(matrix);
    for (int i = 0; i < MAX_ITERATION_COUNT; i++)
        matrix = termodynamics(matrix);
    write_matrix_to_file(matrix);
}
