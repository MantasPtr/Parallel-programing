#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

#define DEBUG

void genMatrix(int *A, int N, int M) {
   // Clean matrix
   for (int i=0; i<N*M; i++) {
      A[i] = 0;
   }
   // Generate matrix
   int m = M/4;
   for (int i=0; i<N; i++) {
      for (int j=0; j<m; j++)
        A[i*M+j] = (int)((double)rand()/RAND_MAX*99) + 1;
      if (i > 0 && (i+1) % (N/4) == 0)
        m += M/4;
   }
}


int main() {
  srand(time(NULL));
  int N = 16; // eilučių skaičius
  int M = 20; // stulpelių skaičius
  int *A = new int[N*M];
  float *median = new float[N];

  int t, n;
  genMatrix(A, N, M);

  int threadCount = 4;
  omp_set_num_threads(threadCount);


  #pragma omp parallel
  {
  int threadId = omp_get_thread_num();
  for (int rowNo = threadId; rowNo<N; rowNo+=threadCount) {
      n = 0;
      while (A[rowNo*M+n] != 0 && n < M) {
        n++;
      }
      for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-1; j++) {
          if (A[rowNo*M+j] > A[rowNo*M+j+1]) {
            t = A[rowNo*M+j];
            A[rowNo*M+j] = A[rowNo*M+j+1];
            A[rowNo*M+j+1] = t;
          }
        }
      }
      float currentMedian;
      if(n%2==1){
          currentMedian = (float) A[rowNo*M+(n/2)];
      } else {
          currentMedian = ((float)(A[rowNo*M+(n/2)]+A[rowNo*M+(n/2)])/2);
      }
      median[rowNo]=(A[rowNo*M+(n/2)]);
    }
  }
#ifdef DEBUG
// Print matrix
   for (int i=0; i<N; i++) {
       printf("median = %6.3f |", median[i]);
       for (int j=0; j<M; j++) {
          printf("%3d", A[i*M+j]);
       }
       printf("\n");
    }
#endif

    float medianAverage;
    for (int i=0; i<N; i++) {
      medianAverage+=median[i];
    }
    medianAverage = medianAverage/N;

    printf("median average = %6.3f\n",medianAverage  );

}
