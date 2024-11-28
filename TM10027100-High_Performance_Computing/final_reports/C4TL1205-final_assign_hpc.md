## C4TL1205 - LANDY Lucas (COLABS Student) - [lucas.landy.t3@dc.tohoku.ac.jp](mailto:lucas.landy.t3@dc.tohoku.ac.jp)

---

# Table of Contents


---

# 1. program: [```mpi_round_trip.c```](code/mpi_round_trip.c)
## Purpose:

```mpi_round_trip.c``` \
[run_mpi_round_trip.sh.e639599](outputs/run_mpi_round_trip.sh.e639599) \
[run_mpi_round_trip.sh.o639599](outputs/run_mpi_round_trip.sh.o639599)

# 2-I. program: [```n-body.c```](code/n-body.c)
## Purpose:
```n-body.c``` \
[run_n-body.sh.e639605](outputs/run_n-body.sh.e639605) \
[run_n-body.sh.o639605](outputs/run_n-body.sh.o639605)

```n-body-serial.c``` \
[run_n-body-serial.sh.e639612](outputs/run_n-body-serial.sh.e639612) \
[run_n-body-serial.sh.o639612](outputs/run_n-body-serial.sh.o639612)

Speedup $S = \frac{T_{serial}}{T_{parrallel}}$ \
Efficiency $E = \frac{S}{P}$ \
$P$ is the number of threads 

# 2-II. program: [```n-body-mpi.c```](code/n-body-mpi.c)
## Purpose:

Speedup $S = \frac{T_{serial}}{T_{parrallel}}$ \
Efficiency $E = \frac{S}{P}$ \
$P$ is the number of threads 

```n-body-mpi.c``` \
[run_n-body-mpi.sh.e639586](outputs/run_n-body-mpi.sh.e639586) \
[run_n-body-mpi.sh.o639586](outputs/run_n-body-mpi.sh.o639586)




# 3. Description of my research theme
## Graduate Research Theme
My current research focuses on developing and optimizing Convolutional Neural Networks (CNNs) for the detection of brain tumors in MRI images. The goal is to achieve high accuracy and efficiency in identifying tumor regions, addressing challenges such as limited labeled datasets, variability in tumor shapes and sizes, and the computational intensity required for processing high-resolution medical images.

The study involves training CNN architectures, such as U-Net and ResNet, on annotated MRI datasets. This research aims to contribute to early tumor detection, aiding clinicians in diagnostic processes, and reducing the reliance on subjective interpretation. Further, I am exploring advanced techniques like transfer learning to enhance model performance on small datasets and data augmentation to create diverse training samples.

## Supercomputing Contributions to the Research
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

## Conclusion
The availability of a supercomputer would significantly accelerate the progress of my research by addressing current computational limitations, enabling larger-scale studies, and fostering the development of more robust and accurate tumor detection models. This, in turn, could pave the way for early and precise diagnostics, ultimately improving patient outcomes.

# 4. How was this class?
