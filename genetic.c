#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

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

void crossover(chromosome_t a, chromosome_t b, chromosome_t *child_a, chromosome_t *child_b)
{
	int i;
	int half = GENE_SIZE / 2;	

	for (i = 0; i < half; i++) {
		child_a->genes[i] = a.genes[i];
		child_a->genes[i+half] = b.genes[i+half];

		child_b->genes[i] = b.genes[i];
		child_b->genes[i+half] = a.genes[i+half];
	}
}

void mutation(chromosome_t a, chromosome_t b, chromosome_t *child_a, chromosome_t *child_b)
{
	int i;
	int half = GENE_SIZE / 2;	

	for (i = 0; i < half; i++) {
		child_a->genes[i] = a.genes[i];
		child_a->genes[i+half] = b.genes[i+half] + ((random()%1000) - 500);

		child_b->genes[i] = b.genes[i];
		child_b->genes[i+half] = a.genes[i+half] + ((random()%1000) - 500);
	}
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

	random_population(&generation_next);

	for (times = 0; times < TIMES; times++) {

		memcpy(&generation, &generation_next, sizeof(population_t));
		for (i = 0; i < POPULATION_SIZE; i++) {
			fitness(&(generation.chromosomes[i]));
		}
		qsort(&(generation.chromosomes), POPULATION_SIZE, sizeof(chromosome_t), compare_chromosome);
		printf("Iteration %d ", times);
		print_population(generation);

		memset(&generation_next, 0, sizeof(population_t));
		for (i = 0; i < POPULATION_SIZE/2; i+=2) {
			crossover(generation.chromosomes[i], 
                      generation.chromosomes[i+1],
					  &(generation_next.chromosomes[i]), 
                      &(generation_next.chromosomes[i+1]));
			mutation(generation.chromosomes[i], 
                      generation.chromosomes[i+1],
					  &(generation_next.chromosomes[i+(POPULATION_SIZE/2)]), 
                      &(generation_next.chromosomes[i+1+(POPULATION_SIZE/2)]));
		}
	}

	qsort(&(generation.chromosomes), POPULATION_SIZE, sizeof(chromosome_t), compare_chromosome);
	printf("Final ");
	print_population(generation);

	return 0;
}
