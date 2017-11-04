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
    int fr1;
    for (fr1 = 0; fr1 < outerLoop; fr1++) {
	int fr2;
        #pragma omp parallel for // reduction (+:inCircle, total)
        for (fr2 = 0; fr2 < innerLoop; fr2++) {
	    if(fr2 == 1000) {
		printf("asd %d", omp_get_thread_num());
	    }
            double x = randF;
            double y = randF;
            if (sqr(x) + sqr(y) < 1) {
                inCircle++;
            }
            total++;
        }
//        #pragma omp master
//        {

//	    printf("total: %d, inCircle: %d ", total, inCircle);
  //          printf("pi %f\n", ((double)inCircle / total) * 4);
  //      }
    }
}
 
int main(int argc, char *argv[]){
    srand(time(NULL));
    double startTime = GetTime();
    calculatePi(100, 10000000);
    double endTime = GetTime();
    printf("%.3f\n", endTime - startTime);
}
