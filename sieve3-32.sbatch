#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 1
#SBATCH -J sieve3-32
#SBATCH -o sieve3-32.out
#SBATCJ -e sieve3-32.%j.error

mpirun -n 32 ./sieve3 10000000000
