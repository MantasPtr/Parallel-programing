#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <sstream>
#include <omp.h>

double GetTime() {
   struct timeval laikas;
   gettimeofday(&laikas, NULL);
   double rez = (double)laikas.tv_sec+(double)laikas.tv_usec/1000000;
   return rez;
}

void genfile(int N, int p) {
   char filename[255];
   sprintf(filename, "src_%d.dat", p);
   FILE* f = fopen(filename, "w");
   for (int i=0; i<N; i++) {
      for (int j=0; j<p; j++) fprintf(f, "%.3f", (double)rand()/RAND_MAX);
      fprintf(f, "\n");
   }
   fclose(f);
}

void loadfile(int N, int p, float* M) {
   float a;
   char filename[255];
   sprintf(filename, "src_%d.dat", p);
   FILE *f = fopen(filename, "r");
   for (int i=0; i<N; i++) {
      fscanf(f, "%f %f", M+i*3, M+i*3+1);
      M[i*3+2] = 0;
      for (int j=2; j<p; j++) {
         fscanf(f, "%f", &a);
         M[i*3+2] += a; 
      }
      M[i*3+2] /= p-2;
   }
   fclose(f);
}

void performcalc(int N, int p, float* M, float* D) {

   #pragma omp parallel 
   {
      int threadCount = omp_get_num_threads();
      int threadId = omp_get_thread_num();
      int chunk = N/threadCount;
      float min, d;
      for (int i=threadId*chunk; i<(threadId+1)*chunk; i++) {
         min = 1e10;
         for (int j=0; j<N; j++) {
            if (j != i) {
               d = (M[2*i]-M[2*j]) + (M[2*i+1]-M[2*j+1]);
               if (d < min) {
                  min = d;
               }
            }
            D[i] = min;
         }
      }
   }
}

int main(int argc, char *argv[])
{
   int N = 24000;
   
   if (argc > 1) {
      // N value;
      int narg;
      std::istringstream ss(argv[1]);
      if (!(ss >> narg)) {
         printf("Invalid argument: Invalid number %s\n", argv[1]);
         return -1;
      }
      N = narg;
   }

   int threads = 2;
   if (argc > 2) {
      // thread count value;
      int threadarg;
      std::istringstream ss(argv[2]);
      if (!(ss >> threadarg)) {
         printf("Invalid argument: Invalid number %s\n", argv[2]);
         return -1;
      }
      threads = threadarg;
   }
   omp_set_num_threads(threads);
   srand(time(NULL));

   int p = 102;
   float* M = new float[3*N];
   float* D = new float[N];

//   genfile(N, p);


   double t_start = GetTime();
   
   loadfile(N, p, M);
   double t_load = GetTime();
   
   
   performcalc(N, p, M, D);
   double t_calc = GetTime();
   printf("Load time: %.2f\n", t_load - t_start);
   printf("Calc time: %.2f\n", t_calc - t_load);
   //for (int i=0; i<N; i++)
}
