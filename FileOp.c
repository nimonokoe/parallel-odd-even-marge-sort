
#include "sort0.h"

void readfile(char *in_file) {
	FILE *fp;
	int *iap;

	if(*in_file == '\0') return;
	fp = fopen(in_file, "r");
	fscanf(fp, "%d", &N);
	InputArray = iap= (int *)malloc(sizeof(int)*N);
	OutputArray = (int *)malloc(sizeof(int)*N);
	for(int i=0; i<N; i++) {
		fscanf(fp, "%d", iap++);
	}
	fclose(fp);
}

void writefile(char *out_file) {
	FILE *fp;
	int *oap = OutputArray;

	if(strcmp(out_file, "NULL") == 0) return;
	fp = fopen(out_file, "w");
	fprintf(fp, "%d\n", N);
	for(int i=0; i<N; i++, oap++) {
		fprintf(fp, "%d\n", *oap);
	}
	fclose(fp);
}
