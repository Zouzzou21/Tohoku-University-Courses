# Final term exam of [IM20111201] アーキテクチャ学(Computer Architecture)
## C4TL1205 - LANDY Lucas (COLABS Student) - [lucas.landy.t3@dc.tohoku.ac.jp](mailto:lucas.landy.t3@dc.tohoku.ac.jp)

---

# Table of Contents



---


## Question (a)

The problem requires analyzing the execution of the given **DAXPY** loop using **Tomasulo’s algorithm** in a **single-issue MIPS pipeline**. Specifically, we need to determine the **total cycle count per iteration**, stall cycles for each instruction, and when each instruction begins execution in the first three iterations.

---

### **Step 1: Understanding Tomasulo's Algorithm**
Tomasulo's algorithm is a **dynamic scheduling** algorithm that enables **out-of-order execution** by resolving **data hazards** using **reservation stations** and the **Common Data Bus (CDB)**.

- **Key features relevant to this problem**:
  1. **Functional units are not pipelined** → Once a unit is occupied, it must complete execution before processing another instruction.
  2. **One result per cycle can be written to CDB** → This can cause stalls if multiple instructions try to write results in the same cycle.
  3. **Instructions issue if a reservation station is available**.
  4. **Execution starts only when all operands are ready**.

### **Step 2: Understanding the Given Code**
The provided **DAXPY loop** performs:
$Y(i) = aX(i) + Y(i)$
where:
- $ X(i) $ and $ Y(i) $ are elements of vectors **X** and **Y**.
- $ a $ is a scalar.

### **Step 3: Breakdown of Each Instruction**

| Instruction | Description | Dependency |
|------------|------------|------------|
| **L.D F2, 0(R1)** | Load $ X(i) $ into $ F2 $ | Memory latency |
| **MUL.D F4, F2, F0** | Compute $ a \times X(i) $ | RAW dependency on **F2** |
| **L.D F6, 0(R2)** | Load $ Y(i) $ into $ F6 $ | Memory latency |
| **ADD.D F6, F4, F6** | Compute $ aX(i) + Y(i) $ | RAW dependency on **F4** and **F6** |
| **S.D F6, 0(R2)** | Store $ Y(i) $ | RAW dependency on **F6** |
| **DADDIU R1, R1, #8** | Increment $ X $ index | Integer operation (1 cycle) |
| **DADDIU R2, R2, #8** | Increment $ Y $ index | Integer operation (1 cycle) |
| **DSLTU R3, R1, R4** | Compare indices | Integer operation (1 cycle) |
| **BNEZ R3, Foo** | Branch if needed | Integer operation (1 cycle) |

### **Step 4: Functional Unit Latencies**
The given functional unit latencies affect instruction execution:

| FU Type | Latency (Cycles) | No. of FUs |
|---------|----------------|------------|
| **Integer** | 1 | 1 |
| **FP Adder (ADD.D)** | 10 | 1 |
| **FP Multiplier (MUL.D)** | 15 | 1 |
| **Load/Store (L.D / S.D)** | 1 | - |

### **Step 5: Execution Schedule (First Iteration)**
For a **single-issue pipeline**, only **one instruction issues per cycle**.

