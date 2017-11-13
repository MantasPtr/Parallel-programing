#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int id, numProcs, buff;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    if (id == 0) {
        for (int i = 1; i < numProcs; i++) {
            // I variantas
            // MPI_Recv(&buff, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
            // printf("Message received from process %d\n", i);

            // II variantas
            MPI_Recv(&buff, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,
                &stat);
            printf("Message received from process %d\n", stat.MPI_SOURCE);
        }
    } else {
        MPI_Send(&buff, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
