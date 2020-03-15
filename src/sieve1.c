#include "../lib/sieve1.h"

void sieve1(int argc, char *argv[], long n)
{
   long count;          /* Local prime count */
   double elapsed_time; /* Parallel execution time */
   long first;          /* Index of first multiple */
   long global_count;   /* Global prime count */
   long high_value;     /* Highest value on this proc */
   long i;
   int id;         /* Process ID number */
   long index;     /* Index of current prime */
   long low_value; /* Lowest value on this proc */
   char *marked;   /* Portion of 2,...,'n' */
   int p;          /* Number of processes */
   long prime;     /* Current prime */
   long size;      /* Elements in 'marked' */

   // initialize mpi
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &id);
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   MPI_Barrier(MPI_COMM_WORLD);

   // initialize mpi
   elapsed_time = -MPI_Wtime();

   // set basic variables
   low_value = 2 + id * (n - 1) / p;
   high_value = 1 + (id + 1) * (n - 1) / p;
   size = high_value - low_value + 1;

   // process number max
   if ((2 + ((n - 1) / p)) < (int)sqrt((double)n))
   {
      if (!id)
         printf("Too many processes\n");
      MPI_Finalize();
      exit(1);
   }

   // make array
   marked = (char *)malloc(size);
   if (marked == NULL)
   {
      printf("Cannot allocate enough memory\n");
      MPI_Finalize();
      exit(1);
   }

   // initialize array: *marked
   for (i = 0; i < size; i++)
      marked[i] = 0;

   // mark primes
   if (!id)
      index = 0;
   prime = 2;
   do
   {
      if (prime * prime > low_value)
         first = prime * prime - low_value;
      else
      {
         if (!(low_value % prime))
            first = 0;
         else
            first = prime - (low_value % prime);
      }
      for (i = first; i < size; i += prime)
         marked[i] = 1;
      if (!id)
      {
         while (marked[++index])
            ;
         prime = index + 2;
      }
      MPI_Bcast(&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
   } while (prime * prime <= n);

   // count primes
   count = 0;
   for (i = 0; i < size; i++)
      if (!marked[i])
         count++;

   MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

   // stop timer
   elapsed_time += MPI_Wtime();

   // results
   if (!id)
   {
      printf("\nThere are %d primes less than or equal to %ld\n", global_count, n);
      printf("SIEVE (%d) %10.6f\n", p, elapsed_time);
   }

   MPI_Finalize();
}
