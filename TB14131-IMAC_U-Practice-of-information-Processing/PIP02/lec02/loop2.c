#include <stdio.h>

int main(void)
{
    /**** variable declaration ****/
    int i;
    int sum = 0;
    /**** processing contents****/
    for(i=1; i <= 1000; i++){
        if(i%3 == 0){
            sum += i;
        }
    }
    printf("The results of the sum of numbers that are multiples of 3 from 1 to 100 is: %d\n", sum);
    return 0;
}
