#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define debug
#ifdef debug
#define D(a) a
#else
#define D(a)
#endif
#define blockCount 4

double GetTime() {
    struct timeval laikas;
    gettimeofday(&laikas, NULL);
    return (double)laikas.tv_sec+(double)laikas.tv_usec/1000000;
 }

void genMatrix(int *A, int N, int M) {
    // Clean matrix
    for (int i = 0; i < N * M; i++) {
        A[i] = 0;
    }
    // Generate matrix
    int m = M / blockCount;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < m; j++) A[i * M + j] = (int)((double)rand() / RAND_MAX * 99) + 1;
        if (i > 0 && (i + 1) % (N / blockCount) == 0) m += M / blockCount;
    }
}

void calculateMedian(int M, int oneBlockSize, int procCount, int* workMatrix, double* median){
     int t,n;
     for (int rowNo = 0; rowNo < oneBlockSize; rowNo++) {
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

}

int main(int argc, char* argv[]) {
    double startTime = GetTime();
    int id, procCount; 
    int N = 256;
    int M = 10000;
    int *Matrix = new int[N * M];
    double *median;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);
    int *workMatrix = new int[N*M/procCount/blockCount];
    int oneBlockSize = N/procCount/blockCount;
    if (id == 0) {
        srand(time(NULL));
        genMatrix(Matrix, N, M);
        median = new double[N];
    } else {
        median = new double[N/blockCount];
    }
    for (int i=0;i<blockCount;i++) {
        MPI_Scatter(Matrix+N*M/blockCount*i     ,M*oneBlockSize, MPI_INT, workMatrix, M*oneBlockSize, MPI_INT, 0, MPI_COMM_WORLD);
        calculateMedian(M, oneBlockSize, procCount, workMatrix, median);
        MPI_Gather(median, oneBlockSize, MPI_DOUBLE, median+N/blockCount*i, oneBlockSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    double endTime = GetTime();
    if (id == 0) {
        printf("-------------------/n time: %.3f\n-------------------/n" , endTime - startTime);
    }
    /*if (id == 0) {  
        for (int j=0; j< N;j++) {
            for (int i = 0; i < M; i++) {
                printf("%3d ",Matrix[j*M+i]);            
            }
        printf("\n");   
        }   
    }
    if (id == 0) {
        printf("Hello from master\n");
        for (int i = 0; i < N; i++) {
            printf("%3.3f\n", median[i]);
        }
    }*/

}