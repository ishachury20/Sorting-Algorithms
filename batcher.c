#include "batcher.h"

#include "stats.h"

#include <stdio.h>
#include <stdlib.h>

void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {
    //if(A[x] > A[y]){
    if (cmp(stats, A[x], A[y]) > 0) {
        swap(stats, &A[x], &A[y]);
    }
}

uint32_t bit_length(uint32_t x) {
    uint32_t n = 0;
    while (x != 0) {
        x >>= 1;
        n += 1;
    }
    return n;
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }
    uint32_t n_copy = n;
    uint32_t t = bit_length(n_copy);
    uint32_t p = 1 << (t - 1);
    while (p > 0) {
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;
        while (d > 0) {
            for (uint32_t i = 0; i < n - d; i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
        //p -= 1;
    }
}

/*int main(void){
    
	uint32_t n_elements = 4; 

	uint32_t *arr; 
	arr = (uint32_t *)malloc(n_elements * sizeof(uint32_t)); 
	for(uint32_t i = 0; i < n_elements; i++){
		scanf("%u", &arr[i]); 
        } 
	Stats stats = {
	0,
	0, 
	}; 
	batcher_sort(&stats, arr, n_elements); 
	for(uint32_t i= 0; i < n_elements; i++){
		printf("%u\n", arr[i]); 
	} 	
        
} */
