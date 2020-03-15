#include "../lib/sieve2.h"

void sieve2(int argc, char *argv[], long n)
{
   long count;          /* Local prime count */
   double elapsed_time; /* Parallel execution time */
   long first;          /* Index of first multiple */
   long global_count;   /* Global prime count */
   long high_value;     /* Highest value on this proc */
   long i;
   long m;
   long loc;
   int id;         /* Process ID number */
   long index;     /* Index of current prime */
   long low_value; /* Lowest value on this proc */
   char *marked;   /* Portion of 2,...,'n' */
   int p;          /* Number of processes */
   long prime;     /* Current prime */
   long size;      /* Elements in 'marked' */

   // initializa mpi
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &id);
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   MPI_Barrier(MPI_COMM_WORLD);

   // start timer
   elapsed_time = -MPI_Wtime();

   // set basic variables
   m = (n - 3) / 2 + 1;
   low_value = 2 * BLOCK_LOW(id, p, m) + 3;
   high_value = 2 * BLOCK_HIGH(id, p, m) + 3;
   size = BLOCK_SIZE(id, p, m);

   // process number max
   if ((2 * (m - 1) + 3) < (int)sqrt((double)n))
   {
      if (!id)
         printf("Too many processes\n");
      MPI_Finalize();
      exit(1);
   }

   // allocate array: *marked
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
   prime = 3;
   do
   {
      if (prime * prime > low_value)
         first = (prime * prime - 3) / 2 - (low_value - 3) / 2;
      else
      {
         loc = low_value % prime;
         if (!loc)
            first = 0;
         else
         {
            first = prime - loc;
            if (!((low_value + first) % 2))
               first = (first + prime) / 2;
            else
               first /= 2;
         }
      }
      for (i = first; i < size; i += prime)
         marked[i] = 1;
      if (!id)
      {
         while (marked[++index])
            ;
         prime = 2 * index + 3;
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
      printf("\nThere are %d primes less than or equal to %ld\n", global_count + 1, n);
      printf("SIEVE (%d) %10.6f\n", p, elapsed_time);
   }

   MPI_Finalize();
}
