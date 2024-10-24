#include <stdio.h>

int main(void)
{
    /**** variable declaration ****/
    int i;
    int sum = 0;

    /**** processing contents****/
    for(i = 1; i <= 100; i++){
        sum += i;
    }
    printf("The sum from 1 to 100 is: %d\n", sum);
    
    return 0;
}