#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 4
#SBATCH -J sieve2-128
#SBATCH -o sieve2-128.out
#SBATCJ -e sieve2-128.%j.error

mpirun -n 128 ./sieve2 10000000000
