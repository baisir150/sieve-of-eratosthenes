#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 1
#SBATCH -J sieve1-32
#SBATCH -o sieve1-32.out
#SBATCJ -e sieve1-32.%j.error

mpirun -n 32 ./sieve1 10000000000
