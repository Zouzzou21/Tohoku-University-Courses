#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int main() {
    char str[MAX_LENGTH];
    int length, i;

    printf("Enter a string: ");
    fgets(str, MAX_LENGTH, stdin);

    // Remove the newline character if present
    length = strlen(str);
    if (str[length - 1] == '\n') {
        str[length - 1] = '\0';
        length--;
    }

    printf("Reversed string: ");
    for (i = length - 1; i >= 0; i--) {
        putchar(str[i]);
    }
    printf("\n");

    return 0;
}