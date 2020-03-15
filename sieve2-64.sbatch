#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 2
#SBATCH -J sieve2-64
#SBATCH -o sieve2-64.out
#SBATCJ -e sieve2-64.%j.error

mpirun -n 64 ./sieve2 10000000000
