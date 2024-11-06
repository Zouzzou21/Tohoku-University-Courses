#include <stdio.h>

int main(void) {
    int c;                // Variable to hold each character read from the file
    FILE *fp;             // File pointer to handle file operations
    int count[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Array to store count of each digit from 0 to 9

    // Open the file 'pi.txt' in read mode
    fp = fopen("pi.txt", "r");
    if (fp == NULL) {     // Check if the file opened successfully
        printf("Error opening file\n");
        return 1;
    }

    // Loop to read each character from the file until reaching End of File (EOF)
    while ((c = fgetc(fp)) != EOF) {
        // Check if the character is a digit and increment the corresponding count
        if (c == '0') count[0] = count[0] + 1;
        else if (c == '1') count[1] = count[1] + 1;
        else if (c == '2') count[2] = count[2] + 1;
        else if (c == '3') count[3] = count[3] + 1;
        else if (c == '4') count[4] = count[4] + 1;
        else if (c == '5') count[5] = count[5] + 1;
        else if (c == '6') count[6] = count[6] + 1;
        else if (c == '7') count[7] = count[7] + 1;
        else if (c == '8') count[8] = count[8] + 1;
        else if (c == '9') count[9] = count[9] + 1;
    }

    // Close the file after reading
    fclose(fp);

    // Output the counts of each digit
    printf("Digit counts in pi.txt:\n");
    for (int i = 0; i < 10; i++) {
        printf("Count of %d: %d\n", i, count[i]);
    }

    return 0;
}
