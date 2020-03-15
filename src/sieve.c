#include "../lib/helper.h"

int main(int argc, char *argv[])
{
  int o;
  long n;
  while (1)
	{
		o = optionO();
		if (o == 5)
			return 0;
		else if (o < 1 || o > 4)
			continue;
		else
    {
      n = optionN();
      if (o == 1) sieve1(argc, argv, n);
      else if (o == 2) sieve2(argc, argv, n);
      else if (o == 3) sieve3(argc, argv, n);
      else if (o == 4) sieve4(argc, argv, n);
      else printf("this shouldn't happen");
    }
  }
  return 0;
}
