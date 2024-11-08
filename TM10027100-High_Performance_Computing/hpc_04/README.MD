# High Performance Computing (HPC)
**Cyberscience Center, Tohoku University**  
Instructor: Hiroyuki Takizawa

---

## Table of Contents
1. [Parallel Computers and Systems](#1-parallel-computers-and-systems)
2. [Software and Resources](#2-software-and-resources)
3. [Parallel Algorithm Design](#3-parallel-algorithm-design)
4. [Running Programs on HPC](#4-running-programs-on-hpc)
5. [Introduction to MPI Programming](#5-introduction-to-mpi-programming)
6. [MPI Programming Basics](#6-mpi-programming-basics)
7. [MPI Functions and Communication Patterns](#7-mpi-functions-and-communication-patterns)
8. [Collective Communication](#8-collective-communication)
9. [Deadlocks and Synchronization](#9-deadlocks-and-synchronization)
10. [Performance Measurement](#10-performance-measurement)
11. [Exercise - Monte Carlo π Calculation](#11-exercise---monte-carlo-π-calculation)
12. [Summary of MPI Programming Concepts](#12-summary-of-mpi-programming-concepts)
13. [Sample Codes](#sample-codes)
    - [Minimal MPI Program](#minimal-mpi-program)
    - [Simple Parallel Reduction Code](#simple-parallel-reduction-code)

---

## Topics Covered

### 1. Parallel Computers and Systems
- **Types of Parallel Systems:**
  - **Vector/SIMD** - Single instruction, multiple data processing.
  - **Shared-memory computers** - Multiple processors access the same memory space.
  - **Distributed-memory computers** - Processors have individual memory; communication via message passing.
  - **Hybrid Systems** - Combine shared and distributed memory, typically managed by one OS instance per node.
- **Hybrid Systems:**
  - Large-scale systems use both shared and distributed parallelism.
  - Each node managed by an OS instance, possibly with GPU accelerators.

### 2. Software and Resources
- **Processes and Threads:** When a program starts, resources are allocated in the form of processes, which run across nodes.
- **Job Level Parallelism:** Involves task scheduling and execution patterns using policies like First-Come-First-Serve (FCFS).

### 3. Parallel Algorithm Design
- **Foster’s Methodology:** Key design steps:
  1. **Partitioning** - Dividing the computation.
  2. **Communication** - Determining data exchange between tasks.
  3. **Agglomeration** - Merging tasks to reduce communication.
  4. **Mapping** - Assigning tasks to processors.

### 4. Running Programs on HPC
- **Batch Jobs:** User jobs are submitted as batches from the front-end server.
- **Job Scheduling:** Efficient resource use through scheduling; basic FCFS policy is common.

### 5. Introduction to MPI Programming
- **MPI Overview:** Message Passing Interface for parallel programming.
  - **MPI Implementations:** MPICH, Open MPI, MVAPICH.
  - **Naming Conventions:** Functions like `MPI_Init`, `MPI_Finalize`, `MPI_Send`, `MPI_Recv`.
  - **Single-Program Multiple-Data (SPMD) Model:** Same program runs across multiple nodes, each with unique data.
- **MPI Model:**
  - **MPI Rank:** ID number of each process.
  - **Communicator:** Group of MPI processes.

### 6. MPI Programming Basics
- **Minimal MPI Program:**
  ```c
  #include <mpi.h>

  int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    MPI_Finalize();
    return 0;
  }
- **Compiling and Running MPI Programs:**
  - Compile with `mpicc -o program program.c`.
  - Run with `mpirun -np <num_processes> ./program`.

### 7. MPI Functions and Communication Patterns
- **Basic MPI Functions:**
  - `MPI_Init`, `MPI_Finalize` - Start/stop MPI.
  - `MPI_Comm_size` - Retrieve the number of processes.
  - `MPI_Comm_rank` - Get the unique rank (ID) of each process.
- **Parallel Reduction with MPI:**
  - Example: `MPI_Reduce` gathers and reduces values from all processes.
  - Common Operators: `MPI_SUM`, `MPI_MAX`, `MPI_MIN`, etc.
- **Peer-to-Peer Communication:** `MPI_Send`, `MPI_Recv` for direct process-to-process messaging.
- **Blocking vs Non-Blocking Communication:**
  - Blocking (e.g., MPI_Send) waits until the operation completes.
  - Non-blocking (e.g., MPI_Isend, MPI_Irecv) allows computation to overlap with communication, with synchronization via MPI_Waitall.

### 8. Collective Communication
- **Collective Operations:**
  - **Reduce & Allreduce:** Aggregate data across processes.
  - **Gather & Allgather:** Collect data from processes.
  - **Scatter & Broadcast:** Distribute data to processes.

### 9. Deadlocks and Synchronization
- **Deadlocks:** Caused when all processes wait indefinitely for each other (e.g., due to unsynchronized blocking communication).
- **Barrier Synchronization:** Ensures processes synchronize before moving to the next step.

### 10. Performance Measurement
- **Benchmarking with MPI_Wtime:** Measure elapsed time for parallel tasks.
- **Barrier Synchronization for Timings:** Use MPI_Barrier for synchronized measurements.

### 11. Exercise - Monte Carlo π Calculation
- **Monte Carlo Simulation:** Estimate π by counting random points within a unit circle.
- **Parallelization Strategy:** Divide workload among MPI processes and use reduction for result aggregation.

### 12. Summary of MPI Programming Concepts
- **Core Skills:**
  - Basic MPI programming and job submission.
  - Collective and peer-to-peer communication.
  - Blocking/non-blocking operations and performance benchmarking.

#### Sample Codes
##### Minimal MPI Program
```c
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    MPI_Finalize();
    return 0;
}
```

##### Simple Parallel Reduction Code
```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size, value = 1, result;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Reduce(&value, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0) printf("Total: %d\n", result);

    MPI_Finalize();
    return 0;
}
```

## Date Types
`MPI_CHAR` => signed char \
`MPI_DOUBLE` => double \
`MPI_FLOAT` => float \
`MPI_INT` => int \
`MPI_LONG` => long \
`MPI_LONG_DOUBLE` => long double \
`MPI_SHORT` => short \
`MPI_USIGNED_CHAR` => unsigned char \
`MPI_UNSIGNED` => unsigned int \
`MPI_UNSIGNED_LONG` => unsigned long \
`MPI_UNSIGNED_SHORT` => unsigned short

## Reduction Operators
`MPI_BAND` => Bitwise AND \
`MPI_BOR` => Bitwise OR \
`MPI_BXOR` => Bitwise eXclusive OR (XOR) \
`MPI_LAND` => Logical AND \
`MPI_LOR` => Logical OR \
`MPI_LXOR` => Logical eXclusive OR (XOR) \
`MPI_MAX` => Maximum \
`MPI_MAXLOC` => Maximum and its location \
`MPI_MIN` => Minimum \
`MPI_MINLOC` => Minimum and its location \
`MPI_PROD` => Product \
`MPI_SUM` => Sum

## Other Comm. Functions
`MPI_Allreduce` => allreduce \
`MPI_Gather` => gather \
`MPI_Allgather` => allgather \
`MPI_Scatter` => scatter \
`MPI_Bcast` => broadcast \
`MPI_Send` => send data (blocking) \
`MPI_Recv` => receive data (blocking) \
`MPI_Isend` => send data(non-blocking) \
`MPI_Irecv` => receive data (non-blocking) \
`MPI_Alltoall` => all-to-all communicationHigh Performance Computing
