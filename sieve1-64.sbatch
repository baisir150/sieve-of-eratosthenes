#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 2
#SBATCH -J sieve1-64
#SBATCH -o sieve1-64.out
#SBATCJ -e sieve1-64.%j.error

mpirun -n 64 ./sieve1 10000000000
