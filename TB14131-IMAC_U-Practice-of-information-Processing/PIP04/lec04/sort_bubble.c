/*
 bubble sort sort_bubble.c
 */

#include <stdio.h>

/* Macro definition */
#define NUM 10

int main()
{
    
    /**** (1) variable declaration ****/
    int A[NUM] = {8,2,7,4,5,6,9,0,1,3};
    
    
    int i, j, temp;

    
    /**** (2) processing contents ****/

    /* display array before sorting */
    for (i=0;i<NUM;i++){
        printf("%d ",A[i]);
    }
    printf("\n");

    
    for (i = 0; i < NUM-1; i++) {
        
        for (j = 0; j < NUM-i-1; j++) {
            if (A[j] > A[j+1]) {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
        
    }

    /* display array after sorting */
    for (i=0;i<NUM;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
    
    return 0;
    
}
