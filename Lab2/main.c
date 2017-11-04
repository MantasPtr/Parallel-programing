#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define sqr(x) (x*x)
#define randF (double)rand()/RAND_MAX

double GetTime() {
    struct timeval laikas;
    gettimeofday(&laikas, NULL);
    double rez = (double)laikas.tv_sec+(double)laikas.tv_usec/1000000;
    return rez;
 } 

int calculatePi (int outerLoop, int innerLoop) {
    int inCircle = 0;
    int total = 0;
    for (int fr1 = 0; fr1 < outerLoop; fr1++) {
        #pragma omp parallel for //reduction(+:total)
        for (int fr2 = 0; fr2 < innerLoop; fr2++) {
            double x = randF;
            double y = randF;
            if (sqr(x) + sqr(y) < 1) {
                inCircle++;
            }
            total++;
        }
        #pragma omp parallel master 
        {
            printf("pi %f\n", ((double)inCircle / total) * 4);
        }
    }
}
 
int main(int argc, char *argv[]){
    srand(time(NULL));
    double startTime = GetTime();
    calculatePi(100, 10000000);
    double endTime = GetTime();
    printf("%.3f\n", endTime - startTime);
}
