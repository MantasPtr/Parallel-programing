#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, procCount;
    double value = 0;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    printf("rank:%d procCount:%d value:%f\n", rank, procCount, value);
    if (rank == 0)
    {
        value = 12;
        printf("sending\n");
        MPI_Send(&value, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    }
    else
    {
        printf("receiving\n");
        MPI_Recv(&value, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
    }
    printf("rank:%d value:%f\n", rank, value);
    MPI_Finalize();
}