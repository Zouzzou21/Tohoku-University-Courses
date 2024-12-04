# Computer Architecture Design (CAD) - Course Summary #1 ([chapter1-6.pdf]-(chapter1-6.pdf))

---

## Instructor
- Hiroaki Kobayashi
    - Professor, Graduate School of Information Sciences 
    - Office:Room523, 5-th floor, Mechanical Engineering Building No.2
    - E-mail: koba@tohoku.ac.jp
- Masayuki Sato
    - Associate Professor, Graduate School of Information Sciences
    - Office: Room 525 in the same building
    - E-mail: masa@tohoku.ac.jp

---

## Table of Contents


---

## Introduction
What is a computer?
- A programmable electronic device that can store, retrieve and process data.
- Basic functions:
    - Input
    - Output
    - Memory
    - Calculation
    - Control (programmable)
- Computer $\neq$ Calculator：does calculations, but is not programmable

![Basic_Structure_of_Computer-Von-Neumann_Model.png](image/Basic_Structure_of_Computer-Von-Neumann_Model.png)

(Yellow arrow) Control flow = is use for control the calculator flow
(Red arrow) Data flow = is use to transfert the data to calculate

Moore's law = Cqlculations per second per constant dollar by year increase du to the number of transistor in a CPU increase due to the process of miniaturisation of them.

The Law of Accelerating Returns
```mermaid
graph LR
    A[Technology Advances] --> B[More New Users Adopt]
    B --> C[Finances Innovation]
    C --> A
```

Different type of architecture of a CPU. x86 was invented by Intel and it's was amazing!

MIPS (Million Instruction Pers Seconds) = It's one way to calculate the performance of a computer

![Incredible-progress-in-computer-technology-over-last-60-years.png](image/Incredible-progress-in-computer-technology-over-last-60-years.png)

---

## Class of Computers
Changes in computer systems
- Large mainframes in 1960s
- Minicomputer and Supercomputers in 1970s
- Desktop computers in 1980
- Handheld computing devices (PDA, Video games) in 1990s
- Cell phones in 2000

Class of Parallelism and Parallel Architectures
- Two parallelism in applications
    - Data-Level Parallelism (DLP)
    - Parallelism exploited in many data items that can be operated on at the same time
- Task-Level Parallelism (TLP)
    - Parallelism exploited in tasks of work that can operate independently and largely in parallel
- Pipelining and Superscalar use Instruction-Level Parallelism
- SIMD/Vector Processing/GPU use data level parallelism with a single instruction for a collection of data in parallel.
- Multicore processors/ parallel processors use Thread-Level. Parallelism created by using data-level parallelism or task-level parallelism
- Request-Level Parallelism exploits parallelism among largely decoupled tasks specified by the programmer or the operating system


|                     | **Data Streams**           |                      |
|---------------------|----------------------------|----------------------|
| **Instruction Streams** | **Single**               | **Multiple**         |
| **Single**          | **SISD:** Intel Pentium 4  | **SIMD:** SSE/AVX of Core i7 |
| **Multiple**        | **MISD:** No examples today | **MIMD:** Multicore Core i7 |


SPMD: Single Program Multiple Data
- Parallel program on a MIMD computer
- Conditional code for different processors

![i7-Chip-Microarchitecture.png](image/i7-Chip-Microarchitecture.png)

![i7-Chip-Microarchitecture(2).png](image/i7-Chip-Microarchitecture(2).png)

---

## Defining Computer Architecture
ISA (Instruction Set Architecture) design:
- The actual programmer-visible instruction set
- The boundary between the software and hardware

![Computer-System-Layers.png](image/Computer-System-Layers.png)

The target of this lecture is **Computer Architecture** and **Machine Oraganization**.

### Seven dimension of an ISA:
1. **Class of ISA**
    - General-purpose register architectures
        - Register-memory ISAs of 80x86
        - Load-store ISAs of MIPS
2. **Memory addressing**
    - Byte-addressing
    - Aligned (MIPS)
    - Not aligned (80x86)
3. **Addressing modes**
    - register, immediate, displacement, register indirect, based with scaled index
4. **Types and sizes of operands**
    - 8-bit (char), 16-bit (unicode char, half-word), 32-bit (integer or word), 64-bit (double word or long int), and IEEE 745 fp in 32-bit(single)&64-bit(dobule), 80-bit fp in 80x86)
5. **Operations**
    - Data transfer, arithmetic logical, control, and floating point
    - MIPS is simple but 80x86 has a much richer and larger set
6. **Control flow instructions**
    - Cond branch, uncond jump, procedure call and return
    - PC-relative addressing
    - MIPS cond branches test the contents of registers
    - 80x86 branches test condition code bits set as side effects of operations
7. **Encoding an ISA (bits sequences)**
    - Fixed length (**32-bit fix in MIPS**) and variable length (1 to 18 bytes in 80x86)
    - Variable length inst. can take less space, but needs complicated decoding
    - Number of registers and number of addressing modes have a significant impact on size of instructions

MPIS ISA instructions:
- 3 Basics intrusction formats
    - **R** : 
        | 31-26 | 25-21 | 20-16 | 15-11 | 10-6  | 5-0   |
        |-------|-------|-------|-------|-------|-------|
        | opcode|   rs  |   rt  |   rd  | shamt | funct |
    - **I** : 
        | 31-26 | 25-21 | 20-16 | 15-0        |
        |-------|-------|-------|-------------|
        | opcode|   rs  |   rt  | immediate   |
    - **J** : 
        | 31-26 | 25-0                |
        |-------|---------------------|
        | opcode| address             |
- Floating-point instruction formats:
    - **FR** :
        | 31-26 | 25-21 | 20-16 | 15-11 | 10-6  | 5-0   |
        |-------|-------|-------|-------|-------|-------|
        | opcode|  fmt  |   ft  |   fs  |   fd  | funct |
    - **FI** :
        | 31-26 | 25-21 | 20-16 | 15-0        |
        |-------|-------|-------|-------------|
        | opcode|  fmt  |   ft  | immediate   |

**Organization**: the high-level aspects of a computer’s design \
**Hardware**: the specifics of a computer, including the detailed logic design and the packaging technology

### ***Computer architecture = ISA, Organization, and Hardware***

Microarchitecture Design= Data Path & Control Units Design
- Pipelining
- Instruction Level / Parallel Processing
- On-chip cache and TLB
- Speculation and Branch Prediction

Intel’s TICK-TOCK Strategy, and Then Process-Architecture-Optimization Strategy

Requirements in Designing a New Computer
- Design a computer to meet functional requirements as well as price, power, performance, and availability goals.
- Market (applications), and technology decide the requirements.
- Although technology improves continuously, the impact of these improvements can be in discrete leaps.

Tracking Technology Performance Trends
- Drill down into 4 technologies:
    - Disks, 
    - Memory, 
    - Network, 
    - Processors
- Compare ~1980 Archaic (Nostalgic) vs. ~2010 Modern (Newfangled)
    - Performance Milestones in each technology
- Compare for Bandwidth vs. Latency improvements in performance over time
- **Bandwidth**,**Throughput**: number of events per unit time
    - E.g., MIPS (million instructions/second), M bits / second over network, M bytes / second from disk
- **Latency**: elapsed time for a single event
    - E.g., one-way network delay in microseconds, average disk access time in milliseconds

