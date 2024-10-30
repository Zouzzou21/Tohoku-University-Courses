/*
 Mathematical function sin_wave.c
 M_PI is defined in math.h
 MACRO definition of π
 */

#include <stdio.h>
#include <math.h>

int main()
{

    /* (1) variable declaration */
    double t, y;
    double freq = 2.;
    
    /* (2) processing contents */
    for (t = 0.; t <=1.; t += .01){
        y = sin(2.0 * M_PI * freq *t);
        printf("%f %f\n", t, y);
    }
    
	return 0;
}



