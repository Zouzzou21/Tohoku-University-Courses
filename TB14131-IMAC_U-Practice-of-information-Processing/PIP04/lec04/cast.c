/*
type conversion cast.c
 */

#include <stdio.h>

int main()
{
    /**** (1) variable decracation ****/
    int a = 3;
    int b = 2;
    float g = 9.81;
    float f_val;
    int   i_val;
    
    /**** (2) processing contents ****/
    i_val = g;
    printf("i_val = %d\n", i_val);
    
    f_val = a * g;
    printf("f_val = %f\n", f_val);

    f_val = a / b;
    printf("f_val = %f\n", f_val);

    f_val = (float) a / b;
    printf("f_val = %f\n", f_val);

    return 0;
}
