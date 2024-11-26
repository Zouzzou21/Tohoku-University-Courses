# How to compile and run this code

## Compilation

```
# Default
mpicc -O3 cg.c main.c MyMPI.c -o cg
```


```
# For profiling
mpicc -pg cg.c main.c MyMPI.c -o cg
```

``` 
# With OpenMP
mpicc -fopenmp -O3 cg.c main.c MyMPI.c -o cg
```

## Generate input files

``` 
gcc gen-cg.c -o gen-cg
./gen-cg 10240 a-10k b-10k
```

