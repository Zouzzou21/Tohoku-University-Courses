#include <stdio.h>

int main(){
    
    /**** variable declaration ****/
    float x, y;         /* real type */
    float sum, diff, prod; /* real type */
    float quot;         /* real type */
    
    /**** processing contents ****/
    
    /* get keyboard input */
    scanf("%f %f", &x, &y);
    
    /* sum */
    sum = x + y;
    printf("sum=%f\n", sum);
    
    /* diff */
    diff = x - y;
    printf("diff=%f\n", diff);
    
    /* prod */
    prod = x * y;
    printf("prod=%f\n", prod);
    
    /* quot */
    if ( y == 0){
        printf("quot is not available\n");
    }else{
        quot = (float)x/y;
        printf("quot=%f\n", quot);
    }
    
    return 0;
}
