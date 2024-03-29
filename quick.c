#include "quick.h"

#include "stats.h"

#include <stdio.h>
#include <stdlib.h>

int partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t i = lo - 1;
    for (uint32_t j = lo; j < hi; j++) {
        if (cmp(stats, A[j - 1], A[hi - 1]) < 0) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[hi - 1]);
    return i + 1;
}

void quick_sorter(Stats *stats, uint32_t *A, int32_t lo, int32_t hi) {
    if (lo < hi) {
        int32_t p = partition(stats, A, lo, hi);
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}

/*int main(void){
	Stats stats;
	uint32_t arr1[] = {100, 3, 4, 5, 2}; 
	quick_sort(&stats, arr1, 5); 
	for (int i=0; i<5; i++){
		printf("%d ", arr1[i]); 
	}
	printf("\n"); 
} */
