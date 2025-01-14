# [IM20111201] アーキテクチャ学(Computer Architecture)
## C4TL1205 - LANDY Lucas (COLABS Student) - [lucas.landy.t3@dc.tohoku.ac.jp](mailto:lucas.landy.t3@dc.tohoku.ac.jp)

---

# Table of Contents
- [Probleme 1](#probleme-1)
- [Probleme 2](#probleme-2)


---

# Probleme 1
Problem Statement
Given the high-level expression:

$ D = \frac{ ( A - B ) \times ( A + B ) }{ C } + \frac{ A - B }{ C } $
​
## Step 1: Assumptions
1. ISA Features:
- Accumulator-based: Single accumulator register interacts with memory for operations.
- Memory-memory: Operands are fetched directly from memory for all operations.
- Stack-based: Operations use a stack for intermediate results. Only push and pop access memory.
- Load-store: All operations use registers (16 general-purpose registers). Memory is accessed only for load/store.
2. Instruction Format:
- Opcode: 1 byte.
- Memory address: 2 bytes.
- Data operand: 4 bytes.
- All instructions are a whole number of bytes.

## Step 2: Assembly Code for Each ISA
### 1. Accumulator-Based Architecture
- Intermediate results are stored in the accumulator or moved to memory.assembly

```assembly
LOAD A          ; Load A into the accumulator (3 bytes)
SUB B           ; Subtract B from the accumulator (3 bytes)
STORE TEMP1     ; Store result (A-B) into TEMP1 (3 bytes)

LOAD A          ; Load A into the accumulator (3 bytes)
ADD B           ; Add B to the accumulator (3 bytes)
STORE TEMP2     ; Store result (A+B) into TEMP2 (3 bytes)

LOAD TEMP1      ; Load TEMP1 (A-B) into the accumulator (3 bytes)
MUL TEMP2       ; Multiply (A-B) * (A+B) (3 bytes)
DIV C           ; Divide by C (3 bytes)
STORE TEMP3     ; Store result into TEMP3 (3 bytes)

LOAD TEMP1      ; Load TEMP1 (A-B) into the accumulator (3 bytes)
DIV C           ; Divide by C (3 bytes)
ADD TEMP3       ; Add TEMP3 and TEMP1/C (3 bytes)
STORE D         ; Store final result into D (3 bytes)
```

Instruction Bytes: $ 12 \times 3 = 36 $

Memory-data Bytes:
- $ A,B,C,TEMP1,TEMP2,TEMP3,D:7 \times 4 = 28 $

### 2. Memory-Memory Architecture
- Operands and results are directly fetched/stored from/to memory.assembly
```assembly
SUB TEMP1, A, B        ; TEMP1 = A - B (10 bytes: 1 opcode + 2 addr each for TEMP1, A, B)
ADD TEMP2, A, B        ; TEMP2 = A + B (10 bytes)
MUL TEMP3, TEMP1, TEMP2; TEMP3 = TEMP1 * TEMP2 (10 bytes)
DIV TEMP3, TEMP3, C    ; TEMP3 = TEMP3 / C (10 bytes)
DIV TEMP4, TEMP1, C    ; TEMP4 = TEMP1 / C (10 bytes)
ADD D, TEMP3, TEMP4    ; D = TEMP3 + TEMP4 (10 bytes)
```
Instruction Bytes: $ 6 \times 10 = 60 $

Memory-data Bytes:
- $ A,B,C,TEMP1,TEMP2,TEMP3,TEMP4,D:8 \times 4 = 32 $

### 3. Stack-Based Architecture
-Operations use a stack, with the top two elements used for operations.
```assembly
PUSH A            ; Push A onto the stack (3 bytes)
PUSH B            ; Push B onto the stack (3 bytes)
SUB               ; Subtract top two elements (1 byte)
PUSH C            ; Push C onto the stack (3 bytes)
DIV               ; Divide top two elements (1 byte)
STORE TEMP1       ; Store TEMP1 = (A-B)/C (3 bytes)

PUSH A            ; Push A onto the stack (3 bytes)
PUSH B            ; Push B onto the stack (3 bytes)
ADD               ; Add top two elements (1 byte)
PUSH TEMP1        ; Push TEMP1 onto the stack (3 bytes)
MUL               ; Multiply top two elements (1 byte)
PUSH C            ; Push C onto the stack (3 bytes)
DIV               ; Divide top two elements (1 byte)
ADD               ; Add top two elements (1 byte)
STORE D           ; Store final result into D (3 bytes)
```

Instruction Bytes: $ 36 $

Memory-data Bytes:
- $ A,B,C,TEMP1,D:5 \times 4 = 20 $

### 4. Load-Store Architecture
- Operands are loaded into registers for operations.
```assembly
LOAD R1, A        ; Load A into R1 (5 bytes: 1 opcode + 4-bit reg + 2-byte addr)
LOAD R2, B        ; Load B into R2 (5 bytes)
SUB R3, R1, R2    ; R3 = R1 - R2 (4 bytes)
LOAD R4, C        ; Load C into R4 (5 bytes)
DIV R5, R3, R4    ; R5 = R3 / R4 (4 bytes)
STORE TEMP1, R5   ; Store TEMP1 = R5 (5 bytes)

ADD R6, R1, R2    ; R6 = R1 + R2 (4 bytes)
MUL R7, R3, R6    ; R7 = R3 * R6 (4 bytes)
DIV R8, R7, R4    ; R8 = R7 / R4 (4 bytes)
ADD R9, R8, R5    ; R9 = R8 + R5 (4 bytes)
STORE D, R9       ; Store D = R9 (5 bytes)
```

Instruction Bytes: $ 49 $

Memory-data Bytes:
- $ A,B,C,TEMP1,D:5 \times 4 = 20 $

## Step 3: Efficiency Analysis
Instruction Bytes Fetched
- Accumulator: $ 36 $
- Memory-memory: $ 60 $
- Stack: $ 36 $
- Load-store: $ 49 $

Most efficient in code size: Accumulator/Stack.

Memory Bandwidth (Code + Data)
- Accumulator: $ 36 + 28 = 64 $
Memory-memory: $ 60 + 32 = 92 $
Stack: $ 36 + 20 = 56 $
Load-store: $ 49 + 20 = 69 $

Most efficient overall: Stack architecture (lowest total bandwidth).


## Summary
- Best in Code Size: Accumulator or Stack.
- Best in Total Bandwidth: Stack.


---


# Probleme 2

Sure! Here’s a **detailed breakdown of Problem 2** that will help you write a comprehensive report. The problem revolves around **matrix transposition** for a 256x256 matrix stored in memory and focuses on cache behavior optimization.

## **Problem Statement Recap**

We are tasked to transpose a $ 256 \times 256 $ double-precision matrix stored in **row-major order**. Each matrix element is 8 bytes (double-precision). The processor has:
- **Cache**: 16 KB, fully associative.
- **Cache block size**: 64 bytes.

We will:
1. Compute **cache misses** during naive transposition.
2. Optimize the transposition using **blocking** and determine:
   - Block size $ B \times B $.
   - New cache misses and miss rate improvement.
3. Write optimized transposition code using $ B $-blocking.
4. Analyze the impact of switching to **single-precision** data.
5. Measure execution time and estimate cache size on a personal computer.

## **Step 1: Naive Transposition Cache Miss Analysis**

### Memory Layout:
- **Row-major order**: Elements in a row are stored contiguously in memory.
- Matrix size:
  - $ 256 \times 256 $ elements.
  - Element size: 8 bytes (double-precision).
  - Total size: $ 256 \times 256 \times 8 = 512 \, \text{KB} $.

### Cache Parameters:
- Cache size: 16 KB.
- Block size: 64 bytes (can store $ 64 / 8 = 8 $ elements).

### Transposition:
For a naive algorithm:
```c
for (i = 0; i < 256; i++) {
    for (j = 0; j < 256; j++) {
        output[j][i] = input[i][j];
    }
}
```

- Access **input[i][j]**:
  - Row-major storage means elements of $ i $-th row are contiguous.
  - Accessing elements sequentially within a row leads to **few cache misses**.
- Access **output[j][i]**:
  - Elements in $ j $-th column are **not contiguous** in row-major order.
  - Accessing $ j $-th column causes frequent cache misses.

### Cache Misses:
- For $ i $-loop (rows of input):
  - Accessing $ input[i][j] $: 1 cache miss for every 8 elements ($ 64 / 8 = 8 $).
  - Total misses for $ input[i][j] $: $ 256 \times \frac{256}{8} = 8192 $.
- For $ j $-loop (columns of output):
  - Accessing $ output[j][i] $: 1 miss for every element (due to column access).
  - Total misses for $ output[j][i] $: $ 256 \times 256 = 65536 $.

**Total Cache Misses (Naive)**:
$8192 + 65536 = 73728$

## **Step 2: Blocking to Optimize Cache Usage**

### Idea of Blocking:
- Divide the matrix into smaller $ B \times B $ submatrices.
- Perform transposition within each block to maximize cache reuse.

### Block Size $ B \times B $:
- Each block fits into the cache.
- Cache can hold $ 16 \, \text{KB} / 8 \, \text{bytes} = 2048 $ elements.
- Optimal block size $ B $ is:
$B \times B \times 8 \, \text{bytes} \leq 16 \, \text{KB} \implies B^2 \leq 2048 \implies B = 32.$

### Cache Miss Analysis (Blocking):
- Input and output accesses are now limited to $ 32 \times 32 $ blocks.
- Cache miss calculations:
  - **Input block**: $ 32 \times 32 = 1024 $ elements ($ 1024 / 8 = 128 $ misses).
  - **Output block**: $ 32 \times 32 = 1024 $ elements ($ 1024 / 8 = 128 $ misses).
- Total misses per block:
  $  128 + 128 = 256.$
- Total blocks:
  $  \frac{256 \times 256}{32 \times 32} = 64.$
- Total cache misses:
  $  256 \times 64 = 16384.$

**Miss Rate Improvement**:
- Naive misses: $ 73728 $.
- Blocking misses: $ 16384 $.
- Improvement:
$\text{Miss rate improvement} = \frac{73728 - 16384}{73728} \times 100\% = 77.8\%.$

## **Step 3: Optimized Code with Blocking**

Here’s the C code using $ B \times B $ blocking:

```c
#define B 32

void transpose(double input[256][256], double output[256][256]) {
    int i, j, ii, jj;
    for (ii = 0; ii < 256; ii += B) {
        for (jj = 0; jj < 256; jj += B) {
            for (i = ii; i < ii + B; i++) {
                for (j = jj; j < jj + B; j++) {
                    output[j][i] = input[i][j];
                }
            }
        }
    }
}
```

## **Step 4: Single-Precision Improvement**

Switching to **single-precision** reduces element size from 8 bytes to 4 bytes:
- Block size $ B $: Cache now holds $ 2 \times \text{elements} $.
$B^2 \leq \frac{16 \, \text{KB}}{4 \, \text{bytes}} \implies B = 45 \, (\text{rounded to 32 or 64 for alignment}).$
- Cache reuse increases further, reducing misses.

## **Step 5: Measuring Execution Time and Cache Size**

To estimate cache size:
1. Run transposition for varying $ B $ values.
2. Measure execution time using the `clock()` function.
3. Plot $ B $ vs. execution time. Look for $ B $ where time is minimized, indicating optimal cache utilization.

Example code snippet for timing:
```c
#include <stdio.h>
#include <time.h>

void timed_transpose(double input[256][256], double output[256][256]) {
    clock_t start, end;
    start = clock();
    
    transpose(input, output);
    
    end = clock();
    printf("Execution Time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}
```

## **Final Report Outline**

1. **Introduction**:
   - Explain matrix transposition and memory access patterns.
   - Discuss cache behavior (temporal/spatial locality).

2. **Naive Transposition**:
   - Present cache miss analysis.
   - Highlight inefficiencies due to row-major layout.

3. **Blocking Optimization**:
   - Explain the concept of blocking.
   - Derive optimal block size.
   - Present miss rate improvement.

4. **Code Implementation**:
   - Provide both naive and optimized code snippets.

5. **Single-Precision Impact**:
   - Discuss how reduced data size further improves cache behavior.

6. **Experimental Analysis**:
   - Describe timing experiments.
   - Plot $ B $-size vs. execution time.
   - Estimate cache size based on results.

7. **Conclusion**:
   - Summarize findings and recommend optimization techniques.









<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
<script type="text/x-mathjax-config">
    MathJax.Hub.Config({ tex2jax: {inlineMath: [['$', '$']]}, messageStyle: "none" });
</script>