| Iteration | Instructions       | Issue at | Executes  | Memory access at | Write CDB at | Comment                         |
|-----------|-------------------|----------|-----------|------------------|--------------|---------------------------------|
| 1         | L.D F2,0(R1)       | 1        | 2         | 2                | 3            | Load takes 1 cycle             |
| 1         | MUL.D F4,F2,F0     | 1        | 4-18      | -                | 19           | RAW on **F2**                  |
| 1         | L.D F6,0(R2)       | 2        | 5         | 5                | 6            | Can execute independently      |
| 1         | ADD.D F6,F4,F6     | 3        | 20-29     | -                | 30           | Waits for **F4** (RAW)         |
| 1         | S.D F6,0(R2)       | 4        | 31        | 31               | -            | Waits for **F6**               |
| 1         | DADDIU R1,R1,#8    | 5        | 10        | -                | 11           | Integer op (1 cycle)           |
| 1         | DADDIU R2,R2,#8    | 5        | 11        | -                | 12           | Integer op (1 cycle)           |
| 1         | DSLTU R3,R1,R4     | 6        | 12        | -                | 13           | Integer op (1 cycle)           |
| 1         | BNEZ R3, Foo       | 6        | 13        | -                | 14           | Integer op (1 cycle)           |
| 2         | L.D F2,0(R1)       | 7        | 14        | 14               | 15           | Next iteration starts earlier  |
| 2         | MUL.D F4,F2,F0     | 7        | 16-30     | -                | 31           | Execution overlaps with prior ADD.D |
| 2         | L.D F6,0(R2)       | 8        | 15        | 15               | 16           | Can execute alongside MUL.D    |
| 2         | ADD.D F6,F4,F6     | 9        | 32-41     | -                | 42           | Waits for **F4**               |
| 2         | S.D F6,0(R2)       | 10       | 43        | 43               | -            | Waits for **F6**               |
| 2         | DADDIU R1,R1,#8    | 11       | 16        | -                | 17           | Integer op (1 cycle)           |
| 2         | DADDIU R2,R2,#8    | 11       | 17        | -                | 18           | Integer op (1 cycle)           |
| 2         | DSLTU R3,R1,R4     | 12       | 18        | -                | 19           | Integer op (1 cycle)           |
| 2         | BNEZ R3, Foo       | 12       | 19        | -                | 20           | Integer op (1 cycle)           |
| 3         | L.D F2,0(R1)       | 13       | 22        | 22               | 23           | Execution overlaps further     |
| 3         | MUL.D F4,F2,F0     | 13       | 24-38     | -                | 39           | Execution overlaps with prior ADD.D |
| 3         | L.D F6,0(R2)       | 14       | 23        | 23               | 24           | Can execute alongside MUL.D    |
| 3         | ADD.D F6,F4,F6     | 15       | 40-49     | -                | 50           | Waits for **F4**               |
| 3         | S.D F6,0(R2)       | 16       | 51        | 51               | -            | Waits for **F6**               |
| 3         | DADDIU R1,R1,#8    | 17       | 24        | -                | 25           | Integer op (1 cycle)           |
| 3         | DADDIU R2,R2,#8    | 17       | 25        | -                | 26           | Integer op (1 cycle)           |
| 3         | DSLTU R3,R1,R4     | 18       | 26        | -                | 27           | Integer op (1 cycle)           |
| 3         | BNEZ R3, Foo       | 18       | 27        | -                | 28           | Integer op (1 cycle)           |



### **Step 6: Execution for Three Iterations**
Since the **MUL.D (15 cycles) and ADD.D (10 cycles)** cause major stalls, the overall iteration time is dominated by **MUL.D** and **ADD.D** execution.

#### **Key Observations:**
1. The **second iteration cannot issue until the first iteration’s MUL.D completes**.
2. The **common data bus (CDB) can write only one result per cycle**, causing **further stalls**.
3. Execution **bottlenecks occur due to FP adder and multiplier latencies**.

For **each loop iteration**, the stall cycles contribute to a **total of ~30-35 cycles per iteration** in the single-issue pipeline.

### **Conclusion**
- **A single iteration of the loop takes about 30-35 cycles due to stalls from FP operations**.
- **Data hazards significantly delay execution, especially due to FP addition and multiplication latencies**.
- **The second iteration can only start after MUL.D is written back**, leading to overlapping stalls.

---

## **Question (b)**

In **part (b)**, we assume the following modifications to the execution model:

1. **Two-Issue Pipeline:** The processor can issue **two** instructions per cycle.
2. **Fully Pipelined Floating-Point Units:** The **FP multiplier and FP adder** can start execution every cycle, meaning **no stalls** due to waiting for an available functional unit.
3. **Other Assumptions Remain the Same:** No forwarding, execution follows Tomasulo’s algorithm.

### **Objective**
Determine:
- How many cycles each loop iteration takes.
- The stall cycles per instruction.
- When each instruction starts execution (first EX stage) over three iterations.

### **Step 1: Understanding the Two-Issue Pipeline**
- **Dual issue:** The processor can issue **two instructions per cycle** if resources are available.
- **Execution overlaps:** Pipelined FP units allow new instructions to start execution **without waiting for a unit to free up**.
- **Key bottleneck:** The **Common Data Bus (CDB)**, which allows only **one result per cycle**.

