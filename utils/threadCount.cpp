#include <omp.h>
#include <stdio.h>
int main() {
	int threadCount = 0;
	#pragma omp parallel
	{
		threadCount = omp_get_num_threads();
	}
	printf("thread count = %d\n", threadCount);
}

