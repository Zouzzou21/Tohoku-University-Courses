#include <stdio.h>

int main()
{    
    /**** variable declaration ****/
    int x, y;           /* int type */
    int sum, diff, prod;   /* int type */
    float quot;         /* real type */
    
    /**** processing contents ****/
    
    /* assignment */
    x = 3;
    y = 2;
    
    /* sum */
    sum = x + y;
    printf("sum=%d\n", sum);
    
    /* diff */
    diff = x - y;
    printf("diff=%d\n", diff);
    
    /* prod */
    prod = x * y;
    printf("production=%d\n", prod);
    
    /* quot */
    if ( y == 0){
        printf("quotient is not available\n");
    }else{
        quot = (float)x/y;
        printf("quotient=%f\n", quot);
    }
    
    return 0;
}
