#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

void genMatrix(int *A, int N, int M) {
   // Clean matrix
   for (int i=0; i<N*M; i++) {
      A[i] = 0;
   }
   // Generate matrix
   int m = M/4;
   for (int i=0; i<N; i++) {
      for (int j=0; j<m; j++) A[i*M+j] = (int)((double)rand()/RAND_MAX*99) + 1;
      if (i > 0 && (i+1) % (N/4) == 0) m += M/4;
   }  
}


int main() {
  srand(time(NULL));
  int N = 16;
  int M = 20;
  int *A = new int[N*M];
  int *mediana = new int[N];

  int t, n; 
  genMatrix(A, N, M);
 
  int threadCount = 4;
  omp_set_num_threads(threadCount);


  #pragma omp parallel
  {
  int threadId = omp_get_thread_num();

  for (int k = threadId; k<N; k+=threadCount) {
      n = 0;
      printf("k = %d \n", k);   
      while (A[k*M+n] != 0 && n < M) 
        n++;
      for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-1; j++) {
          if (A[k*M+j] > A[k*M+j+1]) {
            t = A[k*M+j];
            A[k*M+j] = A[k*M+j+1];
            A[k*M+j+1] = A[k*M+j];
          }
        }
      }
      mediana[k]=(A[k+(n/2)]);
    }
  }
   // Print matrix
   for (int i=0; i<N; i++) {
       printf("mediana = %3d |", mediana[i]);   
       for (int j=0; j<M; j++) {
          printf("%3d", A[i*M+j]);
       }
       printf("\n");
    }
}
