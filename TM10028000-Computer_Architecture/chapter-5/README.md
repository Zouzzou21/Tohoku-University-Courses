# 


## Table of contents
1. Trends in Computer Architecture Design
2. Instruction Set Principles and Examples
3. Pipelining
4. Memory Hierarchy (1/7)
5. Instruction Level Parallelism and Its Exploitation(1/7?) 
6. Multicores, Multiprocessors, and Clusters (1/14)
7. Data-Level Parallelism: SIMD, Vector, and GPU (1/14)
8. Warehouse-Scale Computers (1/21)

## Trends in Computer Architecture Design
### Techniques to Avoid Pipeline-Stalls
- Maintain the dependence among the instructions but avoid a hazard, and eliminate a dependence by transforming the code to increase instruction-level parallelism, and then
- Fill stall-slots in the pipeline with independent instructions by their reordering 
    - Exploit instruction-Level Parallelism (ILP), parallelism among instructions

Two approaches to exploiting ILP
- Dynamic reordering of instruction execution by hardware
    - Pentium III&4, Athlon, MIPSR10000/12000, UltraSPARC III, PowerPC G3&G4, Alpha 21264
- Static reordering of instruction execution by compiler
    - IA-64 (Itanium 1&2)

## Importance of Data Dependences and Hazards
- Determining whether an instruction is dependent on another instruction is critical to ...
    - Determining how much parallelism exists in a program and
    - Determining how that parallelism can be exploited.

😀 If two instructions are parallel, they can execute simultaneously in a pipeline without causing any stalls

🙁 If two instructions are dependent, they are not parallel and must be executed in order, though they may often be partially overlapped in pipelining.

## Data Dependences
- **Data depences**: An instruction *j* is *data dependent*on instruction *i* if either of the following holds
    - instruction i produces a result that may be used by instruction j, or 
    - instruction j is data dependent on instruction k, and instruction k is data dependent on instruction i.


### Name Dependences
A name dependence occurs when 
- **Two instructions use the same register or memory location**, called *name*, 
- But **there is no flow of data** between the instructions associated with that name.
- An **antidependence** between instructions i and j occurs 
    - When j writes a register or memory location that i reads.
- An **output dependence** occurs 
    - When instructions i and j write the same register or memory location.

**Since a name dependence is not a true dependence, it can be solved if the number of registers is enough**

### Data Hazards
- A hazard is created whenever 
    - There is a dependence between instructions, and 
    - They are close enough that the overlap caused by pipelining, or other reordering of instructions, would change the order of access to the operand involved in the dependence.
- The goal of software and hardware techniques is *to exploit parallelism by preserving program order only where it affects the outcome of the program*.

### Types of Data Hazards
- **RAW (read after write)**
    - j tries to read a source before iwrites it, so j incorrectly gets the old value in the case of  i occurring before j in program order
    - **True dependence**
    - RAW \
        LD **F0**, 0(R2) \
        ADD F4,**F0**,F2
- **WAW (write after write)**
    - i tries to write an operand before it is written by i.
    - **Output dependence**
    - WAW \
        ADD **F4**,F0,F2 \
        ・・・ \
        DIV **F4**, F1,F3
- **WAR (write after read)**
    - j tries to write a destination before it is read by i, so i incorrectly gets the new value.
    - **Antidependence**
    - WAR \
        ADD F4, **F0**, F2 \
        LD **F0**, 0(R2)


## Exploiting Instruction-Level Parallelism with Hardware Approaches
### Overcoming Data Hazards with Dynamic Scheduling
- Dynamic scheduling
    - Hardware rearranges the instruction execution to reduce the stalls while maintaining data flow and exception behavior.
- Advantages
    - It enables handling some cases when dependences are unknown at compile time (e.g., memory references)
    - It simplifies the compiler
    - It allows code that was compiled with one pipeline in mind to run efficiently on a different pipeline.

**🙁 The advantages of dynamic scheduling are gained at a cost of significant increase in hardware complexity.**

### Dynamic Scheduling: The Idea
- Simple pipelining techniques use in-order instruction issue and execution.
    - Instructions are issued in program order, and if an instruction is stalled in the pipeline, no later instructions can proceed.

![Dynamic_Scheduling_The_Idea.png](image/Dynamic_Scheduling_The_Idea.png)

### Some Concerns about Dynamic Scheduling
- *WAR and WAW hazards* \
Example: \
    DIV F0,F2,F4 \
    ADD F6,F0,F8 RAW \
    SUB F8,F10,F14 WAR \
    MUL F6,F10,F8 WAW \
If the pipeline executes SUB before ADD, it will violate the antidependence (**WAR**). \
Likewise, to avoid violating output dependences, **WAW** hazards must be handled.

- *Precise exception handling*
    - Dynamic scheduling with out-of-order completion must preserve exception behavior in the sense that **exactly** those exceptions that would arise if the program were executed in strict program order **actually** do arise.

Dynamically scheduled processors preserve exception behavior by ensuring that no instruction can generate an exception until the processor knows that the instruction raising the exception will be executed.

### New Pipeline Staging for Out-Of-Order Execution
To allow out-of-order execution, the ID pipe stage is split into two stages
- *Issue*: Decode instructions, check for structural hazards
- *Read operands*: Wait until no data hazards are observed, and the read operands are ready for execution.
- An instruction fetch stage precedes the issue stage and may fetch either into an instruction register or into a queue of pending instructions
- Instructions are then issued from the register or queue.
- The EX stage follows the read operands stage, just as in the five-stage pipeline

To take advantage of dynamic scheduling, 
- Pipelines allows multiple instructions to be in execution at the same time, and
- Have multiple functional units, pipelined functional units or both.

