#include <stdio.h>
#include <math.h>
#include <complex.h>  // Required for complex numbers

/* Function prototypes */
void calculateRoots(double a, double b, double c);

int main() {
    double a, b, c;

    printf("Enter coefficients a, b, and c (for ax^2 + bx + c = 0):\n");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a == 0) {
        printf("The value of 'a' cannot be 0 for a quadratic equation.\n");
        return 1;
    }

    calculateRoots(a, b, c);

    return 0;
}

/* Function to calculate and display the roots of the quadratic equation */
void calculateRoots(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        /* Two distinct real roots */
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("The roots are real and different:\n");
        printf("Root 1 = %.6lf\n", root1);
        printf("Root 2 = %.6lf\n", root2);
    } else if (discriminant == 0) {
        /* One real root (double root) */
        double root = -b / (2 * a);
        printf("The roots are real and identical:\n");
        printf("Root = %.6lf\n", root);
    } else {
        /* Complex roots */
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-discriminant) / (2 * a);
        printf("The roots are complex:\n");
        printf("Root 1 = %.6lf + %.6lfi\n", realPart, imaginaryPart);
        printf("Root 2 = %.6lf - %.6lfi\n", realPart, imaginaryPart);
    }
}
