all:
	mpicc -Wall -O3 main.c cg.c MyMPI.c -o cg
	gcc gen-cg.c -o gen-cg
clean:
	-@rm -f cg gen-cg *.o
prof:
	mpicc -Wall -pg main.c cg.c MyMPI.c -o cg
omp:
	mpicc -Wall -O3 -fopenmp main.c cg.c MyMPI.c -o cg


