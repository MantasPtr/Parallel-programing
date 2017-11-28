#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#ifdef debug
#define D(a) a
#else
#define D(a)
#endif

void genMatrix(int *A, int N, int M) {
    // Clean matrix
    for (int i = 0; i < N * M; i++) {
        A[i] = 0;
    }
    // Generate matrix
    int m = M / 4;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < m; j++) A[i * M + j] = (int)((double)rand() / RAND_MAX * 99) + 1;
        if (i > 0 && (i + 1) % (N / 4) == 0) m += M / 4;
    }
}

int main(int argc, char* argv[]) {
    int id, procCount; 
    int N = 16;
    int M = 20;
    int *A = new int[N * M];
    int t, n;
    double *median = new double[N];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    int *workMatrix = new int[N*M/procCount];
    if (id == 0) {
        srand(time(NULL));
        genMatrix(A, N, M);
    }
    MPI_Scatter(A           ,N*M/4/procCount, MPI_INT, workMatrix                  , N*M/4/procCount, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(A+N*M/4     ,N*M/4/procCount, MPI_INT, workMatrix+N*M/4/procCount  , N*M/4/procCount, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(A+N*M/4*2   ,N*M/4/procCount, MPI_INT, workMatrix+N*M/4/procCount*2, N*M/4/procCount, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(A+N*M/4*3   ,N*M/4/procCount, MPI_INT, workMatrix+N*M/4/procCount*3, N*M/4/procCount, MPI_INT, 0, MPI_COMM_WORLD);
    

    for (int rowNo = 0; rowNo < N/procCount; rowNo++) {
        n = 0;
        while (workMatrix[rowNo * M + n] != 0 && n < M) {
            n++;
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1; j++) {
                if (workMatrix[rowNo * M + j] > workMatrix[rowNo * M + j + 1]) {
                    t = workMatrix[rowNo * M + j];
                    workMatrix[rowNo * M + j] = workMatrix[rowNo * M + j + 1];
                    workMatrix[rowNo * M + j + 1] = t;
                }
            }
        }
        if (n % 2 == 1) {
            median[rowNo] = (double)workMatrix[rowNo * M + (n / 2)];
        } else {
            median[rowNo] = (double(workMatrix[rowNo * M + (n / 2)] + workMatrix[rowNo * M + (n / 2) - 1]) / 2);
        }
    }



// Print matrix
for (int j=0; j< procCount;j++) {
    if (id == j) {
        printf("id= %d\n",id);
        for (int i = 0; i < N/procCount; i++) {
            printf("median = %3.3f", median[i]);
            for (int j = 0; j < M; j++) {
                printf("%3d", workMatrix[i * M + j]);
            }
            printf("\n");
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
}
    MPI_Finalize();

}