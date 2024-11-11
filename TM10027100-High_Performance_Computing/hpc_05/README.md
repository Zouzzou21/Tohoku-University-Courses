# High Performance Computing (HPC)
**Cyberscience Center, Tohoku University**  
Instructor: Hiroyuki Takizawa

---

## Table of Contents


---

## 1. Introduction to High-Performance Computing (HPC)
   - **HPC Systems**: Use multiple processors to handle complex computations efficiently.
     - **Distributed-memory parallel computers**: Multiple interconnected computers, suitable for large-scale systems.
     - **Shared-memory parallel computers**: Use symmetric multiprocessing (SMP) or multicore processors.
   - **Large-Scale Systems**: Often a combination of distributed and shared-memory systems, sometimes incorporating GPUs or other accelerators.

---

## 2. Parallel Programming Fundamentals
   - **Parallel Programming**: Allows simultaneous execution of tasks, crucial for HPC.
   - **Standards**:
     - **OpenMP**: For shared-memory systems.
     - **MPI**: For distributed-memory systems.
   - **Challenges**: Managing memory and balancing tasks across multiple processors.

---

## 3. Core Concepts in Parallel Processing with OpenMP
   - **Data Parallelism**: Divides data across multiple processors, where each processor performs the same task on different data segments.
   - **Work-Sharing Constructs**:
     - OpenMP directives (e.g., `#pragma omp parallel for`) allow for automatic data distribution in parallel loops.
   - **Thread Management**:
     - Directives like `#pragma omp parallel` create threads.
     - `OMP_NUM_THREADS` environment variable controls the number of threads.

---

## 4. Data Management in OpenMP
   - **Shared and Private Variables**:
     - By default, variables are shared across threads, except for loop indices which remain private.
     - **Private Variables**: Allow each thread to have unique values, critical for avoiding race conditions.
     - **Critical Sections**: Managed by `#pragma omp critical`, preventing concurrent access to shared resources.
   - **Clauses**:
     - Options like `shared`, `private`, `reduction`, `nowait` specify variable behavior and optimize performance.

---

## 5. Task Parallelism
   - **Sections Directive**:
     - `#pragma omp sections` divides different sections of code, running them in parallel on separate threads, enabling task-parallel execution.

---

## 6. Heterogeneous Computing and Offloading
   - **Heterogeneous Processors**:
     - **CPU**: Optimized for latency with cache memory.
     - **GPU**: Designed for throughput, highly parallelized, suitable for matrix operations.
   - **GPU Offloading with Target Directives**:
     - `#pragma omp target` and `#pragma omp teams distribute` enable specific tasks to run on GPUs, increasing processing throughput.

---

## 7. Performance and Scalability Considerations
   - **Scalability**:
     - **Amdahl's Law**: Describes the limits of speedup as parallelism increases; only highly parallel tasks gain from more processors.
     - **Pareto Principle**: A small portion of code often consumes most of the time; optimizing this part is essential.
   - **Parallelization Overheads**:
     - Includes thread creation and synchronization delays, limiting linear scalability with increased thread counts.

---

## 8. Optimization Techniques
   - **Compiler Directives and Clauses**: Used to control parallel execution and fine-tune memory management and task synchronization.
   - **Load Balancing and Memory Mapping**:
     - Techniques to optimize data distribution and minimize synchronization costs across memory.
