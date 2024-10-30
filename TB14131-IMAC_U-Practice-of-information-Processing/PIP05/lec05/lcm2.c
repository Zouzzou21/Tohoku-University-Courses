#include <stdio.h>

// Recursive function to calculate GCD using rgcd(a, b)
int rgcd(int a, int b) {
    if (b == 0)
        return a;
    return rgcd(b, a % b);
}

// Function to calculate LCM using the GCD
int lcm(int a, int b) {
    return (a * b) / rgcd(a, b);
}

int main() {
    int num1, num2;

    // Input two integers from the user
    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    // Calculate and print the LCM
    printf("LCM of %d and %d is %d\n", num1, num2, lcm(num1, num2));

    return 0;
}