#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

typedef struct
{
  double x, y, z;
} vector;

#define NUM_BODIES 10000
#define TIME_STEP 10
#define GRAV_CONST 0.01

double *masses;
vector *positions, *velocities, *accelerations;

vector addVectors(vector a, vector b)
{
  vector c = {a.x + b.x, a.y + b.y, a.z + b.z};

  return c;
}

vector scaleVector(double b, vector a)
{
  vector c = {b * a.x, b * a.y, b * a.z};

  return c;
}

vector subtractVectors(vector a, vector b)
{
  vector c = {a.x - b.x, a.y - b.y, a.z - b.z};

  return c;
}

double mod(vector a)
{
  return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

double random_number(double max, double min)
{
  double x = (double)rand() / RAND_MAX;

  return (max - min) * x + min;
}

void initiateSystem(void)
{
  int i;

  masses = (double *)malloc(NUM_BODIES * sizeof(double));
  positions = (vector *)malloc(NUM_BODIES * sizeof(vector));
  velocities = (vector *)malloc(NUM_BODIES * sizeof(vector));
  accelerations = (vector *)malloc(NUM_BODIES * sizeof(vector));

  for (i = 0; i < NUM_BODIES; i++)
  {
    masses[i] = random_number(0, 1);
    positions[i].x = random_number(-1, 1);
    positions[i].y = random_number(-1, 1);
    positions[i].z = random_number(-1, 1);
    velocities[i].x = random_number(-1, 1);
    velocities[i].y = random_number(-1, 1);
    velocities[i].z = random_number(-1, 1);
  }
}

void resolveCollisions()
{
  int i, j;

  for (i = 0; i < NUM_BODIES - 1; i++)
    for (j = i + 1; j < NUM_BODIES; j++)
    {
      if (positions[i].x == positions[j].x && positions[i].y == positions[j].y && positions[i].z == positions[j].z)
      {
        vector temp = velocities[i];
        velocities[i] = velocities[j];
        velocities[j] = temp;
      }
    }
}

void computeAccelerations()
{
  int i, j;

  for (i = 0; i < NUM_BODIES; i++)
  {
    accelerations[i].x = 0;
    accelerations[i].y = 0;
    accelerations[i].z = 0;
    for (j = 0; j < NUM_BODIES; j++)
    {
      if (i != j)
      {
        accelerations[i] = addVectors(accelerations[i], scaleVector(GRAV_CONST * masses[j] / pow(mod(subtractVectors(positions[i], positions[j])), 3), subtractVectors(positions[j], positions[i])));
      }
    }
  }
}

void computeVelocities()
{
  int i;

  for (i = 0; i < NUM_BODIES; i++)
    velocities[i] = addVectors(velocities[i], accelerations[i]);
}

void computePositions()
{
  int i;

  for (i = 0; i < NUM_BODIES; i++)
    positions[i] = addVectors(positions[i], addVectors(velocities[i], scaleVector(0.5, accelerations[i])));
}

void simulate()
{
  computeAccelerations();
  computePositions();
  computeVelocities();
  resolveCollisions();
}

/* start time measurement */
void timer_start(struct timespec *t)
{
  clock_gettime(CLOCK_REALTIME, t);
}

/* stop time measurement and print out */
void timer_stop(struct timespec *b, struct timespec *e)
{
  clock_gettime(CLOCK_REALTIME, e);
  unsigned int sec = e->tv_sec - b->tv_sec;
  int nsec = e->tv_nsec - b->tv_nsec;
  printf("%lf [sec]\n", sec + (double)nsec / (1000 * 1000 * 1000));
}

int main(int argc, char **argv)
{
  int i, j;
  struct timespec bgn, end;

  srand(time(NULL)); /* random seed */
  initiateSystem(); 

  for (i = 0; i < TIME_STEP; i++)
  {
    printf("\nCycle %d: ", i + 1);
    timer_start(&bgn);
    simulate();
    timer_stop(&bgn, &end);
  }
  return 0;
}