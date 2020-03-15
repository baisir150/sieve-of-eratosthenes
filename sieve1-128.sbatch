#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 4
#SBATCH -J sieve1-128
#SBATCH -o sieve1-128.out
#SBATCJ -e sieve1-128.%j.error

mpirun -n 128 ./sieve1 10000000000
