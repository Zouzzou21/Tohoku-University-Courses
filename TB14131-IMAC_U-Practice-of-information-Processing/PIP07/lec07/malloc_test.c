#include <stdio.h>
#include <stdlib.h>

int main() {
    int num, i;
    int array[10];
    int* ptr;

    /**** scan the data from keyboard ****/
    printf("Number of Data? ");
    scanf("%d", &num);

    /**** array version ****/
    for (i = 0; i < num; i++) {
        printf("Enter number %d (array version): ", i + 1);
        scanf("%d", &array[i]);
    }

    /* malloc version */
    ptr = malloc(sizeof(int) * num);
    if (ptr == NULL) {
        /* the case of the memory does not have enough space */
        printf("Memory allocation error\n");
        return 1;
    }

    for (i = 0; i < num; i++) {
        printf("Enter number %d (malloc version): ", i + 1);
        scanf("%d", &ptr[i]);
    }

    /* Display the input data */
    for (i = 0; i < num; i++) {
        printf("%d %d\n", array[i], ptr[i]);
    }

    /* Display the memory usage */
    printf("\n--- Memory usage ---\n");
    printf("Array: %lu [bytes]\n", sizeof(array));
    printf("Malloc: %lu [bytes]\n", num * sizeof(int));

    /* Release the reserved memory space */
    free(ptr);

    return 0;
}
