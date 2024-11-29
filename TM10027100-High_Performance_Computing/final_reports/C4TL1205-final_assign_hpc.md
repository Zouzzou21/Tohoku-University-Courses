## C4TL1205 - LANDY Lucas (COLABS Student) - [lucas.landy.t3@dc.tohoku.ac.jp](mailto:lucas.landy.t3@dc.tohoku.ac.jp)

---

# Table of Contents


---

# 1. program: [```mpi_round_trip.c```](code/mpi_round_trip.c)

To compile this program using mpi we need to use the compiler ```mpicc```
To simplify the build and the execution of the program i made a [```makefile```](code/makefile).
The ```all-mpi-round-trip``` make command is use to build and send to the queue the program with the [```run_mpi_round_trip.sh```](code/run_mpi_round_trip.c)
The ```build-mpi-round-trip``` make command is use to build the ```mpi_round_trip.c``` code to the ```mpi_round_trip``` executable file.
The ```run-mpi-round-trip``` make command is use to put in queue the ```run_mpi_round_trip.sh``` script
```makefile
all-mpi-round-trip: build-mpi-round-trip run-mpi-round-trip

build-mpi-round-trip:
	mpicc mpi_round_trip.c -o mpi_round_trip

run-mpi-round-trip:
	qsub ./run_mpi_round_trip.sh
	qstat

clean-mpi-round-trip:
	-@rm -f mpi_round_trip
```

Below is the ```run_mpi_round_trip.sh``` script who execute the ```mpi_round_trip``` file using 2 node.
```sh run_mpi_round_trip.sh
#!/bin/sh -
#PBS -q lx_edu
#PBS -l elapstim_req=0:10:00

cd $PBS_O_WORKDIR

time mpirun -np 2 ./mpi_round_trip
```


To see the relation between data size and communication time i made the graph bellow:
![Relation_between_data_size_and_communication_time](image/chart.png)

In the output of the execution can be found in the file [```run_mpi_round_trip.sh.o639599```](outputs/run_mpi_round_trip.sh.o639599). We can see the calculat latency and the bandwidth.
```sh output
Data size: 1 bytes, Time: 0.000010 seconds, Latency: 4.82 microseconds, Bandwidth: 0.21 MB/s
Data size: 2 bytes, Time: 0.000328 seconds, Latency: 163.75 microseconds, Bandwidth: 0.01 MB/s
Data size: 4 bytes, Time: 0.000001 seconds, Latency: 0.27 microseconds, Bandwidth: 14.81 MB/s
Data size: 8 bytes, Time: 0.000004 seconds, Latency: 1.81 microseconds, Bandwidth: 4.43 MB/s
Data size: 16 bytes, Time: 0.000000 seconds, Latency: 0.18 microseconds, Bandwidth: 88.89 MB/s
Data size: 32 bytes, Time: 0.000001 seconds, Latency: 0.34 microseconds, Bandwidth: 92.75 MB/s
Data size: 64 bytes, Time: 0.000000 seconds, Latency: 0.16 microseconds, Bandwidth: 400.00 MB/s
Data size: 128 bytes, Time: 0.000006 seconds, Latency: 3.00 microseconds, Bandwidth: 42.74 MB/s
Data size: 256 bytes, Time: 0.000003 seconds, Latency: 1.36 microseconds, Bandwidth: 188.86 MB/s
Data size: 512 bytes, Time: 0.000003 seconds, Latency: 1.44 microseconds, Bandwidth: 356.79 MB/s
Data size: 1024 bytes, Time: 0.000003 seconds, Latency: 1.28 microseconds, Bandwidth: 803.14 MB/s
Data size: 2048 bytes, Time: 0.000009 seconds, Latency: 4.32 microseconds, Bandwidth: 474.62 MB/s
Data size: 4096 bytes, Time: 0.000008 seconds, Latency: 4.09 microseconds, Bandwidth: 1000.24 MB/s
Data size: 8192 bytes, Time: 0.000008 seconds, Latency: 3.85 microseconds, Bandwidth: 2127.79 MB/s
Data size: 16384 bytes, Time: 0.000016 seconds, Latency: 7.97 microseconds, Bandwidth: 2056.87 MB/s
Data size: 32768 bytes, Time: 0.000027 seconds, Latency: 13.32 microseconds, Bandwidth: 2460.98 MB/s
Data size: 65536 bytes, Time: 0.000060 seconds, Latency: 30.20 microseconds, Bandwidth: 2170.03 MB/s
Data size: 131072 bytes, Time: 0.000088 seconds, Latency: 44.24 microseconds, Bandwidth: 2963.05 MB/s
Data size: 262144 bytes, Time: 0.001885 seconds, Latency: 942.26 microseconds, Bandwidth: 278.21 MB/s
Data size: 524288 bytes, Time: 0.002195 seconds, Latency: 1097.30 microseconds, Bandwidth: 477.80 MB/s
Data size: 1048576 bytes, Time: 0.003109 seconds, Latency: 1554.63 microseconds, Bandwidth: 674.49 MB/s
```

