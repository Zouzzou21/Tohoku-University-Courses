# Computer Architecture Design (CAD) - Course Summary #4 ([chapter4.pdf]-(chapter4.pdf))

---

## Table of Contents
- [Introduction](#introduction)
- [Cache Performance](#cache-performance)
- [Eleven Cache Optimizations](#eleven-cache-optimizations)
- [Virtual Memory](#virtual-memory)
- [Protection and Examples of Virtual Memory](#protection-and-examples-of-virtual-memory)

---

## Introduction
### Memory Wall Problem and The Principle of Locality
![Memory_Wall.png](image/Memory_Wall.png)
- The Principle of Locality:
    - Programs access a relatively small portion of the address space at any instant of time.
- Two Different Types of Locality:
    - Temporal Locality (Locality in Time): If an item is referenced, it will tend to be referenced again soon (e.g., loops, reuse)
    - Spatial Locality (Locality in Space): If an item is referenced, items whose addresses are close by tend to be referenced soon (e.g., straight-line code, array access)

### Levels of the Memory Hierarchy
![Levels_of_the_Memory_Hierarchy.png](image/Levels_of_the_Memory_Hierarchy.png)
Exemple of memory hierarchies for server and PMD at slide 5.

### Terminology
- **Cache** is originally the name given to highest or first level of the memory hierarchy for faster data accesses, but now has the meaning of buffering to reuse commonly occurring items.
    - File cache, name caches... 
- **Cache hit** means the situation where a requested data item can be found in the cache
    - **Cache miss** occurs when the processor does not find a data item in the cache
- **A cache block or line** is a fixed-size collection of data containing the requested word,  which is retrieved from the main memory and placed into the cache.
    - Because of the spatial locality, there is a high probability that the other data in the block will be needed soon.
- **Latency** is the time to retrieve the first word of the block, and
- **Bandwidth** is the total amount of work done in a given time.
- **The time required for the cache miss** depends on both **latency** and 
**bandwidth** of the memory.
    - **Latency** determines the time to retrieve the first word of the block, and 
    - **Bandwidth** determines the time to retrieve the rest of this block.
- **A cache miss is handled by hardware**.
    - In-order processors are stalled until the data are available, while 
    - Out-of-order processors switch their execution to other instructions during the miss
- **Virtual memory** provides a program with a large logical memory space beyond the physical one by using the fact that not all objects referenced by a program need to reside in main memory.
    - Some objects may reside on disk.
- The address space is broken into fixed-sized blocks, called **pages**.
- **A page fault** occurs when the processor references an item within a page that is not present in the cache or main memory, and 
    - The entire memory is moved from the disk to main memory.
    - Page faults are handled by software (OS)
    - The processor usually switches to some other task while the disk access occurs, in order to avoid processor stall since they take so long.

---

## Cache Performance
### Definition
- **We must account for memory stall cycles**, the number of cycles during which the processor is stalled waiting for a memory access, in CPU execution time
    - $CPU execution time = (CPU Clock cycles + Memory Stall Cycles) \times (Clock cycle time)$
        - **CPU Clock cycles include time to handle a cache hit**, and the processor is stalled during a cache miss.
    - $Memory stall cycles= (Number of misses) \times (Miss penalty)$ \
        $= IC \times（Misses)/(Instruction) \times(Miss penalty)$ \
        $= IC \times(Memory accesses)/(Instruction) \times（Miss rate) \times(Miss penalty)$ \
        $= IC \times (Memory accesses per Instruction) \times（Miss rate) \times(Miss penalty)$ \
        - **The miss penalty** is the cost per miss
        - **Miss rate** is the fraction of cache accesses that result in a miss.
            - \# of accesses that miss divided by # of accesses
- As **miss rates and miss penalties are often different for reads and writes**, memory stall clock cycles could then be defined as follows:
    - $Memory stall cycles=IC \times Reads per inst. \times Read miss rate \times Read miss penalty + IC \times Writes per Inst. \times Write miss rate \times Write miss penalty$

#### Exemple
Assume we have a computer where the the clocks per instruction (CPI) is 1.0 when all memory accesses hit in the cache.   The only data accesses are loads and stores, and these total 50% of the instructions.   If the miss penalty is 25 clock cycles and the miss rate is 2%, how much faster would the computer be if all instructions were cache hits?

### Four memory hierarchy questions
- **Q1: Where can a block be placed in the upper level?**
    - Block placement
    - Direct mapped cache
        - *Each block has only one place* it can appear in the cache.
        - Mapping is usually **(Block address) MOD (# of Blocks in cache)**
    - Full associative cache
        - *A block can be placed anywhere* in the cache
    - Set associative cache
        - *A block can be placed in a restricted set of places* in the cache.
        - A set is a group of blocks in the cache
        - A block is first mapped onto a set, and then the block can be placed anywhere within that set.
        - The set is usually chosen by bit selection:
            - **(Block address) MOD (# of sets in cache)**
        - If *there are n blocks in a set*, the placement is called *n-way set associative*.
            - **N-way set associative cache**

![Q1-Where_can_a_Block_Be_Placed_in_a_Cache.png](image/Q1-Where_can_a_Block_Be_Placed_in_a_Cache.png)

- **Q2: How is a block found if it is in the upper level?**
    - Block identification
    - *The three portions of an address in a set-associative or direct-mapped cache*.
        - **The block offset field** selects the desired data from the block
        - **The index field** selects the sets
        - **The tag field** is compared against it for a hit
        - Increasing associativity increases the number of blocks per set
            - Decreasing the size of the index and increasing the size of the tag
            - Tag-index boundary moves to the right with increasing associativity.

![Q2-How_Is_a_Block_Found_If_It_Is_in_the_Cache.png](image/Q2-How_Is_a_Block_Found_If_It_Is_in_the_Cache.png) \
Organization of the 2-way set-associative data cache in the Opteron


- **Q3: Which block should be replaced on a miss?**
    - Block replacement
    - Three Primary Strategies for Replacement
    1. *Random*  (There is little difference between LRU and random for the largest-size cache)
        - To spread allocation uniformly, candidate blocks are randomly selected.
    2. *Least-recently used (LRU)* (outperforms others for smaller caches)
        - To reduce the chance of throwing out information that will be needed soon, accesses to blocks are recorded.
        - **Relying on the past to predict the future**, the block replaced is the one that has been unused for the longest time.
            - If recently used blocks are likely to be used again (locality of reference), then a good candidate for disposal is the least-recently used block.
        - Effective, **but expensive**
    3. *First in, First out (FIFO)* (generally outperforms random for smaller caches)
        - Because LRU can be complicated to calculate, this approximates LRU by determining the oldest block rather than the LRU.
        - Simple to build in hardware


- **Q4: What happens on a write?**
    - Write strategy
    - As a write change the state of the cache, there are two basic policies for the cache design.
    - *Write through*
        - The information is written to both the block in the cache and to the block in the lower-level memory.
        - The cache is always **clean**.
        - Easier to implement, but **it takes a longer time to complete** due to a longer latency to access the lower-level memory.
        - Read misses never result in writes to the lower level.
            - The next lower level has the most current copy of the data, which simplifies **data coherency**, especially important for multiprocessors.
            - Multi-level cache make write through more viable for the upper-level caches
    - *Write back*
        - The information is written only to the block in the cache.  The modified cache block, **dirty block**, is written to main memory only when it is replaced.
        - **More complicated implementation**: Each block has a dirty bit that indicates whether the block is dirty or clean.
        - **Writes occur at the speed of the cache memory**, and
        - Multiple writes within a block require only one write to the lower-level memory.
            - **Less memory bandwidth, lower power consumption**
            - **Attractive features for multiprocessors and embedded applications**

### Two options on a write miss
- Write allocate
    - The block is allocated on a write miss, followed by the write hit actions. Write misses act like read misses
        - Even blocks that are only written will still be in the cache.
- No-write allocate
    - Write misses do not affect the cache.   Instead, the block is modified only in the lower-level memory.
        - Blocks stay out of the cache in no-write allocate until the program tries to read the block.

Example:
- Assume a fully associative write-back cache with many cache entries that starts empty. Below is a sequence of five memory options (the address is in square brackets):
        - Write Mem[100]; Write Mem[100]; Read Mem[200]; 
        - Write Mem[200]; Write Mem[100].
    - What are the number of hits and misses when using no-write allocate versus write allocate.

![An_Example-The_Opteron_Data_Cache.png](image/An_Example-The_Opteron_Data_Cache.png)



---

## Eleven Cache Optimizations


---

## Virtual Memory


---

## Protection and Examples of Virtual Memory
