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
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    int recipientSize = 1;
    int sendSize = 16;
    if (rank == 0) {
        for (int i = 0; i < bufferSize; i++) {
            buff[i] = i;
        }
    }
    while (recipientSize != procCount) {
        if (rank < recipientSize) {
            D(printf("%d sending to %d\n", rank, rank + recipientSize));
            MPI_Send(buff + sendSize, sendSize, MPI_INT, rank + recipientSize, 0, MPI_COMM_WORLD);
            D(printf(" %d send to %d (%d)\n", rank, rank + recipientSize, *(buff + sendSize)));
        }
        if (rank > recipientSize - 1 && rank <= recipientSize * 2 - 1) {
            D(printf(" %d receiving form  %d\n", rank, rank - recipientSize));
            MPI_Recv(buff, sendSize, MPI_INT, rank - recipientSize, 0, MPI_COMM_WORLD, &stat);
            D(printf("  %d received form  %d (%d)\n", rank, rank - recipientSize, buff[0]));
        }
        recipientSize *= 2;
        sendSize /= 2;
    }
    printf("rank: %d array: %3d", rank, buff[0]);
    for (int i = 1; i < sendSize * 2; i++) {
        printf(", %3d", buff[i]);
    }
    printf("\n");
    MPI_Finalize();
}