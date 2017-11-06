#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

double getRandomDouble(unsigned int *seed) {
    return (double)rand_r(seed)/RAND_MAX;
}

double GetTime() {
    struct timeval laikas;
    gettimeofday(&laikas, NULL);
    double rez = (double)laikas.tv_sec+(double)laikas.tv_usec/1000000;
    return rez;
 }

int calculatePi (int outerLoop, int innerLoop, int seedRandom) {
    int inCircle = 0;
    int total = 0;
    for (int fr1 = 0; fr1 < outerLoop; fr1++) {
        for (int fr2 = 0; fr2 < innerLoop; fr2++) {
            double x = getRandomDouble(&seedRandom);
            double y = getRandomDouble(&seedRandom);         
                if (pow(x,2) + pow(y,2) < 1) {
                        inCircle++;
                }
                total++;
            }
        printf("pi %f\n", ((double)inCircle / total) * 4);
    }
}
int main(int argc, char *argv[]){
    struct timeval laikas;
    gettimeofday(&laikas, NULL); 
    double startTime = GetTime();
    calculatePi(10, 20000000, (int) laikas.tv_usec);
    double endTime = GetTime();
    printf("time: %.3f\n", endTime - startTime);
}
