# module swap openmpi3 mpich/3.2.1

OBJS = sieve.o helper.o sieve1.o sieve2.o sieve3.o sieve4.o
OOPTS = -lm -c
LOPTS = -lm

all : sieve

sieve : $(OBJS)
		mpicc $(LOPTS) $(OBJS) -o sieve

helper.o : ./src/helper.c ./lib/helper.h
		mpicc $(OOPTS) ./src/helper.c

sieve1.o : ./src/sieve1.c ./lib/sieve1.h
		mpicc $(OOPTS) ./src/sieve1.c

sieve2.o : ./src/sieve2.c ./lib/sieve2.h
		mpicc $(OOPTS) ./src/sieve2.c

sieve3.o : ./src/sieve3.c ./lib/sieve3.h
		mpicc $(OOPTS) ./src/sieve3.c

sieve4.o : ./src/sieve4.c ./lib/sieve4.h
		mpicc $(OOPTS) ./src/sieve4.c

sieve.o : ./src/sieve.c ./lib/sieve1.h ./lib/sieve2.h ./lib/sieve3.h ./lib/sieve4.h
		mpicc $(OOPTS) ./src/sieve.c

test : sieve
		./sieve

valgrind : sieve
		valgrind ./sieve

clean	:
		rm -f $(OBJS) sieve