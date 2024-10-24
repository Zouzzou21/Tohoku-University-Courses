#include <stdio.h>

int main(void)
{
    unsigned long long sum = 1;
    unsigned long long max_iterations;
    printf("Enter a number for which you want to know the factorial: ");
    scanf("%llu", &max_iterations);
    for (unsigned long long i = 1; i <= max_iterations; i++)
    {
        sum *= i;
    }
    printf("The factorial of %llu is %llu\n", max_iterations, sum);
}