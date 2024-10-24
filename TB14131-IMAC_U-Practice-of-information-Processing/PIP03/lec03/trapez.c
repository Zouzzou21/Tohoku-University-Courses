#include <stdio.h>

// Function to compute f(x) = x^2
double f(double x) {
    return x * x;
}

// Function to calculate the integral using trapezoidal rule
double trapezoidal_rule(double L, int N) {
    double h = L / N;  // step size
    double sum = 0.0;
    
    // Array to store f(iL/N) values
    double f_values[N + 1];
    
    // Calculate function values and store in array
    for (int i = 0; i <= N; i++) {
        double x_i = i * h;
        f_values[i] = f(x_i);
    }
    
    // Apply trapezoidal rule
    sum = f_values[0] + f_values[N];  // First and last terms
    for (int i = 1; i < N; i++) {
        sum += 2 * f_values[i];
    }
    sum *= h / 2;
    
    return sum;
}

int main() {
    double L;
    int N;

    // Input values for L and N
    printf("Enter the value of L: ");
    scanf("%lf", &L);
    
    printf("Enter the number of intervals N: ");
    scanf("%d", &N);

    // Compute the integral using trapezoidal rule
    double result = trapezoidal_rule(L, N);
    printf("The approximate value of the integral is: %lf\n", result);
    
    return 0;
}