The file [```run_mpi_round_trip.sh.e639599```](outputs/run_mpi_round_trip.sh.e639599) dispay the output of the ```time``` command.


# 2. [```n-body.c```](code/n-body.c)
## 2-I. program: [```n-body.c```](code/n-body.c)
```n-body.c``` \
[run_n-body.sh.e639605](outputs/run_n-body.sh.e639605) \
[run_n-body.sh.o639605](outputs/run_n-body.sh.o639605)

```makefile
all-n-body: build-n-body run-n-body

build-n-body:
	gcc -fopenmp n-body.c -o n-body -lm

run-n-body:
	qsub ./run_n-body.sh
	qstat

clean-n-body:
	-@rm -f n-body
	-@rm -f n-body-serial

n-body-serial:
	gcc n-body.c -o n-body-serial -lm
	qsub ./run_n-body-serial.sh
```

```sh run_n-body.sh
#!/bin/sh -
#PBS -q lx_edu
#PBS -l elapstim_req=0:10:00

cd $PBS_O_WORKDIR

for threads in 1 2 4 8 16 32; do
    echo "OMP_NUM_THREADS=${threads}"
    export OMP_NUM_THREADS=${threads}
    time ./n-body
done
```

```n-body-serial.c``` \
[run_n-body-serial.sh.e639612](outputs/run_n-body-serial.sh.e639612) \
[run_n-body-serial.sh.o639612](outputs/run_n-body-serial.sh.o639612)

```sh run_n-body-serial.sh
#!/bin/sh -
#PBS -q lx_edu
#PBS -l elapstim_req=0:10:00

# Ensure we're in the right directory
cd "${PBS_O_WORKDIR}"

time ./n-body-serial
```

Speedup $S = \frac{T_{serial}}{T_{parrallel}}$ \
Efficiency $E = \frac{S}{P}$ \
$P$ is the number of threads 


## 2-II. program: [```n-body-mpi.c```](code/n-body-mpi.c)
```n-body-mpi.c``` \
[run_n-body-mpi.sh.e639586](outputs/run_n-body-mpi.sh.e639586) \
[run_n-body-mpi.sh.o639586](outputs/run_n-body-mpi.sh.o639586)

```makefile
all-n-body-mpi: build-n-body-mpi run-n-body-mpi

build-n-body-mpi:
	mpicc n-body-mpi.c -o n-body-mpi -lm

run-n-body-mpi:
	qsub ./run_n-body-mpi.sh
	qstat

clean-n-body-mpi:
	-@rm -f n-body-mpi
```

```sh run_n-body-mpi.sh
#!/bin/sh -
#PBS -q lx_edu
#PBS -l elapstim_req=0:10:00

cd $PBS_O_WORKDIR

for processes in 1 2 4 8 16 32; do
    echo "mpirun -np ${processes} ./n-body-mpi"
    time mpirun -np ${processes} ./n-body-mpi
done
```

Speedup $S = \frac{T_{serial}}{T_{parrallel}}$ \
Efficiency $E = \frac{S}{P}$ \
$P$ is the number of threads 


Is used to clean all executable file
```makefile
clean-all: clean-mpi-round-trip clean-n-body clean-n-body-mpi
	-@rm -f run_mpi_round_trip.sh.*
	-@rm -f run_n-body.sh.*
	-@rm -f run_n-body-serial.sh.*
	-@rm -f run_n-body-mpi.sh.*
```


