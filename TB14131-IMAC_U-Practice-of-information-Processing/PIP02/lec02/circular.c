#include <stdio.h>

int main() {
    // Initialize variables
    double x=1.0, sum=0.0; // arctan(x) = arctan(1) = π/4
    int max_iterations = 1000000; // Number of terms to sum

    // Calculate the series sum
    for (int n = 0; n < max_iterations; n++) {
        sum += (n % 2 == 0 ? 1.0 : -1.0) * (1.0 / (2 * n + 1));
    }

    // Multiply by 4 to get π
    double pi = 4.0 * sum;

    // Print the result
    printf("Approximate value of π: %.50f\n", pi);

    return 0;
}