
#include "sort0.h"

#define greater(i,j)	((i) > (j))
#define exch(i,j)	{int k; k=(i); (i)=(j); (j)=(k);}

void sortprog(int *A, int l, int r) {
	int i, j;

	for (i = r; i > l; i--) {
		for (j = l; j < i; j++) {
			if (greater(A[j], A[j + 1])) exch(A[j], A[j + 1]);
		}
	}
}

