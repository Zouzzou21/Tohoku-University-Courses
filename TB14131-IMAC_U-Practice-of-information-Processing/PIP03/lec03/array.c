/*
 exercise of array: array.c
 */

#include <stdio.h>

#define N 3 /* MACRO definition */

int main()
{

    /**** (1) variable declaration ****/
    int a[N];
    int i, j;
    
    /**** (2) processing contents ****/
    /* initialization of array */
    for (i = 0; i < N; i++){
        a[i] = 0;
    }
    
    /* Operation for arrays */
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;
    
    /* Display arrays */
    for(j = 0; j < N; j++){
        printf("a[%d] = %d\n", j, a[j]);
    }
    
	return 0;

}



