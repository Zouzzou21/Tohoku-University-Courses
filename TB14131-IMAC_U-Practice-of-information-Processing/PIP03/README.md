# Practice of Information Processing (IMACU) - Third Lecture
[PIP03_slide2024.pdf](PIP03_slide2024.pdf)
## Instructor: Makoto Hirota

### Part 1: Review and Introduction to Iteration and Selection

---

#### **1. Review of Previous Lecture**
- **Topic:** `for` statement
- **Example:** Iterating to display numbers (e.g., hello: 0 to hello: 9).
- **Exercise:** Modify code to calculate sums (1 to 100, multiples of 3 from 1 to 1000).

#### **2. For Statement**
- Execution steps of a `for` loop:
  1. Execute the initial condition.
  2. Perform the loop block.
  3. Increment.
  4. Check continuation condition, repeat if true.

---

### Part 2: Iteration and Selection Process

---

#### **1. Iteration Processes**
- **for**: Iterates a fixed number of times.
- **while**: Repeats while a condition is true.
- **do-while**: Executes at least once, then checks the condition.

#### **2. Selection Processes**
- **if statement**: Executes code if a condition is true.
- **else if**: Allows for multiple conditions.
- **else**: Executes if no other condition is met.
- **switch statement**: Selects code based on the value of a variable.

---

### Part 3: Exercises and Model Answers

---

#### **1. Factorial Calculation (`factorial.c`)**
- Program to calculate factorial of a number using a `for` loop.
- **Caution:** Large numbers may exceed the integer limit, resulting in incorrect output.

#### **2. Calculation of π (`circular.c`)**
- Approximation of π using an iterative method based on the arctangent series.

#### **3. Exercises with `while` loop**
- **Example 1:** Exiting a loop when a sum reaches a value.
- **Example 2:** Using a `break` statement to exit an infinite loop.

---

### Part 4: Arrays and Strings

---

#### **1. Array Basics**
- Arrays store multiple values of the same type.
- Elements are accessed using an index starting from 0.
- Initialization can be done individually or during declaration.

#### **2. Strings as Arrays of `char`**
- Strings are arrays of characters in C, terminated by a NUL (`\0`) character.

#### **3. Multi-dimensional Arrays**
- Example: A 2D array for storing tabular data.

---

### Part 5: Exercises

---

#### **1. Array Input and Manipulation (`array_input.c`)**
- Input 5 integers into an array, display them, and calculate their sum.

#### **2. String Reversal (`reverse.c`)**
- Reverse the input string and display it.
  
#### **3. Matrix Multiplication (`matrix_multiple.c`)**
- Multiply two matrices (4x3 and 3x4) and display the result.

#### **4. Numerical Integration (`trapez.c`)**
- Approximate the integral of a function using the trapezoidal rule.

---

### Summary of Key Topics
- **Selection Process**: if, switch.
- **Iteration Process**: for, while.
- **Array Handling**: Indexing, initialization, string manipulation.
- **Multidimensional Arrays**: Usage and initialization.

---

### Next Steps
- **Upcoming Topics:**
  - Array exercises.
  - Midterm report.
