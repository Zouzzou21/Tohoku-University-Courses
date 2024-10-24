/*
 math_calc.c
 */

#include <stdio.h>
#include <math.h> //mathematical function

int main()
{
    
    /**** (1) variable decraration ****/
    double x, y;
    
    /**** (2) processing contents ****/
    x = M_PI;
    
    y = sin(x);
    printf("sin(pi)=%f\n",y);
    
    y = cos(x);
    printf("cos(pi)=%f\n",y);
    
    x = M_E;
    
    y = log(x);
    printf("log(pi)=%f\n",y);
    
    return 0;
    
}