### Basic Dynamic Scheduling
In a dynamically scheduled pipeline, 
- All instructions pass through the issue stage in order (*in-order issue*), however, 
- They can be *stalled or bypass* each other in second stage (read operand) and 
- Thus enter execution *out of order*.
- *Scoreboarding: The basic idea*
    - When the next instruction to execute is stalled, other instructions can be issued and executed if they do not depend on any active or stalled instruction.

DIV **F0**,F2,F4 \
ADD ***F6***,**F0**,*F8* **RAW** \
SUB *F8*,F10,F14 *WAR* \
MUL ***F6***,F10,F8 ***WAW*** 

### Scoreboarding (First introduced in CDC6600)
- All hazard detection and resolution are centralized in the scoreboard to control instruction execution.
    - Every instruction goes through the scoreboard, where a record of the data dependences is constructed.
    - The scoreboard determines when the instruction can read its operands and begin execution.
    - If the scoreboard decides the instruction cannot execute immediately, it monitors every change in the hardware and decides when the instruction can be executed.
    - The scoreboard also controls when an instruction can write its result into the destination register.

![Scoreboarding_CDC6600.png](image/Scoreboarding_CDC6600.png)

### The basic four steps for scoreboarding
- Issue
    - If **a functional unit for the instruction is free** and **no other active instruction has the same destination register**, the scoreboard issues the instruction to the functional unit and updates it internal data structure
    - *Structural and WAW hazard handling*
- Read operands
    - The scoreboard **monitors the availability of the source operands**.
    - When the source operands are available, the scoreboard tells the functional unit **to proceed to read the operands from the register and begin execution**.
    - *Dynamic RAW hazard handling*
- Execution
    - The functional unit begins execution upon receiving operands
    - When the result is ready, it notifies the scoreboard that it has completed execution
- Write result
    - Once the scoreboard is aware that the functional unit has completed execution, **the scoreboard checks for WAR hazards and stall the completing instruction**, if necessary.
    - If **this WAR hazard does not exist**, or when it clears, the scoreboard tells the functional unit to store its result to the destination register.
    - *WAR hazard handling*

### Data Structures for Scoreboarding
- Instruction status
    - Indicates which of the four steps the instruction is in.
- Functional unit status
    - Indicates the state of the functional unit (FU).
    - There are nine fields for each functional unit
        - Busy: indicates whether the unit is busy or not
        - Op: operation to perform in the unit
        - Fi: destination register
        - Fj, Fk: source registers
        - Qj, Qk: Functional units producing source registers Fj,Fk
        - Rj,Rk: Flags indicating when Fj, Fkare ready and not yet read. Set to No after operands are read
- Register result status
    - Indicates which functional unit will write each register, if an active instruction has the register as its destination.
    - This field is set to blank whenever there are no pending instructions that will write that register.

Exemple slide 18 and 19

### Required Checks and Bookkeeping Actions
| Instruction Status   | Wait until                                      | Bookkeeping                                                                                     |
|----------------------|-------------------------------------------------|------------------------------------------------------------------------------------------------|
| Issue                | Not Busy[FU] and Not Result[D]                 | Busy[FU] ← yes; Op[FU] ← op; Fi[FU] ← D;<br>Fj[FU] ← S1; Fk[FU] ← S2;<br>Qj ← Result[S1]; Qk ← Result[S2];<br>Rj ← not Qj; Rk ← not Qk; Result[D] ← FU |
| Read operands        | Rj and Rk                                       | Rj ← No; Rk ← No; Qj ← 0; Qk ← 0                                                               |
| Execution Complete   | Functional unit done                            |                                                                                                 |
| Write result         | ∀f((Fj[f]≠Fi[FU] or Rj[f]=No) & (Fk[f]≠Fi[FU] or Rk[f]=No)) | ∀f(if Qj[f]=FU then Rj[f]←Yes);<br>∀f(if Qk[f]=FU then Rk[f]←Yes);<br>Result[Fi[FU]] ← 0; Busy[FU] ← No;       |

### Scoreboarding
👍 *1.7x Performance improvement for a Fortran program on CDC6600*
👎 **Main Cost: Large number of buses**

Factors Limiting the Scoreboard Performance
- The amount of parallelism available among the instruction
    - This determines whether independent instructions can be found to execute.

This is due to...
1. The number of scoreboard entries **limited**!
    - This determines how far ahead the pipeline can look for independent instructions.
    - The set of instructions examined as candidates for potential execution is called the *window*.
2. The number and types of functional units **limited**!
    - This determines the importance of structural hazards, which can increase when dynamic scheduling is used
3. The presence of antidependences and output dependences **unavoidable**!
    - These lead to WAR and WAW stalls

### Tomasulo’s Approach: Solve the Problems of Scoreboarding!
Invented by Robert Tomasulo for IBM 360/91 FP units
- Tracks when operands for instructions are available, to minimize RAW hazards
    - Reservation stations of functional units buffers the operands of instructions waiting to issue
- Introduces register renaming, to minimize WAW and WAR hazards
    - Register renaming eliminates WAR and WAW hazards by renaming all destination registers, including those with a pending read or write for an earlier instruction.
- Hazard detection and execution control are distributed

### Dynamic Scheduling with Register Renaming
![Dynamic_Scheduling_with_Register_Renaming.png](image/Dynamic_Scheduling_with_Register_Renaming.png)


### Reservation Stations for Register Renaming
- As instructions are issued, the register specifiers for pending operands are renamed to the names of the reservation stations
- A reservation station fetches and buffers an operand as soon as it is available, eliminating the need to get the operand from a register.
- Pending instructions designate the reservation station that will provide their input.

- Since there can be more reservation stations than real registers, the technique can even eliminate hazards arising from name dependences.

![Reservation_Stations_for_Register_Renaming.png](image/Reservation_Stations_for_Register_Renaming.png)

