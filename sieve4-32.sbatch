#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 1
#SBATCH -J sieve4-32
#SBATCH -o sieve4-32.out
#SBATCJ -e sieve4-32.%j.error

mpirun -n 32 ./sieve4 10000000000 524288
