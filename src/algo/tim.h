#ifndef TIM

#define TIM

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define F(optimal, N, t, n) optimal[(t)*(N+1) + (n)]
#define FP(path, N, t, n) path[(t)*(N+1) + (n)]
#define get_probability(probabilities, N, kp, k) probabilities[(k)*(N+1) + (kp)]


int sample();
extern int caller();
void calculate_deterministic_probabilities(double* probabilities, int shares_count);
void calculate_alpha_log_priceshifts(double* d, int shares_count, double alpha);
int tim_resources_allocate(int N, int T, double alpha);
int tim_optimize(int N, int T, double *probabilities, double *optimal, double *path, double *d);

#endif
