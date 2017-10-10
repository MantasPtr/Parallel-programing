#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

//#define DEBUG

double GetTime() {
   struct timeval laikas;
   gettimeofday(&laikas, NULL);
   double rez = (double)laikas.tv_sec+(double)laikas.tv_usec/1000000;
   return rez;
}

void genMatrix(int *A, int N, int M) {
   // Clean matrix
   for (int i=0; i<N*M; i++) {
      A[i] = 0;
   }
   // Generate matrix
   int m = M/4;
   for (int i=0; i<N; i++) {
      for (int j=0; j<m; j++) {
        A[i*M+j] = (int)((double)rand()/RAND_MAX*99) + 1;
      }
      if (i > 0 && (i+1) % (N/4) == 0)
        m += M/4;
   }
}


int main() {
  srand(time(NULL));
  int N = 256; // eilučių skaičius
  int M = 2000; // stulpelių skaičius
  int *A = new int[N*M];
  float *median = new float[N];

  int t, n;
  genMatrix(A, N, M);

  int threadCount = 2;
  omp_set_num_threads(threadCount);

  double t_start = GetTime();
  //#pragma omp parallel for schedule(static) private(n, t) //2.86
  //#pragma omp parallel for schedule(static, N/(4*threadCount)) private(n, t) //1.56
  //#pragma omp parallel for schedule(dynamic) private(n, t) //1.72
  //#pragma omp parallel for schedule(guided) private(n, t) //1.68
  //#pragma omp parallel for schedule(guided, N/(4*threadCount) private(n, t) //1.69
  #pragma omp parallel for schedule(auto) private(n, t) //2.88

  for (int rowNo = 0; rowNo<N; rowNo++) {
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
          currentMedian = ((float)(A[rowNo*M+(n/2)]+A[rowNo*M+(n/2)-1])/2);
      }
      median[rowNo]=currentMedian;
    }
    double t_end = GetTime();
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
    printf("calculation time: %.2f\n", t_end - t_start);
    float medianAverage = 0;
    for (int i=0; i<N; i++) {
      medianAverage+=median[i];
    }
    medianAverage = medianAverage/N;

    printf("median average = %6.3f\n", medianAverage);

}