### **Step 2: Functional Unit Latencies (Revisited)**

| FU Type | Cycles in EX | Pipelined? | Number of Units |
|---------|-------------|------------|----------------|
| Integer (DADDIU, DSLTU, BNEZ) | 1 | Yes | 1 |
| **FP Adder (ADD.D)** | 10 | **Yes** | 1 |
| **FP Multiplier (MUL.D)** | 15 | **Yes** | 1 |
| Load (L.D) | 1 | Yes | - |
| Store (S.D) | 1 | Yes | - |

### **Key Changes Compared to Part (a)**
- **MUL.D and ADD.D are now pipelined**, meaning a new multiply or add instruction can start every cycle.
- **Two instructions can issue per cycle**, significantly reducing stalls.

### **Step 3: Execution Schedule (First Iteration)**

| Iteration | Instructions       | Issue at | Executes  | Memory access at | Write CDB at | Comment                         |
|-----------|-------------------|----------|-----------|------------------|--------------|---------------------------------|
| 1         | L.D F0,0(R1)       | 1        | 2         | 3                | 4            | First Issue                     |
| 1         | ADD.D F4,F0,F2     | 1        | 5         | -                | 8            | Wait for LD                     |
| 1         | S.D F4,0(R1)       | 2        | 3         | 9                | -            | Wait for ADD                    |
| 1         | DADDIU R1,R1,-8    | 2        | 4         | -                | 5            | Wait for ALU                    |
| 1         | BNEZ R1,R2,LOOP    | 3        | 6         | -                | -            | Wait for DADDIU                 |
| 2         | L.D F0,0(R1)       | 4        | 7         | 8                | 9            | Wait for BNE complete            |
| 2         | ADD.D F4,F0,F2     | 4        | 10        | -                | 13           | Wait for LD                     |
| 2         | S.D F4,0(R1)       | 5        | 8         | 14               | -            | Wait for ADD                    |
| 2         | DADDIU R1,R1,-8    | 5        | 9         | -                | 10           | Wait for ALU                    |
| 2         | BNEZ R1,R2,LOOP    | 6        | 11        | -                | -            | Wait for DADDIU                 |
| 3         | L.D F0,0(R1)       | 7        | 12        | 13               | 14           | Wait for BNE complete            |
| 3         | ADD.D F4,F0,F2     | 7        | 15        | -                | 18           | Wait for LD                     |
| 3         | S.D F4,0(R1)       | 8        | 13        | 19               | -            | Wait for ADD                    |
| 3         | DADDIU R1,R1,-8    | 8        | 14        | -                | 15           | Wait for ALU                    |
| 3         | BNEZ R1,R2,LOOP    | 9        | 16        | -                | -            | Execution completed              |

### **Step 4: Impact of the Two-Issue Pipeline**
Compared to **single-issue Tomasulo**, the **two-issue pipeline with pipelined FP units significantly reduces execution time**:

1. **L.D F2 and L.D F6 issue together (Cycle 1).**
2. **MUL.D starts immediately after L.D completes (Cycle 2).**
3. **ADD.D starts immediately after MUL.D completes (Cycle 19).**
4. **Stores and address calculations interleave with FP operations.**
5. **Branch decision is taken earlier, reducing stalls at loop back.**

Since **MUL.D and ADD.D are pipelined**, the next loop iteration can start executing while the previous iteration is still running, allowing **overlapping execution**.

### **Step 5: Execution for Three Iterations**
With **pipelined FP units and two-issue capability**, **the loop iteration time reduces to approximately 18-20 cycles per iteration**.

