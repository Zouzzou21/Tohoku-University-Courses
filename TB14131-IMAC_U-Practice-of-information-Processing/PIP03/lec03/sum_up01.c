/*
 sum_up01: sample program for while (1)
 Make the condition which becomes false in condition statement
 */

#include <stdio.h>

int main(){

    /* (1) variable declaration */
    int a;
    int sum = 0;
    
    /* (2) processing contents */
    
    while(sum < 100){  /* while statement */
        
        scanf("%d", &a); /*formatted input*/
        
        sum += a;
        
        printf("sum = %d\n", sum);
        
    }
    
    printf("sum is more than 100\n");

	
	return 0;
}

