/* Fibonacci sequence (1) */
#include <stdio.h>
 
int main(void)
{
    /**** variable declaration ****/
    int f1, f2, f3;
    int i, n;
 
     /**** processing contents ****/
    f1 = 1;
    f2 = 1;
    n = 8;
    
    for(i=0;i < n-2; i++){
        f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
    }
    printf("n=%d: fn=%d\n", n, f3);

   return 0;
}
