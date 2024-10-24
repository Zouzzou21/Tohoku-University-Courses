#include <stdio.h>

// Factorial function to compute n!
int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

// 5th-order McLaughlin series for sin(x)
double sin_approx_5th(double x) {
    return x - (x * x * x) / factorial(3) + (x * x * x * x * x) / factorial(5);
}

int main() {
    double x;
    for (x = -2 * 3.14159; x <= 2 * 3.14159; x += 0.1) {
        printf("x: %lf, sin_approx_5th: %lf\n", x, sin_approx_5th(x));
    }
    return 0;
}
