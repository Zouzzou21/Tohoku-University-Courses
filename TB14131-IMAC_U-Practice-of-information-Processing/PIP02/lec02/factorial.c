#include <stdio.h>

unsigned long long factorial(int n);

int main() {
    int n;
    printf("Enter a natural number: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Factorial is not defined for negative numbers.\n");
    } else {
        printf("Factorial of %d is %llu\n", n, factorial(n));
    }

    return 0;
}

unsigned long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}