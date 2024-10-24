#include <stdio.h>

int main(void)
{
    /**** variable declaration ****/
    int sum = 0;

    /**** processing contents ****/
    for(int i = 0; i <= 1000; i=i+3){
            sum += i;
    }
    
    printf("The sum of numbers that are multiples of 3 from 1 to 1000 is: %d\n", sum);
    return 0;
}