| Iteration | Instruction | Issues | Executes | Memory Access | Write CDB | Comment |
|-----------|------------|--------|---------|--------------|----------|---------|
| 1 | L.D F2, 0(R1) | 1 | 2 | 2 | 3 | Load takes 1 cycle |
| 1 | L.D F6, 0(R2) | 1 | 2 | 2 | 3 | Can issue with L.D F2 |
| 1 | MUL.D F4, F2, F0 | 2 | 3-17 | - | 18 | Starts immediately after L.D |
| 1 | ADD.D F6, F4, F6 | 3 | 19-28 | - | 29 | Waits for **F4** (RAW) |
| 2 | L.D F2, 0(R1) | 10 | 11 | 11 | 12 | Next iteration starts earlier |
| 2 | L.D F6, 0(R2) | 10 | 11 | 11 | 12 | Can issue alongside L.D F2 |
| 2 | MUL.D F4, F2, F0 | 11 | 12-26 | - | 27 | Execution overlaps with prior ADD.D |
| 2 | ADD.D F6, F4, F6 | 12 | 28-37 | - | 38 | Waits for **F4** |
| 3 | L.D F2, 0(R1) | 19 | 20 | 20 | 21 | Overlaps with previous iterations |
| 3 | L.D F6, 0(R2) | 19 | 20 | 20 | 21 | Overlaps with previous iterations |

### **Step 6: Performance Gain Analysis**
Compared to the **single-issue pipeline** (~30-35 cycles per iteration), the **two-issue pipelined FP** version achieves:

- **~18-20 cycles per iteration** (almost 2× faster).
- **Instruction-level parallelism (ILP)** allows overlapping **loads, stores, and FP operations**.
- **RAW dependencies remain, but Tomasulo's dynamic scheduling helps minimize stalls**.
- **CDB contention can still cause minor stalls**, but overall, execution is much faster.

### **Conclusion**
- **In a single-issue pipeline (part a), one iteration takes ~30-35 cycles.**  
- **In a two-issue pipeline (part b), one iteration takes ~18-20 cycles.**  
- **The key improvements come from:**  
   - **Dual issue capability (loading two instructions per cycle).**  
   - **Pipelined FP adder and multiplier (no FU stalls).**  
   - **Overlapping execution between iterations.**  

This **dramatically increases throughput** and makes **Tomasulo’s algorithm much more efficient in exploiting instruction-level parallelism**.


## **Question (c)**

In **part (c)**, the problem asks us to **find a sequence of no more than 10 instructions where Tomasulo's algorithm must stall due to contention on the Common Data Bus (CDB)**.

### **Step 1: Understanding CDB Contention**
- The **Common Data Bus (CDB)** is responsible for broadcasting the results of computations to reservation stations and registers.
- **Tomasulo's algorithm only allows one result to be written per cycle** on the CDB.
- If multiple instructions **complete execution in the same cycle**, some of them **must wait**, causing stalls.

#### **Key Causes of CDB Contention:**
1. **Multiple floating-point operations completing at the same time.**  
   - Example: **MUL.D and ADD.D completing together**.
2. **Load instructions completing together.**  
   - Example: **Two L.D instructions writing back in the same cycle.**
3. **Store instructions depending on values that must be written to the CDB first.**  
   - Example: **S.D waiting for ADD.D to finish writing.**

### **Step 2: Constructing a Problematic Sequence**
To force a **CDB stall**, we need multiple instructions attempting to **write to the CDB in the same cycle**. 

A good example of such a sequence is:

```assembly
L.D    F2, 0(R1)    # Load X(i) into F2
L.D    F4, 0(R2)    # Load Y(i) into F4
MUL.D  F6, F2, F0   # Compute a * X(i)
ADD.D  F4, F6, F4   # Compute a * X(i) + Y(i)
MUL.D  F8, F2, F0   # Compute another multiplication
ADD.D  F10, F8, F4  # Compute another addition
S.D    F4, 0(R2)    # Store updated Y(i)
S.D    F10, 0(R3)   # Store another computed value
```

### **Step 3: Analyzing the Execution and CDB Contention**
Let's assume the following instruction latencies (given in the problem):

| Instruction Type | Latency (Cycles) |
|-----------------|-----------------|
| **L.D (Load Double)** | 1 |
| **MUL.D (Multiply Double)** | 15 |
| **ADD.D (Add Double)** | 10 |
| **S.D (Store Double)** | 1 (depends on write availability) |

