#include <stdio.h>
#include <stdlib.h>

#include "equation.h"

void print(float *x, int size) 
{
	int i;
	float v = 0;

	for (i = 0; i < size; i++) {
		v += x[i] * fit_weight[i];
		printf("%0.2f ", x[i]);
	}
	printf(": %0.2f\n", v);
}


float calculate(float *x, int size) 
{
	int i;
	float v = 0;

	for (i = 0; i < size; i++) {
		v += x[i] * fit_weight[i];
	}

	return v;
}

int main()
{
	float x[VARIABLES_NUM];

	for (x[0] = min_value[0]; x[0] <= max_value[0]; x[0] += 0.01) {
		for (x[1] = min_value[1]; x[1] <= max_value[1]; x[1] += 0.01) {
			for (x[2] = min_value[2]; x[2] <= max_value[2]; x[2] += 0.01) {
				for (x[3] = min_value[3]; x[3] <= max_value[3]; x[3] += 0.01) {
					for (x[4] = min_value[4]; x[4] <= max_value[4]; x[4] += 0.01) {
						for (x[5] = min_value[5]; x[5] <= max_value[5]; x[5] += 0.01) {
							if (calculate(x, VARIABLES_NUM) == EQUAL_VALUE) {
								print(x, VARIABLES_NUM);
								exit(0);
							}
						}
					}
				}
			}
		}
	}

	return 0;
}
