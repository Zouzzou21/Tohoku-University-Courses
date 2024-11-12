# Question #1
Run the OpenMP program on Slide 16 with changing the number of threads. How does the execution time change with the thread count?

## My answer:
```sh
[user@front1 ~]$ touch hpc_05_slide_Q1.c
[user@front1 ~]$ nano hpc_05_slide_Q1.c
[user@front1 ~]$ gcc -fopenmp hpc_05_slide_Q1.c
[user@front1 ~]$ export OMP_NUM_THREADS=1
[user@front1 ~]$ time ./a.out
real    0m16.006s
user    0m0.002s
sys     0m0.001s
[user@front1 ~]$ export OMP_NUM_THREADS=4
[user@front1 ~]$ time ./a.out
real    0m4.005s
user    0m0.000s
sys     0m0.006s
[user@front1 ~]$ export OMP_NUM_THREADS=8
[user@front1 ~]$ time ./a.out
real    0m2.005s
user    0m0.000s
sys     0m0.012s
```
We notice that the more threads we use, the faster the process is in execution time.

---

# Question #2
Write a code to check the behavior of reduction code in Slide 22, and paste it.

## My answer:
Code:
```c
#include <stdio.h>
#include <unistd.h>

int main(int ac,char* av){
        int x=0,i,j,N=10;
        #pragma omp parallel for reduction(+:x), private(j)
        for(i=0;i<N;i++){
                for(j=0;j<N;j++){
                        x+=j;
                }
        }
        printf("Sum: %d", x);
        return 0;
}
```

Output bash:
```sh
[user@front1 ~]$ touch hpc_05_Q2.c
[user@front1 ~]$ nano hpc_05_Q2.c
[user@front1 ~]$ gcc -fopenmp hpc_05_Q2.c
[user@front1 ~]$ time ./a.out
Sum: 450
real    0m0.005s
user    0m0.013s
sys     0m0.015s
[user@front1 ~]$ export OMP_NUM_THREADS=1
[user@front1 ~]$ time ./a.out
Sum: 450
real    0m0.003s
user    0m0.000s
sys     0m0.002s
[user@front1 ~]$ export OMP_NUM_THREADS=4
[user@front1 ~]$ time ./a.out
Sum: 450
real    0m0.003s
user    0m0.001s
sys     0m0.005s
[user@front1 ~]$ export OMP_NUM_THREADS=8
[user@front1 ~]$ time ./a.out
Sum: 450
real    0m0.004s
user    0m0.001s
sys     0m0.009s
```

---

# Answer [ans-05.pdf](ans-05.pdf)