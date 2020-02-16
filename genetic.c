#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "equation.h"
#include "genetic.h"

void fitness(chromosome_t *c) 
{
	int i;
	float val = 0;

	for (i = 0; i < VARIABLES_NUM; i++) {
		val += (c->genes[i] * fit_weight[i]);
	}
	if (val > EQUAL_VALUE) {
		c->fit = val - EQUAL_VALUE;
	}
	else {
		c->fit = EQUAL_VALUE - val;
	}
}

float random_number(int i) 
{
	int min, max;

	min = (int)(min_value[i] * 100);
	max = (int)(max_value[i] * 100);
	return ((random() % (max - min + 1)) + min) / 100.0; 
}

int compare_chromosome(const void *a, const void *b) 
{
	chromosome_t *ca = (chromosome_t *)a;
	chromosome_t *cb = (chromosome_t *)b;
	return (int)((ca->fit*100) - (cb->fit*100));
}

void crossover(chromosome_t a, chromosome_t b, chromosome_t *child_a, chromosome_t *child_b)
{
	int i;
	int half = VARIABLES_NUM / 2;	

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
	int half = VARIABLES_NUM / 2;	
	float g;

	for (i = 0; i < half; i++) {
		do {
			g = a.genes[i] + (random_number(i)/0.1);
		} while ((g < min_value[i] || g > max_value[i]));
		child_a->genes[i] = g;

		do {
			g = b.genes[i+half] + (random_number(i)/0.1);
		} while ((g < min_value[i] || g > max_value[i]));
		child_a->genes[i+half] = g;

		do {
			g = b.genes[i] + (random_number(i)/0.1);
		} while ((g < min_value[i] || g > max_value[i]));
		child_b->genes[i] = g;

		do {
			g = a.genes[i+half] + (random_number(i)*0.1);
		} while ((g < min_value[i] || g > max_value[i]));
		child_b->genes[i+half] = g;
	}
}

void random_population(population_t *p)
{
	int i, j;
	time_t t = time(NULL);
	float r;

	srandom((int)t);

	for (i = 0; i < POPULATION_SIZE; i++) {
		for (j = 0; j < VARIABLES_NUM; j++) {
			do {
				r = random_number(j);
			} while (!zero_value[j] && !r);
			p->chromosomes[i].genes[j] = r; 
		}
	}
}


void print_population(population_t p)
{
	int i, j;

	printf("Population:\n");
	for (i = 0; i < POPULATION_SIZE; i++) {
		printf("  Chromosome: ");
		for (j = 0; j < VARIABLES_NUM; j++) {
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
		//printf("Iteration %d ", times);
		//print_population(generation);
		if (generation.chromosomes[0].fit == 0) {
			break;
		}
			
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
	printf("Final %d ", times);
	print_population(generation);

	printf("%f\n", generation.chromosomes[0].genes[0] * fit_weight[0] + 
	               generation.chromosomes[0].genes[1] * fit_weight[1] + 
	               generation.chromosomes[0].genes[2] * fit_weight[2] + 
	               generation.chromosomes[0].genes[3] * fit_weight[3] + 
	               generation.chromosomes[0].genes[4] * fit_weight[4] + 
	               generation.chromosomes[0].genes[5] * fit_weight[5]);

	return 0;
}
