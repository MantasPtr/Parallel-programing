#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, value = 0;
    printf("---");
    MPI_Status stat;
    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        value = 12;
        printf("1. rank: %d, value: %d", rank, value);
        MPI_Send(&value, 1, MPI_INT, rank, 0, MPI_COMM_WORLD);
    } else {
        printf("2. rank: %d, value: %d", rank, value);
        MPI_Recv(&value, 1, MPI_INT, rank, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
    }
    printf("3. rank: %d value: %d", rank, value);
    MPI_Finalize();
}