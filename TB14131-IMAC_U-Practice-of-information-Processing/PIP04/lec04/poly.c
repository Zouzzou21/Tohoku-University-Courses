/*
calculation of polynomials poly.c
 */

#include <stdio.h>

#define N  4

int main()
{
    /**** (1) variable decracation ****/
    /* set coefficients */
    double	c[N] = {1, 15, -52, 37};
    
    double	x, y;
    int	i ;
    
    /**** (2) processing contents ****/
    for(x = 0; x <= 1.; x += .1){
        for(y = c[N-1], i = N-2; i >= 0; --i) {
            y = y * x + c [i];
        }
        printf("%f %f\n", x, y);
    }
    return 0;
}
