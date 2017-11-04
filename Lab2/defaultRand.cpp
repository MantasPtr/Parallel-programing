#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>
#include <sstream>

#define sqr(x) (x*x)
#define randF (double)rand()/RAND_MAX

double getRandomDouble(unsigned int *seed) {
    return (double)rand_r(seed)/RAND_MAX;
}

double getRandomDoubleWithoutSeed() {
    return (double)rand()/RAND_MAX;
}

double GetTime() {
    struct timeval laikas;
    gettimeofday(&laikas, NULL);
    double rez = (double)laikas.tv_sec+(double)laikas.tv_usec/1000000;
    return rez;
 }

int calculatePi (int outerLoop, int innerLoop) {
    int inCircle = 0;
    int total = 0;
    #pragma omp parallel 
    {
        unsigned int seed = (unsigned int) omp_get_thread_num();
        for (int fr1 = 0; fr1 < outerLoop; fr1++) {
            #pragma omp for reduction (+:inCircle, total)
            for (int fr2 = 0; fr2 < innerLoop; fr2++) {
                double x = getRandomDoubleWithoutSeed();
                double y = getRandomDoubleWithoutSeed();         
                if (pow(x,2) + pow(y,2) < 1) {
                        inCircle++;
                }
                total++;
            }
            #pragma omp master
            {
                printf("pi %f\n", ((double)inCircle / total) * 4);
            }
        }
    }
}
int main(int argc, char *argv[]){
    if (argc > 1) {
       // thread count value;
       int threadarg;
       std::istringstream ss(argv[1]);
       if (!(ss >> threadarg)) {
          printf("Invalid argument: Invalid number %s\n", argv[1]);
          return -1;
       }
       omp_set_num_threads(threadarg);       
    }
    srand(time(NULL));
    double startTime = GetTime();
    calculatePi(10, 20000000);
    double endTime = GetTime();
    printf("time: %.3f\n", endTime - startTime);
}
