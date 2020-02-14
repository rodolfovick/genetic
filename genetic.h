#ifndef _GENETIC_H
#define _GENETIC_H

#define TIMES 10

#define GENE_SIZE 6
typedef struct chromosome_s {
	float genes[GENE_SIZE];
	float fit;
} chromosome_t;

#define MAX_VALUE 1000
#define RANGE_MAX MAX_VALUE * 2 * 100
#define RAMGE_AJUST MAX_VALUE * 100
float fit_weight[GENE_SIZE] = {4, -2, 3.5, 5, -11, -4.7};

#define POPULATION_SIZE 8
typedef struct population_s {
	chromosome_t chromosomes[POPULATION_SIZE];
} population_t;

#endif /* _GENETIC_H */
