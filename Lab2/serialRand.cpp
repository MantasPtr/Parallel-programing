#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

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
    for (int fr1 = 0; fr1 < outerLoop; fr1++) {
        for (int fr2 = 0; fr2 < innerLoop; fr2++) {
            double x = getRandomDoubleWithoutSeed();
            double y = getRandomDoubleWithoutSeed();         
                if (pow(x,2) + pow(y,2) < 1) {
                        inCircle++;
                }
                total++;
            }
        printf("pi %f\n", ((double)inCircle / total) * 4);
    }
}
int main(int argc, char *argv[]){
    srand(time(NULL));
    double startTime = GetTime();
    calculatePi(10, 20000000);
    double endTime = GetTime();
    printf("time: %.3f\n", endTime - startTime);
}
