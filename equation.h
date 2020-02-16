#ifndef _EQUATION_H
#define _EQUATION_H

#define TIMES 0xffffffff

#define VARIABLES_NUM 6
#define EQUAL_VALUE 13.0

float fit_weight[VARIABLES_NUM] = {4, -2, 3.5, 5, -11, -4.7};

float min_value[VARIABLES_NUM]  = {-10, -10, -10, -10, -10, -10};

float max_value[VARIABLES_NUM]  = { 10,  10,  10,  10,  10,  10};

char zero_value[VARIABLES_NUM]  = {0, 0, 0, 0, 0, 0};

#endif /*_EQUATION_H*/
