#include "shell.h"

#include "gaps.h"
#include "stats.h"

#include <stdio.h>
#include <stdlib.h>
//macro for gaps
//gaps.h - file w/ array

void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    for (uint32_t g = 0; g < GAPS; g++) {
        uint32_t gap = gaps[g];
        for (uint32_t i = gap; i < length; i++) {
            uint32_t j = i;
            uint32_t temp = move(stats, arr[i]);
            while (j >= gap && cmp(stats, temp, arr[j - gap]) == -1) {
                arr[j] = move(stats, arr[j - gap]);
                j -= gap;
            }

            arr[j] = move(stats, temp);
        }
    }
}

/*int main(void){
	Stats stats; 
	uint32_t arr1[] = {100, 3, 4, 5, 2}; 
	shell_sort(&stats, arr1, 5); 
	for (int i=0; i<5; i++){
		printf("%d ", arr1[i]); 
	}
	printf("\n"); 
} */
