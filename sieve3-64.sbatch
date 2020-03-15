#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 2
#SBATCH -J sieve3-64
#SBATCH -o sieve3-64.out
#SBATCJ -e sieve3-64.%j.error

mpirun -n 64 ./sieve3 10000000000
