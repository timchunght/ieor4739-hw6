#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utilities.h"
#include "pnl.h"
#include "helpers.h"


int main(int argc, char *argv[])
{ 

  int num_of_assets;
  char *positions_filename = "./positions.txt";
  char *prices_filename = "./prices.txt";
  double max = 1e-10;
  double *x = NULL;
  int *indices = NULL;
  int t;
  int max_period = 10000;
  int runs_count = 100;
  double *prices = NULL;
  double budget = 1e10;
  double *deltas = NULL;
  double *sigmas = NULL;
  double *quantities = NULL;
  double *portfo_values = (double*)calloc(runs_count, sizeof(double));
  double *portfo_returns = (double*)calloc(runs_count, sizeof(double));
  

  printf("hello world\n");
  int code = import_positions(positions_filename, &x, &num_of_assets, &indices, max);
  if(code != 0) {
    return code;
  }
  printf("x: %g\n", *x);
  printVector(num_of_assets, x);
  code = import_prices(prices_filename, &prices, num_of_assets, indices, &t, max_period);
  if(code != 0) {
    return code;
  }
  printf("prices:\n");
  printVector(num_of_assets, prices);


  
  // calculate array of averages of changes; array of Mu [Mui1, Mui2...]
  calculate_average_deltas(prices, num_of_assets, t, &deltas);
  printf("deltas:\n");
  printVector(num_of_assets, deltas);

  // calculate array of standard deviation of changes
  calculate_sigmas(prices, num_of_assets, t, deltas, &sigmas);
  printf("sigmas:\n");
  printVector(num_of_assets, sigmas);


  // calculate quantities
  calculate_quantities(num_of_assets, t, budget, x, prices, &quantities);
  printf("quantities:\n");
  printVector(num_of_assets, quantities);


}

// int run_simulation(unsigned int *prseed, int num_of_assets, int t, double *prices, double *deltas, double *sigmas);
// int run_simulation(unsigned int *prseed, int num_of_assets, int t, double *prices, double *deltas, double *sigmas) {
//   // int n, t;
//   int n = num_of_assets;
//   double *p = prices
//   double *deltas = deltas;
//   double *sigmas = sigmas;
//   // double *p, *q, *deltas, *sigmas;
//   double portfo_value;
//   double portfo_value_temp; 
//   double portfo_return;

//   // n = pf->n;
//   // t = pf->t;
//   // p = pf->p;
//   // q = pf->q;
//   // deltas = pf->delta;
//   // sigmas = pf->sigma;

//   portfo_return = 0.0;
//   for (int j = 0; j < t; j++) {
//     portfo_value = 0.0;
//     for (int i = 0; i < n; i++) {
//       /**pf_v += p[i*t + j] * q[i];**/ /** no perturbations **/
//       portfo_value += (p[i*t + j] + (sigmas[i]*drawnormal_r(prseed) + delta[i])) * q[i];
//     }
//     if (j > 0) {
//       portfo_return += (portfo_value - portfo_value_temp) / portfo_value_temp;
//     }
//     portfo_value_temp = portfo_value;
//   }

//   portfo_return = portfo_return/(t - 1);

//   /** save results in an external array **/
//   // pf->pf_values[sim] = pf_v;
//   // pf->portfo_returns[sim] = portfo_return;

//   return 0;
// }


