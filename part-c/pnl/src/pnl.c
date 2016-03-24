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

  int num_of_asset;
  char *positions_filename = "./positions.txt";
  char *prices_filename = "./prices.txt";
  double max = 1e-10;
  double *x = NULL;
  int *indices = NULL;
  int t;
  int max_period = 10000;
  double *prices = NULL;
  printf("hello world\n");
  int code = import_positions(positions_filename, &x, &num_of_asset, &indices, max);
  if(code != 0) {
    return code;
  }
  printf("x: %g\n", *x);
  printVector(num_of_asset, x);
  code = load_prices(prices_filename, &prices, num_of_asset, indices, &t, max_period);
  
}



// int import_prices


