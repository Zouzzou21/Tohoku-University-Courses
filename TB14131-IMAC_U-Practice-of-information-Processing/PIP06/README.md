# Detailed Summary of Lecture 6: Programming in C (PIP06 - IMACU)
[PIP06_slide2024.pdf](PIP06_slide2024.pdf)
## Table of Contents

1. [Pointers and Memory Addressing](#1-pointers-and-memory-addressing)
2. [Function Calls: Call-by-Value vs. Call-by-Reference](#2-function-calls-call-by-value-vs-call-by-reference)
3. [File Input/Output in C](#3-file-inputoutput-in-c)
4. [Summary of Key Concepts](#4-summary-of-key-concepts)

---

### 1. **Pointers and Memory Addressing**
   - **Memory Addressing**:
     - **32-bit OS**: Limited to 4GB of addressable memory.
     - **64-bit OS**: Theoretically supports up to 17.1 billion GB.
   - **Pointers**:
     - A pointer holds the memory address of a variable and must match the variable's type.
     - Using the `&` operator provides the variable’s address, and `*` accesses the value at that address.

---

### 2. **Function Calls: Call-by-Value vs. Call-by-Reference**
   - **Call-by-Value**: Only the argument's value is passed, isolating the function from modifying the original variable.
   - **Call-by-Reference**: Pointers enable functions to modify variables outside their scope by directly accessing memory addresses.

---

### 3. **File Input/Output in C**
   - **File Pointers**: FILE pointers enable files to be opened, read, written, and closed.
   - **File Access Modes**:
      - `"r"` - Read-only
      - `"w"` - Write (overwrites existing files)
      - `"a"` - Append (adds to the end of files)
   - **Functions**:
      - `fprintf` and `fscanf`: Format-based file writing and reading.
      - `fputc` and `fgetc`: Character-based file I/O.
      - `fputs` and `fgets`: String-based file I/O.
   - **Exercise 6-4**: File opening and handling errors.
   - **Exercise 6-5**: Writing to a file in different modes.
   - **Exercise 6-6**: Counting digit occurrences in a file.
   - **Exercise 6-7**: Function for incrementing variable values read from a file.

---

### 4. **Summary of Key Concepts**
   - **Pointers and Memory**: Using pointers for memory management.
   - **File I/O**: Essential functions for reading from and writing to files.
   - **Next Lecture Topics**: Further exploration of pointers and final report preparation.

---
