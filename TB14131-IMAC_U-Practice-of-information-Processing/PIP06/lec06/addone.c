#include <stdio.h>

int a;

/* Function to increment a, b, and *pc */
void addone(int *x, int *y, int *z) {
    (*x)++;
    (*y)++;
    (*z)++;
}

int main(void) {
    FILE *fp;
    int b, c;
    int *pc = &c;

    /* Open the file input.txt and read values */
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open input file\n");
        return 1;
    }

    /* Attempt to read values from file into a, b, and c */
    if (fscanf(fp, "%d, %d, %d", &a, &b, pc) != 3) {
        printf("Error: Failed to read values from file\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    /* Call addone to increment each value by 1 */
    addone(&a, &b, pc);

    /* Print the updated values */
    printf("%d %d %d\n", a, b, *pc);

    return 0;
}
