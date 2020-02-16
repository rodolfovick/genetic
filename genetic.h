#ifndef _GENETIC_H
#define _GENETIC_H

typedef struct chromosome_s {
	float genes[VARIABLES_NUM];
	float fit;
} chromosome_t;

#define POPULATION_SIZE 8
typedef struct population_s {
	chromosome_t chromosomes[POPULATION_SIZE];
} population_t;

#endif /* _GENETIC_H */
