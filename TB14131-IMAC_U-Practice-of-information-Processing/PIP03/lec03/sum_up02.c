/*
 sum_up02: sample program of while (2）
 Escape by break statement
 */

#include <stdio.h>

int main(){
    
    /* (1) variable decraration */
    int a;
    int sum = 0;
    
    /* (2) processing contents */
    
    while(1){  /* while statement without escape */
        
        scanf("%d", &a); /*formatted input*/
        
        sum += a;
        
        printf("sum = %d\n", sum);
        
        if(a < 0){
            break;
        }
    }
    
    printf("input value is negative\n");
    
    
    return 0;
}

