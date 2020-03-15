#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 4
#SBATCH -J sieve4-128
#SBATCH -o sieve4-128.out
#SBATCJ -e sieve4-128.%j.error

mpirun -n 128 ./sieve4 10000000000 524288
