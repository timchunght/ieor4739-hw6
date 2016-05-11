#ifndef TIM

#define TIM

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int sample();
extern int caller();
void calculate_deterministic_probabilities(double* probabilities, int shares_count);
void calculate_alpha_log_priceshifts(double* d, int shares_count, double alpha);
int tim_resources_allocate(int N, int T, double alpha);
#endif