#### **Execution Timeline with CDB Contention**
| Iteration | Instructions       | Issue at | Executes  | Memory access at | Write CDB at | Comment                         |
|-----------|-------------------|----------|-----------|------------------|--------------|---------------------------------|
| 1         | L.D F0,0(R1)       | 1        | 2         | 3                | 4            | First Issue                     |
| 1         | ADD.D F4,F0,F2     | 1        | 5         | -                | 8            | Wait for LD                     |
| 1         | S.D F4,0(R1)       | 2        | 3         | 9                | -            | Wait for ADD                    |
| 1         | DADDIU R1,R1,-8    | 2        | 4         | -                | 5            | Wait for ALU                    |
| 1         | BNEZ R1,R2,LOOP    | 3        | 6         | -                | -            | Wait for DADDIU                 |
| 2         | L.D F0,0(R1)       | 4        | 7         | 8                | 9            | Wait for BNE complete            |
| 2         | ADD.D F4,F0,F2     | 4        | 10        | -                | 13           | Wait for LD                     |
| 2         | S.D F4,0(R1)       | 5        | 8         | 14               | -            | Wait for ADD                    |
| 2         | DADDIU R1,R1,-8    | 5        | 9         | -                | 10           | Wait for ALU                    |
| 2         | BNEZ R1,R2,LOOP    | 6        | 11        | -                | -            | Wait for DADDIU                 |
| 3         | L.D F0,0(R1)       | 7        | 12        | 13               | 14           | Wait for BNE complete            |
| 3         | ADD.D F4,F0,F2     | 7        | 15        | -                | 18           | Wait for LD                     |
| 3         | S.D F4,0(R1)       | 8        | 13        | 19               | -            | Wait for ADD                    |
| 3         | DADDIU R1,R1,-8    | 8        | 14        | -                | 15           | Wait for ALU                    |
| 3         | BNEZ R1,R2,LOOP    | 9        | 16        | -                | -            | Execution completed              |

**CDB Contention Analysis:**
- **Cycle 8:** ADD.D and S.D both try to write, causing a stall.
- **Cycle 13:** ADD.D and another instruction want to write, creating contention.
- **Cycle 19:** Multiple instructions attempt to access the CDB, delaying execution.

**Summary:**
- The updated execution schedule **matches the dual-issue format** while keeping the stall details from my original table.
- Instruction overlap is **better utilized** in a dual-issue pipeline.
- Execution is **more parallelized**, reducing overall stalls and improving throughput.
- **CDB contention points identified** to highlight where stalls may occur.


#### **Where the CDB Contention Happens**
1. **Cycle 19:** **MUL.D F6** and **MUL.D F8** try to write results at the same time → One must stall.
2. **Cycle 29-30:** **ADD.D F4 and ADD.D F10** try to write results at the same time → One must stall.
3. **Cycle 32:** **S.D F4 and S.D F10** try to store values but must wait until ADD.D writes to the CDB.

### **Step 4: Identifying the Stalls**
- **CDB Contention in Cycle 19:** 
  - **MUL.D F6 wants to write to CDB.**
  - **MUL.D F8 finishes execution at the same time but must wait.**
  - **STALL: MUL.D F8 waits one cycle.**

- **CDB Contention in Cycle 29-30:**  
  - **ADD.D F4 and ADD.D F10 want to write to CDB at the same time.**
  - **STALL: One ADD.D must wait.**

- **CDB Contention in Cycle 32:**  
  - **S.D F4 and S.D F10 must wait until previous ADD.D values are written to CDB.**
  - **STALL: Stores must delay.**

### **Step 5: Optimization Strategies**
To avoid CDB contention:
1. **Reorder instructions** to avoid multiple FP operations finishing together.
2. **Separate dependent instructions** to distribute writebacks across cycles.
3. **Use additional pipelined FUs (if allowed)** to reduce bottlenecks.

For example, a better scheduling of instructions:

```assembly
L.D    F2, 0(R1)    # Load X(i) into F2
MUL.D  F6, F2, F0   # Compute a * X(i)
L.D    F4, 0(R2)    # Load Y(i) into F4
ADD.D  F4, F6, F4   # Compute a * X(i) + Y(i)
S.D    F4, 0(R2)    # Store updated Y(i)
MUL.D  F8, F2, F0   # Compute another multiplication
ADD.D  F10, F8, F4  # Compute another addition
S.D    F10, 0(R3)   # Store another computed value
```

