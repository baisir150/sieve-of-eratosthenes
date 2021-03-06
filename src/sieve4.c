#include "../lib/sieve4.h"

void sieve4(int argc, char *argv[], long n)
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
   long primes_size;
   char *primes;
   long sec;
   long chunk;
   long lv;
   int p;      /* Number of processes */
   long prime; /* Current prime */
   long size;  /* Elements in 'marked' */

   // initialize mpi
   MPI_Init(&argc, &argv);
   MPI_Barrier(MPI_COMM_WORLD);
   MPI_Comm_rank(MPI_COMM_WORLD, &id);
   MPI_Comm_size(MPI_COMM_WORLD, &p);

   // start timer
   elapsed_time = -MPI_Wtime();

   // set basic variables
   m = (n - 3) / 2 + 1;
   chunk = atol(argv[2]);
   low_value = 2 * BLOCK_LOW(id, p, m) + 3;
   high_value = 2 * BLOCK_HIGH(id, p, m) + 3;
   size = BLOCK_SIZE(id, p, m);

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

   // process number max
   primes_size = (sqrt(n) - 3) / 2 + 1;
   primes = (char *)malloc(primes_size);
   if (primes == NULL)
   {
      printf("Cannot allocate enough memory\n");
      free(marked);
      MPI_Finalize();
      exit(1);
   }

   // initialize array: *primes
   for (i = 0; i < primes_size; i++)
      primes[i] = 0;

   // mark: *primes
   index = 0;
   prime = 3;
   do
   {
      for (i = (prime * prime - 3) / 2; i < primes_size; i += prime)
         primes[i] = 1;
      while (primes[++index])
         ;
      prime = 2 * index + 3;
   } while (prime * prime <= sqrt(n));

   for (sec = 0; sec < size; sec += chunk)
   {
      index = 0;
      prime = 3;
      lv = 2 * ((low_value - 3) / 2 + sec) + 3;
      do
      {
         if (prime * prime > lv)
            first = (prime * prime - 3) / 2 - (lv - 3) / 2;
         else
         {
            loc = lv % prime;
            if (!loc)
               first = 0;
            else
            {
               first = prime - loc;
               if (!((lv + first) % 2))
                  first = (first + prime) / 2;
               else
                  first /= 2;
            }
         }
         for (i = first + sec; i < first + sec + chunk && i < size; i += prime)
            marked[i] = 1;
         while (primes[++index])
            ;
         prime = 2 * index + 3;
      } while (prime * prime <= n);
   }

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
      printf("\nThere are %ld primes less than or equal to %ld\n", global_count + 1, n);
      printf("SIEVE (%d) %10.6f\n", p, elapsed_time);
   }

   MPI_Finalize();
}
