
#include "sort0.h"
#include <math.h>

#define greater(i,j)	((i) > (j))
#define exch(i,j)	{int k; k=(i); (i)=(j); (j)=(k);}
#define min(i, j)       ((i) < (j))?(i):(j)
#define max(i, j)       ((i) < (j))?(j):(i)
/* #define DEBUG */

void merge(int *A, int l, int mid, int r);

void odd_even_sort(int *A, int l, int r) {
  int diff=0;
  int is_sorted = 0;
#ifdef DEBUG
  printf("[odd-even before] ");
  for(int i=l; i<=r; i++)printf("%d ", A[i]);
  printf("\n");
#endif
  
  while(is_sorted!=3){
    is_sorted |= (1<<diff);

#pragma omp parallel for
    for(int i=l+diff; i<r; i+=2){    
      if(greater(A[i], A[i+1])){
	exch(A[i], A[i+1]);
	is_sorted &= ~(1<<diff);
      }
    }
    diff = (diff+1)%2;
  }
#ifdef DEBUG
  printf("[odd-even after] ");
  for(int i=l; i<=r; i++)printf("%d ", A[i]);
  printf("\n");
#endif
}


int regulate_sequence(int *A, int l, int mid, int r){
  int *tmp = (int *)malloc(sizeof(int)*(r-l+1)); // regulated sequence
  int tmp_l = 0, tmp_r = 0, tmp_mid = 0;
  // calculation the position of the border between odd and even
  if((mid-l)%2 == 0) tmp_r+=(mid-l)/2;
  else tmp_r+=(mid-l+1)/2;
  if((r-mid+1)%2 == 0)tmp_r+=(r-mid+1)/2;
  else tmp_r+=(r-mid+2)/2;  
  tmp_mid = tmp_r;
  // copy A[i] to tmp
  for(int i=l; i<mid; i++){
    if((i-l)%2==0){
      tmp[tmp_l] = A[i];
      tmp_l++;
    }else{
      tmp[tmp_r] = A[i];
      tmp_r++;
    }    
  }
  for(int i=mid; i<=r; i++){
    if((i-mid)%2==0){
      tmp[tmp_l] = A[i];
      tmp_l++;
    }else{
      tmp[tmp_r] = A[i];
      tmp_r++;
    }    
  }
  // copy tmp to A
  for(int i=0; i<(r-l+1); i++){
    A[i+l] = tmp[i];
  }
  free(tmp);
  // merge odd list and even list
  merge(A, l, (l+tmp_mid+l-1)/2+1, tmp_mid+l-1);
  merge(A, tmp_mid+l, (tmp_mid+l+r)/2+1, r);
  return tmp_mid+l;
}

void comparator(int *A, int l, int mid, int r){
  int *tmp = (int *)malloc(sizeof(int) * (r-l+1));
  int tmp_cur = 0;
  int ltop = l, rtop = mid;
  int diff = 0;
  if(mid-l > 1){
    tmp[tmp_cur] = A[ltop];
    tmp_cur++;
    ltop++;
    diff = 1;
  }
  int ul = min(mid-ltop, r-mid+1);
#pragma omp parallel for
  for(int i = ltop; i < ul+ltop; i++){
    tmp[(i-l)*2-diff] = min(A[i], A[i+mid-ltop]);
    tmp[(i-l)*2-diff+1] = max(A[i], A[i+mid-ltop]);
  }
  tmp_cur = (ul+ltop-l)*2-diff;
  ltop = ul+ltop;
  rtop = ul+ltop+mid-ltop;
  while(ltop<mid) tmp[tmp_cur++] = A[ltop++];
  while(rtop<=r) tmp[tmp_cur++] = A[rtop++];

  for(int i=0; i<(r-l+1); i++){
    A[i+l] = tmp[i];
  }

  free(tmp);
}

void merge(int *A, int l, int mid, int r){
  int piv;
#ifdef DEBUG
  printf("[merge] %d %d %d\n", l, mid, r);
  printf("[merge before] ");
  for(int i=l; i<=r; i++){
    printf("%d ", A[i]);
  }
  printf("\n");
#endif
  
  if(r-l > 1)  piv = regulate_sequence(A, l, mid, r);
  else piv = mid;

#ifdef DEBUG  
  printf("[merge regulate] ");
  for(int i=l; i<=r; i++){
    printf("%d ", A[i]);
  }
  printf("\n");
  printf("%d\n", piv);
#endif
  
  comparator(A, l, piv, r);

#ifdef DEBUG
  printf("[merge after] ");
  for(int i=l; i<=r; i++){
    printf("%d ", A[i]);
  }
  printf("\n");
#endif
}

void sortprog(int *A, int l, int r) {
  odd_even_sort(A, l, (l+r)/2);
  odd_even_sort(A, (l+r)/2+1, r);
  merge(A, l, (l+r)/2+1, r);
}

