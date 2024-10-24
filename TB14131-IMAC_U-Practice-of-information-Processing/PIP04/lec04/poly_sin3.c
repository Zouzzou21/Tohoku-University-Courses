#include <stdio.h>

// Factorial function to compute n!
int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

// 3rd-order McLaughlin series for sin(x)
double sin_approx_3rd(double x) {
    return x - (x * x * x) / factorial(3);
}

int main() {
    double x;
    for (x = -2 * 3.14159; x <= 2 * 3.14159; x += 0.1) {
        printf("x: %lf, sin_approx_3rd: %lf\n", x, sin_approx_3rd(x));
    }
    return 0;
}