# 3. Description of my research theme
### Graduate Research Theme
My current research focuses on developing and optimizing Convolutional Neural Networks (CNNs) for the detection of brain tumors in MRI images. The goal is to achieve high accuracy and efficiency in identifying tumor regions, addressing challenges such as limited labeled datasets, variability in tumor shapes and sizes, and the computational intensity required for processing high-resolution medical images.

The study involves training CNN architectures, such as U-Net and ResNet, on annotated MRI datasets. This research aims to contribute to early tumor detection, aiding clinicians in diagnostic processes, and reducing the reliance on subjective interpretation. Further, I am exploring advanced techniques like transfer learning to enhance model performance on small datasets and data augmentation to create diverse training samples.

### Supercomputing Contributions to the Research
If provided access to a next-generation supercomputer with significantly higher performance, the following advancements could be realized in my research:

1. Training on Larger and More Complex Models:
    - Current constraints in GPU memory limit the size of the models and batch sizes that can be trained simultaneously. A supercomputer with large-scale parallelism and memory resources would allow the exploration of deeper CNN architectures, leading to potentially higher detection accuracy.

2. Processing Massive MRI Datasets:
    - Supercomputers could handle the preprocessing and real-time analysis of large MRI datasets from multiple hospitals, enabling a more generalized model that works across diverse populations.

3. Hyperparameter Optimization:
    - The computational demands of techniques like grid search or Bayesian optimization for tuning hyperparameters are immense. With a supercomputer, parallel execution of these techniques would drastically reduce the time required for optimization.

4. Enhanced Resolution Imaging:
    - Higher resolution MRI images contain finer details but demand substantial computational resources. A supercomputer would enable models to utilize such high-resolution images, potentially improving tumor detection accuracy.

5. Incorporating Multi-Modality Data:
    - Integrating other imaging modalities, such as PET or CT scans, alongside MRI, can improve model performance but significantly increases computational needs. A supercomputer would support the simultaneous processing of multi-modality data.

6. Simulation and Virtual Testing:
    - Using advanced simulations to test CNN robustness across various edge cases could become feasible, helping ensure reliability in real-world clinical applications.

7. Federated Learning at Scale:
    - Supercomputing capabilities could facilitate federated learning across multiple medical institutions, ensuring data privacy while improving the generalization of the model.

### Conclusion
The availability of a supercomputer would significantly accelerate the progress of my research by addressing current computational limitations, enabling larger-scale studies, and fostering the development of more robust and accurate tumor detection models. This, in turn, could pave the way for early and precise diagnostics, ultimately improving patient outcomes.

# 4. How was this class?

### Strengths of the Class:
1. **Comprehensive Content**: The course covers a wide range of topics in high-performance computing, including parallel computing paradigms (MPI and OpenMP), parallel algorithm design, job scheduling, and performance analysis techniques like Amdahl's and Gustafson-Barsis's laws. This breadth ensures a robust foundation in HPC.

2. **Practical Orientation**: The inclusion of hands-on exercises such as writing MPI programs, optimizing performance, and using tools like gprof for profiling is excellent for building real-world skills.

3. **Structured Learning**: The class schedule is well-organized with distinct focus areas per session, progressively introducing more complex concepts.

4. **Focus on Emerging Trends**: Topics like GPU programming, hybrid systems, and data-parallel processing reflect current trends in HPC, making the course relevant for modern applications.

5. **Instructor Expertise**: Dr. Hiroyuki Takizawa’s strong background and research focus on HPC lend credibility and depth to the course content.

### Opportunities for Improvement:
1. **Level of Detail in Lectures**: Some areas, such as Amdahl's Law and Roofline model, could include more real-world case studies or examples to clarify the concepts further.

2. **Resource Accessibility**: While the class includes practical assignments, ensuring students have consistent access to necessary resources (e.g., supercomputer access) is vital for effective learning.

3. **Greater Focus on Scalability Challenges**: Although scalability issues are discussed, more emphasis on practical solutions and real-life constraints of scaling parallel programs could enhance understanding.

4. **Hands-On Guidance**: For beginners, additional support with debugging or tackling errors in MPI/OpenMP programming could make the learning curve less steep.

### Overall Impression:
This HPC class is an excellent mix of theory and practice, providing a solid foundation in modern parallel computing techniques and their applications. It caters well to students aiming to work in scientific computing, machine learning, or any domain requiring computational intensity. Slight improvements in accessibility and examples could make the class even better.
