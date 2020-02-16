CC=$(CROSS_COMPILE)gcc

all: genetic

genetic: genetic.c genetic.h equation.h
	$(CC) genetic.c -o genetic -lm

brute: brute.c equation.h
	$(CC) brute.c -o brute

clean: genetic
	rm genetic
