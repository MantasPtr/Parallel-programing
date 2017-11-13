#include <mpi.h>
#include <stdio.h>

//#define debug=true;

int main(int argc, char* argv[]) {
    int rank, procCount;
    int buff[32];
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    int recipientSize = 1;
    int sendSize = 16;
    if (rank == 0) {
        for (int i = 0; i < 32; i++) {
            buff[i] = i;
        }
    }
    while (recipientSize != procCount) {
        //printf("     rank: %d array %d, %d, %d, %d\n", rank, buff[0], buff[1], buff[2], buff[3]);
        if (rank < recipientSize) {
            #ifdef debug
            printf("%d sending to %d\n", rank, rank + recipientSize);
            #endif
            MPI_Send(buff+sendSize, sendSize, MPI_INT, rank + recipientSize, 0, MPI_COMM_WORLD);
            #ifdef debug
            printf(" %d send to %d(%d)\n", rank, rank + recipientSize, *(buff+sendSize));
            #endif
        }
        if (rank > recipientSize - 1 && rank <= recipientSize * 2 - 1) {
            #ifdef debug
            printf(" %d receiving form  %d\n", rank, rank - recipientSize);
            #endif
            MPI_Recv(buff, sendSize, MPI_INT, rank - recipientSize, 0, MPI_COMM_WORLD, &stat);
            #ifdef debug
            printf("  %d received form  %d (%d)\n", rank, rank - recipientSize, buff[0]);
            #endif
        }
        recipientSize *= 2;
        sendSize /= 2;
    }
    printf("rank: %d array %d, %d, %d, %d\n", rank, buff[0], buff[1], buff[2], buff[3]);
    MPI_Finalize();
}