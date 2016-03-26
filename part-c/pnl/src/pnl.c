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
  double *prices = NULL;
  double budget = 1e-10;
  double *deltas = NULL;
  double *sigmas = NULL;

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

  
  // calculate array of averages of changes; array of Mu [Mui1, Mui2...]
  calculate_average_deltas(prices, num_of_assets, t, &deltas);
  printf("deltas:\n");
  printVector(num_of_assets, deltas);

  // calculate array of standard deviation of changes
  calculate_sigmas(prices, num_of_assets, t, deltas, &sigmas);
  printf("sigmas:\n");
  printVector(num_of_assets, sigmas);

  

  


}



