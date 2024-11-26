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

#define EPSILON 1.0e-10       /* Convergence criterion */

double *piece = NULL;         /* Temporary space used in mv product */
double *d = NULL;
double *g = NULL;             /* Gradient vector */
double *tmpvec = NULL;

/* Conjugate gradient method solves ax = b for x */
void cg (int p, int id, double **a, double *b, double *x, int n )
{
   int     i, it;                /* Loop indices */                
   double  denom1, denom2, num1,
           num2, s;              /* Temporaries */

   double dot_product (double *, double *, int);
   void matrix_vector_product (int, int, int, double **,
                               double *, double *);

   /* Initialize solution and gradient vectors */
   if(d == NULL)
     d = (double *) malloc (n * sizeof(double));
   if(g == NULL)
     g = (double *) malloc (n * sizeof(double));
   if(tmpvec == NULL)
     tmpvec = (double *) malloc (n * sizeof(double));
   if(piece == NULL)
     piece = (double *) malloc (BLOCK_SIZE(id,p,n) * sizeof(double));
   for (i = 0; i < n; i++) {
      d[i] = x[i] = 0.0;
      g[i] = -b[i];
   }

   /* Algorithm converges in n or fewer iterations */

   for (it = 0; it < n; it++) {
      denom1 = dot_product (g, g, n);
      matrix_vector_product (id, p, n, a, x, g);
      for (i = 0; i < n; i++)
         g[i] -= b[i];
      num1 = dot_product (g, g, n);

      /* When g is sufficiently close to 0, it is time to halt */
      if (num1 < EPSILON) break;

      for (i = 0; i < n; i++)
         d[i] = -g[i] + (num1/denom1) * d[i];
      num2 = dot_product (d, g, n);
      matrix_vector_product (id, p, n, a, d, tmpvec);
      denom2 = dot_product (d, tmpvec, n);
      s = -num2 / denom2;
      for (i = 0; i < n; i++) x[i] += s * d[i];
   }
}

/*
 *   Return the dot product of two vectors
 */

double dot_product (double *a, double *b, int n)
{
   int i;
   double answer;

   answer = 0.0;
   for (i = 0; i < n; i++)
      answer += a[i] * b[i];
   return answer;
}

/*
 *   Compute the product of matrix a and vector b and
 *   store the result in vector c
 */

void matrix_vector_product (int id, int p, int n,
                            double **a, double *b, double *c)
{
   int    i, j;
   double tmp;       /* Accumulates sum */

#pragma omp parallel for private(tmp,i,j)
   for (i = 0; i < BLOCK_SIZE(id,p,n); i++) {
      tmp = 0.0;
      for (j = 0; j < n; j++)
         tmp += a[i][j] * b[j];
      piece[i] = tmp;
   }
   replicate_block_vector (piece, n, (void *) c, MPI_DOUBLE, MPI_COMM_WORLD);
}
