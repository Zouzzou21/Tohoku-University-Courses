# Detailed Summary of Lecture: Practice of Information Processing (PIP05)

## Lecture Contents Overview
1. **Previous Exercises Overview**  
   - Review of bubble sort and other sorting algorithms.
   - Visualization exercises for better understanding.
   - Polynomial approximation exercises.

2. **Functions and Their Role in C Programming**
   - **What is a Function?**  
     - A program module that encapsulates specific logic.
     - Can be reused and simplifies the code structure.
     - Functions can accept input (arguments) and return output (return value).

   - **Types of Functions**
     - Functions with return values.
     - Procedures (functions without return values).
     - Recursive functions (functions calling themselves).

   - **Function Definitions and Prototype Declarations**
     - Definition syntax and argument handling.
     - Prototype declaration to avoid compile errors.
     - Use of libraries with `#include` for pre-compiled functions.

3. **Practical Exercises and Code Samples**
   - **Exercise 4-1: Visualization of Bubble Sort**
     - Modify the `sort_bubble.c` to visualize sorting and count operations.
     - Display comparison and replacement counts.

   - **Exercise 4-2: Turn-over Array using Bubble Sort Logic**
     - Reverse the array by comparing and replacing elements from the back.

   - **Exercise 4-3: Selection Sort Implementation**
     - Create and compare `sort_select.c` with bubble sort.
     - Visualize the number of comparisons and replacements.

   - **Exercise 4-4: Polynomial Approximation**
     - Implement 3rd and 5th order McLaughlin series expansions for sin(x).
     - Graph the results to analyze approximation accuracy.

4. **Creating User-defined Functions**
   - **Function Syntax Examples**  
     ```c
     int add_func(int x, int y) {
         int a = x + y;
         return a;
     }
     ```
   - **Handling Return Values and Arguments**
     - At most, one return value allowed.
     - Use global variables or pointers to return multiple values.

   - **Exercises Involving Custom Functions**
     - **Exercise 5-1:** Implement functions for addition, subtraction, multiplication, and division.
     - **Exercise 5-2:** Create `lcm.c` to compute the least common multiple using the Euclidean algorithm.

5. **Recursive Functions**
   - Example of recursion: Factorial calculation.
   - **Exercise 5-3:** Recreate the Euclidean algorithm using recursion in `lcm2.c`.

6. **Scope and Variable Handling**
   - **Global vs. Local Variables**
     - Local variables are limited to function scope.
     - Global variables are accessible across all functions.

   - Example of sharing variables using global scope:
     ```c
     int g_count; // Global variable
     void func1() {
         g_count++;
     }
     ```

7. **Data Types and Structures**
   - **Arrays and Structures**  
     - Arrays store multiple variables of the same type.
     - Structures group variables of different types.
   - Example Structure Declaration:
     ```c
     struct person {
         char name[100];
         double height;
         double weight;
     };
     ```
   - **Exercise 5-4:** Calculate the distance between two points using a structure.

8. **Arrays of Structures**
   - Example of defining an array of structures:
     ```c
     struct person members[3]; // Array of structures
     ```

   - **Exercise 5-5:** Create `struct_array.c` to manage data for multiple people and compute average height and weight.

## Summary
- Reviewed sorting algorithms and visualization techniques.
- Explored the concept and utility of functions in C programming.
- Learned about recursion and function prototypes.
- Understood the use of data structures, arrays, and handling of scope.
- Practical exercises reinforced the lecture topics, helping students apply theory through coding tasks.

## Next Lecture Topics
- **Computer Mechanisms and Memory**
- **Pointers in C Programming**
  - Pointer to variables, arrays, and structures.
