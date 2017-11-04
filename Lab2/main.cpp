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
    #pragma omp parallel
    for (int fr1 = 0; fr1 < outerLoop; fr1++) {
        #pragma omp for reduction (+:inCircle, total)
        for (int fr2 = 0; fr2 < innerLoop; fr2++) {
            /*if (fr2 == 0) {
                printf("debug %d, %d\n", fr2 , omp_get_thread_num());
            }*/

            //unsigned int timeint =  (unsigned int )time(NULL);
            //printf("%d ", timeint);
            unsigned int a;
            #pragma omp single 
            {
            a = (unsigned int)(omp_get_thread_num());
            }
            printf("1- %d ", a);
            //double x = getRandomDoubleWithoutSeed();
            double x = getRandomDouble(&a);
            printf("2- %d ", a);
            //double y = getRandomDoubleWithoutSeed();
            double y = getRandomDouble(&a);
            printf("3- %d ", a);
            printf("%f %f %d \n", x,y,omp_get_thread_num());
            if (pow(x,2) + pow(y,2) < 1) {
                inCircle++;
            }
            total++;
        }
       #pragma omp master
        {
            printf("total: %d, inCircle: %d ", total, inCircle);
          printf("pi %f\n", ((double)inCircle / total) * 4);
        }
    }
}
 
int main(int argc, char *argv[]){
    //omp_set_num_threads(2);
    srand(time(NULL));
    double startTime = GetTime();
    calculatePi(100, 1000000);
    double endTime = GetTime();
    printf("%.3f\n", endTime - startTime);
}
