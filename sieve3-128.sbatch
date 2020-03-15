#!/bin/bash -l

#SBATCH -q defg
#SBATCH -N 4
#SBATCH -J sieve3-128
#SBATCH -o sieve3-128.out
#SBATCJ -e sieve3-128.%j.error

mpirun -n 128 ./sieve3 10000000000
