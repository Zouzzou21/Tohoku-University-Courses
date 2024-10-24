/*
 selection sort with visual display - sort_select.c
 */

#include <stdio.h>

/* Macro definition */
#define NUM 10

int main()
{
    /**** (1) variable declaration ****/
    int A[NUM] = {8, 2, 7, 4, 5, 6, 9, 0, 1, 3};
    int i, j, min_idx, temp;

    int comparison_count = 0;
    int replacement_count = 0;

    /**** (2) processing contents ****/

    /* display array before sorting */
    printf("Initial array: ");
    for (i = 0; i < NUM; i++) {
        printf("%d ", A[i]);
    }
    printf("\n\n");

    for (i = 0; i < NUM - 1; i++) {
        min_idx = i;

        printf("[%d] *", i);  // Indicate which element will be replaced.
        for (int k = 0; k < NUM; k++) {
            if (k == i) {
                printf(" *%d ", A[k]);  // Mark the element to be swapped with '*'.
            } else {
                printf(" %d ", A[k]);
            }
        }
        printf("\n");

        for (j = i + 1; j < NUM; j++) {
            comparison_count++;

            printf("[%d] ", i);  // Indicate the current comparison pass.

            for (int k = 0; k < NUM; k++) {
                if (k == min_idx) {
                    printf("!%d ", A[k]);  // Mark the minimum element found so far with '!'.
                } else if (k == j) {
                    printf(">%d ", A[k]);  // Mark the element currently being compared with '>'.
                } else {
                    printf(" %d ", A[k]);
                }
            }
            printf("\n");

            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            // Swap A[i] and A[min_idx]
            temp = A[i];
            A[i] = A[min_idx];
            A[min_idx] = temp;
            replacement_count++;
        }
    }

    /* display array after sorting */
    printf("\nSorted array: ");
    for (i = 0; i < NUM; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    printf("Comparisons: %d\n", comparison_count);
    printf("Replacements: %d\n", replacement_count);

    return 0;
}
