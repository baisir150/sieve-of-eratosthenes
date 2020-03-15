# module swap openmpi3 mpich/3.2.1

all:
	mpicc sieve.c sieve1.c sieve2.c sieve3.c sieve4.c -lm -o sieve

clean:
	rm -f sieve
