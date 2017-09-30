#include <omp.h>
#include <stdio.h>
int main() {
	int theadCount = 0;
	#pragma omp parallel
	{
		threadCount = omp_get_num_threads();
	}
	printf("thead count = %d\n", theadCount);
}

