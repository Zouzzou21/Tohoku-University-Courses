# High Performance Computing (HPC)
**Cyberscience Center, Tohoku University**  
Instructor: Hiroyuki Takizawa

---
## Table of Contents
1. [Overview of Parallel Computing](#1-overview-of-parallel-computing)
2. [Parallel Algorithm Design](#2-parallel-algorithm-design)
3. [Parallel Programming Interfaces](#3-parallel-programming-interfaces)
  - [MPI (Message Passing Interface)](#mpi-message-passing-interface)
  - [OpenMP](#openmp)
4. [Hybrid Programming with MPI and OpenMP](#4-hybrid-programming-with-mpi-and-openmp)
5. [Case Study: Conjugate Gradient Method](#5-case-study-conjugate-gradient-method)
6. [Performance Profiling](#6-performance-profiling)
7. [Performance Prediction and Analysis](#7-performance-prediction-and-analysis)
  - [Roofline Model](#roofline-model)
  - [Amdahl’s Law](#amdahls-law)
  - [Gustafson-Barsis’s Law](#gustafson-barsiss-law)
  - [Karp-Flatt Metric](#karp-flatt-metric)
8. [Key Metrics for Parallel Systems](#8-key-metrics-for-parallel-systems)
9. [Challenges in Achieving Ideal Speedup](#9-challenges-in-achieving-ideal-speedup)
10. [Practical Exercise](#10-practical-exercise)
11. [Summary](#summary)

---

## 1. Overview of Parallel Computing
- **Parallel Computers**: Multi-processor systems designed for parallel programming, categorized into:
  - **Shared-memory computers**: Symmetric multiprocessing and multicore/manycore systems.
  - **Distributed-memory computers**: Systems interconnected through networks, suitable for large-scale applications.
  - **Hierarchical systems**: Combination of shared and distributed memory models.

## 2. Parallel Algorithm Design
- **Foster’s Design Methodology**:
  1. **Partitioning**: Dividing tasks into smaller, independent components.
  2. **Communication**: Defining the data exchange between tasks.
  3. **Agglomeration**: Grouping tasks to reduce communication overhead.
  4. **Mapping**: Assigning tasks to processors.

## 3. Parallel Programming Interfaces
### MPI (Message Passing Interface)
- Supports multiple parallel processes with isolated memory spaces.
- Enables inter-process communication via a defined interface, without implementation details.
- Popular implementations:
  - **MPICH**
  - **Open MPI**

### OpenMP
- Thread-based parallelism, dynamically creating and deleting threads.
- Integration with existing code by adding directives like `#pragma omp parallel`.

## 4. Hybrid Programming with MPI and OpenMP
- Combines the strengths of both models:
  - Reduces communication overhead.
  - Enables overlap of communication and computation.
  - Better scalability for large systems.

## 5. Case Study: Conjugate Gradient Method
- Solves $Ax = b$ iteratively, optimizing a quadratic function $q(x)$.
- **Steps**:
  1. Start with a sequential program.
  2. Profile to find performance bottlenecks.
  3. Parallelize time-intensive functions, such as `matrix_vector_product`.

## 6. Performance Profiling
- Tools like `gprof` help identify bottlenecks in programs.
- Example profiling revealed that `matrix_vector_product` consumed 99.97% of runtime, signaling a focus area for optimization.

## 7. Performance Prediction and Analysis
### Roofline Model
- Analyzes the relationship between memory bandwidth and computation capability to predict performance bottlenecks.

### Amdahl’s Law
- Defines the upper limit of speedup for a fixed problem size.
- Emphasizes the impact of sequential operations and parallelization overhead.

### Gustafson-Barsis’s Law
- Explores scalability when problem size grows with the number of processors.
- Allows better utilization of parallelism.

### Karp-Flatt Metric
- Determines the experimentally observed serial fraction of a computation.
- Useful for identifying inefficiencies like load imbalance and communication delays.

## 8. Key Metrics for Parallel Systems
- **Speedup**: Ratio of sequential to parallel execution time.
- **Efficiency**: Utilization of available processors.
- **Scalability**: Ability to achieve performance gains as the number of processors increases.

## 9. Challenges in Achieving Ideal Speedup
- Serial operations, communication delays, and workload imbalance.
- Overhead from creating and managing parallel threads or processes.

## 10. Practical Exercise
- **Steps**:
  1. Download the source files and upload them to a cluster (e.g., via `scp`).
  2. Compile the program with profiling options.
  3. Run the program to generate profiling data.
  4. Analyze profiling results to identify bottlenecks.
  5. Add OpenMP directives for further optimization.
  6. Experiment with the number of threads and processes to evaluate performance.

## Summary
This class provides a comprehensive framework for understanding and applying parallel computing concepts. It combines theoretical foundations with practical applications. The methodologies discussed are crucial for designing efficient parallel systems and evaluating their performance effectively.