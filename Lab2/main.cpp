#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>

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
    double totalGentime = 0;
    //unsigned int seed = (unsigned int) 1;      
    #pragma omp parallel 
    {
        //printf("%d\n", omp_get_thread_num());
        //srand(int(time(NULL)) ^ omp_get_thread_num());
        //unsigned int seed[omp_get_num_threads()];
        //for (int fr= 0; fr<omp_get_num_threads(); fr++) {
        //    seed[fr] = (unsigned int) fr; 
        //}
        unsigned int seed = (unsigned int) omp_get_thread_num();
        for (int fr1 = 0; fr1 < outerLoop; fr1++) {
            #pragma omp for reduction (+:inCircle, total, totalGentime)
            for (int fr2 = 0; fr2 < innerLoop; fr2++) {
                printf("%d %d \n",omp_get_thread_num() ,seed);
                double gen1s = GetTime();
                //double x = getRandomDoubleWithoutSeed();
                //double x = getRandomDouble(&seed[omp_get_thread_num()]);
                double x = getRandomDouble(&seed);
                //double y = getRandomDoubleWithoutSeed();
                //double y = getRandomDouble(&seed[omp_get_thread_num()]);
                double y = getRandomDouble(&seed);
                //printf("%.6f %.6f\n",x,y);
                
                double gen1f = GetTime();
                totalGentime=gen1f-gen1s;
                //printf("r1: %.9f r2: %.9f\n",gen1f-gen1s, gen2f-gen1f);
                if (pow(x,2) + pow(y,2) < 1) {
                        inCircle++;
                }
                total++;
            }
            #pragma omp master
            {
                printf("total: %d, inCircle: %d , totalGenTime: %.6f ", total, inCircle, totalGentime);
                printf("pi %f\n", ((double)inCircle / total) * 4);
            }
        }
    }
}
int main(int argc, char *argv[]){
    //omp_set_num_threads(1);
    srand(time(NULL));
    double startTime = GetTime();
    calculatePi(1, 12);
    double endTime = GetTime();
    printf("%.3f\n", endTime - startTime);
}
