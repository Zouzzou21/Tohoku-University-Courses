#include <stdio.h>
#include <time.h>

#define N 256  // Matrix size

void transpose_blocked(double input[N][N], double output[N][N], int B) {
    // Iterate over blocks
    for (int ii = 0; ii < N; ii += B) {
        for (int jj = 0; jj < N; jj += B) {
            // Iterate over elements within a block
            for (int i = ii; i < ii + B && i < N; i++) {
                for (int j = jj; j < jj + B && j < N; j++) {
                    output[j][i] = input[i][j];
                }
            }
        }
    }
}

int main() {
    clock_t start, end;
    double input[N][N];
    double output[N][N];
    int B = 32;  // Block size

    // Initialize the input matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            input[i][j] = i * N + j;
        }
    }

    start = clock();
    // Perform the blocked transposition
    transpose_blocked(input, output, B);
    end = clock();

    // Print a portion of the matrices for verification (optional)
    printf("Input matrix (partial):\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%8.2f ", input[i][j]);
        }
        printf("\n");
    }

    printf( "\nProcessing time:%d[ms]³\n", end - start );

    printf("\nOutput matrix (partial):\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%8.2f ", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}