int sqr(int x);

double **empty_matrix(int matrix_dimention);
void delete_matrix(double **matrix, int matrix_dimention);
double **generate_matrix(int matrix_dimention, int max_value);

enum matrix_prefil
{
    donut,
    corner
}; // TODO: use
