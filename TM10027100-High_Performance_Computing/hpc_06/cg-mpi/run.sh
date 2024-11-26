#!/bin/sh -
#PBS -q lx_edu
#PBS -l elapstim_req=0:10:00


cd ${PBS_O_WORKDIR}
export OMP_NUM_THREADS=1
export MPI_NUM_PROCS=4

mpirun --bind-to none -np ${MPI_NUM_PROCS} ./cg a-mat b-vec
