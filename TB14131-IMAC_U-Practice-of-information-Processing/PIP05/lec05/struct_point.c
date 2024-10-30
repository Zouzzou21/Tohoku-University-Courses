#include <stdio.h>
#include <math.h>  // For sqrt() and pow()

// Defining the structure to represent a point with x and y coordinates
struct Point {
    double x;
    double y;
};

int main() {
    // Declaration of two points with given coordinates
    struct Point a = {1.0, 1.0};
    struct Point b = {5.0, 4.0};

    // Calculating the distance between the two points using the formula
    double distance = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));

    // Displaying the coordinates of the two points and the calculated distance
    printf("a = (%.6f, %.6f)\n", a.x, a.y);
    printf("b = (%.6f, %.6f)\n", b.x, b.y);
    printf("distance = %.6f\n", distance);

    return 0;
}
