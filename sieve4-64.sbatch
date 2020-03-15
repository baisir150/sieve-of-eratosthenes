#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 2
#SBATCH -J sieve4-64
#SBATCH -o sieve4-64.out
#SBATCJ -e sieve4-64.%j.error

mpirun -n 64 ./sieve4 10000000000 524288
