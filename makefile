# module swap openmpi3 mpich/3.2.1

all:
	make one
	make two
	make three
	make four

one: 
	mpicc sieve1.c -lm -o sieve1
	sbatch ./sieve1-32.sbatch
	sbatch ./sieve1-64.sbatch
	sbatch ./sieve1-128.sbatch
two: 
	mpicc sieve2.c -lm -o sieve2
	sbatch ./sieve2-32.sbatch
	sbatch ./sieve2-64.sbatch
	sbatch ./sieve2-128.sbatch
three: 
	mpicc sieve3.c -lm -o sieve3
	sbatch ./sieve3-32.sbatch
	sbatch ./sieve3-64.sbatch
	sbatch ./sieve3-128.sbatch
four: 
	mpicc sieve4.c -lm -o sieve4
	sbatch ./sieve4-32.sbatch
	sbatch ./sieve4-64.sbatch
	sbatch ./sieve4-128.sbatch

clean:
	rm -f sieve1 sieve2 sieve3 sieve4 *.out
