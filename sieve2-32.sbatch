#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 1
#SBATCH -J sieve2-32
#SBATCH -o sieve2-32.out
#SBATCJ -e sieve2-32.%j.error

mpirun -n 32 ./sieve2 10000000000
