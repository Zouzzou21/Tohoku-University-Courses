#include <stdio.h>
#include <math.h>

int main(void)
{
    double sum = 0, x = 1.0;
    for(double n = 0; n <= 1000000; n++)
    {
        sum += pow(x,2*n+1)/(2*n+1);
        //printf("%f\n",sum);
    }

    int pi = sum * 4;
    printf("Pi is approximately %.50f\n", pi);
    return 0;
}
