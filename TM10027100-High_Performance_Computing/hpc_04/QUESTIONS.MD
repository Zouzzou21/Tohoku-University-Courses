# Question #1
Have you configured your AOBA account? Have you logged-in to AOBA?

# Question #2
Write a parallel version of the code in Slide 47, and paste your code here. How much does parallel execution with 2 nodes reduce the execution time?
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int N = 1000;
    int i, total = 0;
    double x, y;
    
    clock_t start_time, end_time;  // Variables to hold start and end time
    double execution_time;

    start_time = clock();  // Record the start time

    srand(time(NULL));  // Initialization for random numbers
    for (i = 0; i < N; i++) {
        // Generate two random numbers between 0 and 1
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y < 1) {
            total = total + 1;
        }
    }
    printf("pi = %lf\n", 4.0 * total / N);

    end_time = clock();  // Record the end time
    execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;  // Calculate execution time
    printf("Execution time: %lf seconds\n", execution_time);

    return 0;
}
```
```c

```


```c
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int N = 1000;  // Number of iterations, increase for better accuracy
    int i, total = 0, local_total = 0;
    double x, y;
    int rank, size;

    MPI_Init(&argc, &argv);                 // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get the total number of processes

    double start_time, end_time;
    if (rank == 0) start_time = MPI_Wtime(); // Start timing

    srand(time(NULL) + rank); // Seed the random number generator uniquely for each process

    // Divide the work among processes
    int local_N = N / size;  // Each process works on local_N iterations

    for (i = 0; i < local_N; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1) {
            local_total++;
        }
    }

    // Reduce local_totals from all processes to the total in rank 0
    MPI_Reduce(&local_total, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) { // Only the root process calculates and prints pi
        double pi = 4.0 * total / N;
        printf("Estimated Pi value: %lf\n", pi);
        end_time = MPI_Wtime(); // End timing
        printf("Execution Time with %d processes: %lf seconds\n", size, end_time - start_time);
    }

    MPI_Finalize();  // Finalize the MPI environment
    return 0;
}
```
```c

```

# Answer [ans-04.pdf](ans-04.pdf)