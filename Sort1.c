
#include "sort0.h"

#define NUM_THREADS	2

int N, *InputArray, *OutputArray;

int main()
{
	FILE *fp;
	int i, *iap, *oap, v;
	double start_time=0, end_time=0;
	char s;
	char in_file[256] = "SortData100000_0.txt";
	char out_file[256] = "Sorted100000_0.txt";
	char comp_file[256] = "Result100000_0.txt";

	printf("Odd-Even Sort Start\n");
	omp_set_num_threads(NUM_THREADS);
	printf("# of processors: %d\n", omp_get_num_procs());
	printf("max # of threads: %d\n", omp_get_max_threads());

	readfile(in_file);
	for(i=0, iap=InputArray, oap=OutputArray; i<N; i++, iap++, oap++) 
		*oap = *iap;
	start_time += omp_get_wtime();

	sortprog(OutputArray, 0, N-1); 

	end_time += omp_get_wtime();

	writefile(out_file);

	/* Verify */
	printf("Verify Start!\n");
	fp = fopen(comp_file, "r");
	fscanf(fp, "%d", &N);
	for (i = 0, oap = OutputArray; i < N; i++, oap++) {
		fscanf(fp, "%ld", &v);
		if (*oap != v) {
			printf("WRONG at %d-th line (value %ld should be %ld)\n", i, *oap, v);
			break;
		}
	}
	fclose(fp);
	if (i == N) printf("Verify OK!\n");

	printf("processing time (sec) = %g\n", 
		(float)(end_time-start_time));
	scanf("%c", &s);
	return 0;
}