CC=$(CROSS_COMPILE)gcc

all: genetic

genetic: genetic.c genetic.h
	$(CC) genetic.c -o genetic -lm

clean: genetic
	rm genetic