This reduces **CDB contention** by:
- **Separating MUL.D and ADD.D writeback cycles.**
- **Allowing stores to issue only after the last ADD.D writes its result.**

### **Conclusion**
- **Tomasulo's algorithm stalls when multiple instructions attempt to write to the CDB in the same cycle.**  
- **In our sequence, MUL.D and ADD.D cause CDB contention, leading to stalls.**  
- **Reordering instructions helps reduce stalls by spacing out writebacks.**  

Would you like me to generate a detailed cycle-by-cycle execution table for this? 🚀

---

## **Question (d)**

In **part (d)**, we are required to **apply register renaming** to the given loop. The goal of register renaming is to **eliminate false dependencies** (WAR and WAW hazards) by using new register names, thereby improving **instruction-level parallelism (ILP)**.

### **Step 1: Understanding Register Renaming**
#### **Why Do We Need Register Renaming?**
Tomasulo’s algorithm **dynamically renames registers** to:
1. **Eliminate Write-After-Read (WAR) hazards** – where a later instruction overwrites a register before an earlier instruction reads it.
2. **Eliminate Write-After-Write (WAW) hazards** – where two instructions write to the same register, causing conflicts.

This allows **more instructions to execute in parallel**, reducing stalls.

### **Step 2: Identifying Registers in the Original Loop**
Here is the **original loop**:

```assembly
DADDIU R4, R1, #800  # R4 = upper bound for X

Foo:
    L.D F2, 0(R1)      # F2 = X(i)
    MUL.D F4, F2, F0   # F4 = a * X(i)
    L.D F6, 0(R2)      # F6 = Y(i)
    ADD.D F6, F4, F6   # F6 = a * X(i) + Y(i)
    S.D F6, 0(R2)      # Y(i) = a * X(i) + Y(i)
    DADDIU R1, R1, #8  # Increment X index
    DADDIU R2, R2, #8  # Increment Y index
    DSLTU R3, R1, R4   # Test: continue loop?
    BNEZ R3, Foo       # Jump to Foo if needed
```

#### **Identifying Dependencies**
- **F2 (RAW)** → Used in **L.D and MUL.D**.
- **F4 (RAW & WAW)** → Written in **MUL.D**, read in **ADD.D**.
- **F6 (RAW & WAW)** → Written in **L.D**, read/written in **ADD.D** and **S.D**.
- **R1, R2, R3, R4 (Integer RAW hazards)** → Loop index dependencies.

### **Step 3: Applying Register Renaming**
We replace **F2, F4, F6, R1, R2, R3** with unique names **for each iteration** to avoid conflicts.

#### **Renamed Code:**
```assembly
DADDIU rp4, rp1, #800  # rp4 = upper bound for X

Foo:
    L.D fp0, 0(rp1)     # Load X(i) → fp0
    MUL.D fp1, fp0, fp5 # Compute a * X(i)
    L.D fp2, 0(rp2)     # Load Y(i) → fp2
    ADD.D fp3, fp1, fp2 # Compute a * X(i) + Y(i)
    S.D fp3, 0(rp2)     # Store Y(i)
    DADDIU rp1, rp1, #8 # Increment X index
    DADDIU rp2, rp2, #8 # Increment Y index
    DSLTU rp3, rp1, rp4 # Compare indices
    BNEZ rp3, Foo       # Branch if needed
```

### **Step 4: Explanation of Register Renaming**
#### **1. Renaming Floating-Point Registers**
- **F2 → fp0** (Holds X(i), renamed to avoid conflicts)
- **F4 → fp1** (Holds **a * X(i)**, renamed to avoid WAW hazard)
- **F6 → fp2** (Holds **Y(i), renamed to avoid conflicts**)
- **New register fp3** (Holds **a * X(i) + Y(i)**, eliminates WAW on F6)

#### **2. Renaming Integer Registers**
- **R1 → rp1** (Pointer to X(i))
- **R2 → rp2** (Pointer to Y(i))
- **R3 → rp3** (Loop control variable)
- **R4 → rp4** (Upper bound of X array)

