#ifndef PNL

#define PNL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NOMEMORY 100

int run_simulation(int run_idx, int num_of_assets, int t, double *prices, double *quantities, double *deltas, double *sigmas, double **portfo_values, double **portfo_returns, double *current_prices, double *initial_positions);

#endif
