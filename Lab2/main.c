#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define sqr(x) (x*x)
#define randF (double)rand()/RAND_MAX

int main(int argc, char *argv[]){
    srand(time(NULL));
    int total = 0;
    int inCircle = 0;
    int less = 0;
    for (int fr1 = 0; fr1 < 100; fr1++) {
        for (int fr2 = 0; fr2 < 1000000; fr2++) {
            double d1 = randF;
            double d2 = randF;
            if (sqr(d1) + sqr(d2) < 1) {
                inCircle++;
            }
            total++;
        }
        printf("pi %f\n", (double)inCircle / total * 4);
    }
}
