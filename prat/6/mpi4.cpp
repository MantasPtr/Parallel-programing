#include <mpi.h>
#include <stdio.h>

//#define debug

#ifdef debug
#define D(a) a
#else
#define D(a)
#endif
#define bufferSize 32

int main(int argc, char* argv[]) {
    int rank, procCount;
    int buff[bufferSize];
    double value;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    if (rank == 0) {
        for (int i = 0; i < bufferSize; i++) {
            value = 2.718;
        }
    }
    for (int i = 0; i < procCount; i++) {
        if (rank == i) {
            printf("rank: %d, value: %f\n", rank, value);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&value, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    for (int i = 0; i < procCount; i++) {
        if (rank == i) {
            printf("rank: %d, value: %f\n", rank, value);
        }
    }
     MPI_Finalize();
}