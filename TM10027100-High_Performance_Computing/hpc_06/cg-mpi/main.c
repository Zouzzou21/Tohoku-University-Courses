/*
 *   Conjugate Gradient Method
 *
 *   This hybrid MPI/OpenMP program uses the conjugate gradient method to
 *   solve a postive definite system of linear equations.
 *
 *   Programmer: Michael J. Quinn
 * 
 *   Updated by Hiroyuki Takizawa
 *   Last modification: 15 November 2020
 */
#include <stdlib.h>
#include <stdio.h>
#include "MyMPI.h"
#include <omp.h>

extern void cg (int p, int id, double **a, double *b, double *x, int n );

static void check_solution(double* x, int n)
{
    int i;
    for(i=0;i<n;i++){
        if((int)(x[i]+0.5)!=i) printf("Failed\n");
    }    
    printf("Success\n");
}

int main (int argc, char *argv[])
{
   double **a;                /* Solving Ax = b for x */
   double *astorage;          /* Holds elements of A */
   double *b;                 /* Constant vector */
   double *x=NULL;            /* Solution vector */
   int     p;                 /* MPI Processes */
   int     id;                /* Process rank */
   int     m;                 /* Rows in A */
   int     n;                 /* Columns in A */
   int     n1;                /* Elements in b */
   int     it;                /* iteration */
   double  wtime;
   /* Initialize a and b so that solution is x[i] = i */

   MPI_Init (&argc, &argv);
   MPI_Comm_size (MPI_COMM_WORLD, &p);
   MPI_Comm_rank (MPI_COMM_WORLD, &id);
   read_row_striped_matrix (argv[1], (void *) &a, (void *) &astorage,
      MPI_DOUBLE, &m, &n, MPI_COMM_WORLD);
   read_replicated_vector (argv[2], (void **) &b,
      MPI_DOUBLE, &n1, MPI_COMM_WORLD);
   if ((m != n) || (n != n1)) {
      if (!id)
         printf ("Incompatible dimensions (%d x %d) x (%d)\n", m, n, n1);
   } else {
      x = (double *) malloc (n * sizeof(double));
      /* CG is executed 10 times to increase the execution time */
      MPI_Barrier(MPI_COMM_WORLD);
      wtime = - MPI_Wtime();
      for(it=0;it<1;it++)
        cg (p, id, a, b, x, n);
      /*print_replicated_vector (x, MPI_DOUBLE, n, MPI_COMM_WORLD);*/
      MPI_Barrier(MPI_COMM_WORLD);
      wtime += MPI_Wtime();
   }

   if(id==0){
      check_solution(x,n);
      printf("Problem size : %d\n",n);
      printf("Matrix A     : %s\n",argv[1]);
      printf("Vector B     : %s\n",argv[2]);
      printf("# MPI Procs  : %d\n",p);
      printf("# Threads    : %s\n",getenv("OMP_NUM_THREADS"));
      printf("Time [sec]   : %lf\n",wtime);
   }
   MPI_Finalize();
}

