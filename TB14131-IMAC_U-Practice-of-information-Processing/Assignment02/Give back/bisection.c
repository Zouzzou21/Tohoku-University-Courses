#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define TOLERANCE 1e-8
#define MAX_ITER 1000  // Max iterations for Newton's method or bisection

// Function to evaluate f(x) = x/12 + sin(x)
double f(double x) {
    return x / 12 + sin(x);
}

// Function to evaluate f'(x) for Newton's method, derivative of f(x)
double f_prime(double x) {
    return 1.0 / 12 + cos(x);
}

// Recursive bisection method to find a root in [a, b] to specified tolerance
bool bisection(double a, double b, double *root, int *iterations) {
    double fa = f(a);
    double fb = f(b);
    if (fa * fb > 0) {
        // No root in the interval
        return false;
    }

    double mid = (a + b) / 2.0;
    double fmid = f(mid);
    (*iterations)++;

    if (fabs(fmid) < TOLERANCE || fabs(b - a) < TOLERANCE) {
        *root = mid;
        return true;
    } else if ((*iterations) >= MAX_ITER) {
        return false; // Exceeded max iterations without convergence
    }

    if (fa * fmid < 0) {
        return bisection(a, mid, root, iterations);
    } else {
        return bisection(mid, b, root, iterations);
    }
}

// Newton's method for finding a root near x0
bool newton_method(double x0, double *root, int *iterations) {
    double x = x0;
    for (*iterations = 0; *iterations < MAX_ITER; (*iterations)++) {
        double fx = f(x);
        double fx_prime = f_prime(x);
        
        if (fabs(fx_prime) < TOLERANCE) {
            // Derivative too small; avoid division by near-zero
            return false;
        }
        
        double x_new = x - fx / fx_prime;

        if (fabs(x_new - x) < TOLERANCE) {
            *root = x_new;
            return true;
        }
        x = x_new;
    }
    return false; // Exceeded max iterations without convergence
}

// Function to find all roots in the interval [start, end] using the bisection method
void find_all_roots(double start, double end, double step, bool use_newton) {
    int root_count = 0;
    double root;
    for (double a = start; a < end; a += step) {
        double b = a + step;
        int iterations = 0;
        
        bool found = use_newton ? newton_method((a + b) / 2.0, &root, &iterations)
                                : bisection(a, b, &root, &iterations);

        if (found && root >= a && root <= b) {
            printf("Root %d: %.10f found in [%f, %f] with %d iterations\n", ++root_count, root, a, b, iterations);
        }
    }
    if (root_count == 0) {
        printf("No roots found in the specified interval.\n");
    }
}

int main() {
    double start = -10.0, end = 10.0, step = 1.0;
    bool use_newton = false;
    
    printf("Choose method: 1 for Bisection, 2 for Newton's Method: ");
    int choice;
    scanf("%d", &choice);
    if (choice == 2) use_newton = true;
    
    printf("Finding roots in the interval [%.1f, %.1f] with step %.1f:\n", start, end, step);
    find_all_roots(start, end, step, use_newton);

    return 0;
}