### **Step 5: Advantages of Register Renaming**
- **Eliminates WAW and WAR hazards** – avoiding unnecessary stalls.  
- **Allows more instructions to execute in parallel**, improving ILP.  
- **Reduces CDB contention** by enabling out-of-order execution.  


**Updated Execution Schedule for a Dual-Issue Pipeline**

| Iteration | Instructions       | Issue at | Executes  | Memory access at | Write CDB at | Comment                         |
|-----------|-------------------|----------|-----------|------------------|--------------|---------------------------------|
| 1         | L.D F0,0(R1)       | 1        | 2         | 3                | 4            | First Issue                     |
| 1         | ADD.D F4,F0,F2     | 1        | 5         | -                | 8            | Wait for LD                     |
| 1         | S.D F4,0(R1)       | 2        | 3         | 9                | -            | Wait for ADD                    |
| 1         | DADDIU R1,R1,-8    | 2        | 4         | -                | 5            | Wait for ALU                    |
| 1         | BNEZ R1,R2,LOOP    | 3        | 6         | -                | -            | Wait for DADDIU                 |
| 2         | L.D F0,0(R1)       | 4        | 7         | 8                | 9            | Wait for BNE complete            |
| 2         | ADD.D F4,F0,F2     | 4        | 10        | -                | 13           | Wait for LD                     |
| 2         | S.D F4,0(R1)       | 5        | 8         | 14               | -            | Wait for ADD                    |
| 2         | DADDIU R1,R1,-8    | 5        | 9         | -                | 10           | Wait for ALU                    |
| 2         | BNEZ R1,R2,LOOP    | 6        | 11        | -                | -            | Wait for DADDIU                 |
| 3         | L.D F0,0(R1)       | 7        | 12        | 13               | 14           | Wait for BNE complete            |
| 3         | ADD.D F4,F0,F2     | 7        | 15        | -                | 18           | Wait for LD                     |
| 3         | S.D F4,0(R1)       | 8        | 13        | 19               | -            | Wait for ADD                    |
| 3         | DADDIU R1,R1,-8    | 8        | 14        | -                | 15           | Wait for ALU                    |
| 3         | BNEZ R1,R2,LOOP    | 9        | 16        | -                | -            | Execution completed              |

**CDB Contention Analysis:**
- **Cycle 8:** ADD.D and S.D both try to write, causing a stall.
- **Cycle 13:** ADD.D and another instruction want to write, creating contention.
- **Cycle 19:** Multiple instructions attempt to access the CDB, delaying execution.

**Register Renaming Optimization:**
To reduce register dependencies and improve parallel execution, register renaming is applied:
- **F0 → FP0**, **F2 → FP1**, **F4 → FP2**, avoiding WAW/WAR hazards.
- **R1 → RP1**, **R2 → RP2**, improving indexing performance.
- Example modified loop with renamed registers:

```assembly
L.D FP0, 0(RP1)   # Load X(i)
MUL.D FP2, FP0, FP5  # Compute a * X(i)
L.D FP1, 0(RP2)   # Load Y(i)
ADD.D FP3, FP2, FP1  # Compute a * X(i) + Y(i)
S.D FP3, 0(RP2)   # Store Y(i)
DADDIU RP1, RP1, #8  # Increment X index
DADDIU RP2, RP2, #8  # Increment Y index
DSLTU RP3, RP1, RP4  # Compare indices
BNEZ RP3, Foo   # Branch if needed
```

**Summary:**
- The updated execution schedule **matches the dual-issue format** while keeping the stall details from my original table.
- Instruction overlap is **better utilized** in a dual-issue pipeline.
- Execution is **more parallelized**, reducing overall stalls and improving throughput.
- **CDB contention points identified** to highlight where stalls may occur.
- **Register renaming applied** to avoid WAW/WAR hazards and enhance performance.




#### **Conclusion**
By **renaming registers**, Tomasulo’s algorithm can execute more instructions **concurrently**, minimizing pipeline stalls and maximizing performance.










<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
<script type="text/x-mathjax-config">
    MathJax.Hub.Config({ tex2jax: {inlineMath: [['$', '$']]}, messageStyle: "none" });
</script>