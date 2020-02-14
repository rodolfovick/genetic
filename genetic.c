#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "genetic.h"

void fitness(chromosome_t *c) 
{
	int i;
	float val = 0;

	for (i = 0; i < GENE_SIZE; i++) {
		val += (c->genes[i] * fit_weight[i]);
	}
	c->fit = val;
}

int compare_chromosome(const void *a, const void *b) 
{
	chromosome_t *ca = (chromosome_t *)a;
	chromosome_t *cb = (chromosome_t *)b;
	return (int)(cb->fit - ca->fit);
}

void random_population(population_t *p)
{
	int i, j;
	float rand;
	time_t t = time(NULL);

	srandom((int)t);

	for (i = 0; i < POPULATION_SIZE; i++) {
		for (j = 0; j < GENE_SIZE; j++) {
			rand = ((random() % RANGE_MAX) - RAMGE_AJUST);
			p->chromosomes[i].genes[j] = rand / 100.0;
		}
	}
}


void print_population(population_t p)
{
	int i, j;

	printf("Population:\n");
	for (i = 0; i < POPULATION_SIZE; i++) {
		printf("  Chromosome: ");
		for (j = 0; j < GENE_SIZE; j++) {
			printf("%.02f ", p.chromosomes[i].genes[j]);
		}
		printf("FIT: %0.2f\n", p.chromosomes[i].fit);
	}
	printf("\n");
}

int main()
{
	int i,times;
	population_t generation;
	population_t generation_next;

	random_population(&generation);

	for (times = 0; times < TIMES; times++) {

		for (i = 0; i < POPULATION_SIZE; i++) {
			fitness(&(generation.chromosomes[i]));
		}
		qsort(&(generation.chromosomes), POPULATION_SIZE, sizeof(chromosome_t), compare_chromosome);
		print_population(generation);

	}
	return 0;
}
