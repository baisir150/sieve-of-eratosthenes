#include "../lib/helper.h"

int optionO()
{
  int option;
  printf("\nSelect the Parallel Sieve of Eratosthenes algorithm to use:\n");
  printf("\t1. Default\n\t2. No even numbers\n\t3. Local computations (no broadcasts)\n\t4. Effective use of cache\n\t5. Quit\n\n");
  printf("> ");
  scanf("%d", &option);
  return option;
}

int optionN()
{
  int n;
  printf("\nEnter the maximum prime number:\n");
  printf("> ");
  scanf("%d", &n);
  return n;
}
