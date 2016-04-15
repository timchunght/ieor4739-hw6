
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>


double get_average(int n, double *arr) {
	int i;
	double total;

	total = 0.0;
	for (i = 0; i < n; i++) {
		total += arr[i];
	}

	return total/n;
}

int import_positions(char* filename, double **px, int* num_of_asset, int** indices_pointer, double max) {

  char buffer[100];
  FILE *file;
  int asset_size; //number of assets
  int non_size_asset_count; //number of non zero assets
  double *x = NULL;
  int *indices = NULL;

  file = fopen(filename, "r");
  if (file == NULL) {
    return 1;
  }

  fscanf(file, "%s", buffer);
  fscanf(file, "%s", buffer);
  asset_size = atoi(buffer);
  x = (double*)calloc(asset_size, sizeof(double));
  indices = (int*)calloc(asset_size, sizeof(int));
  if (x == NULL || indices == NULL) {
    return 100;
  }

  for (int i = 0; i < asset_size; i++) {
    fscanf(file, "%s", buffer);
    x[i] = atof(buffer);
  }
  fclose(file);

  non_size_asset_count = 0;
  for (int i = 0; i < asset_size; i++) {
    if (x[i] > max) {
      indices[non_size_asset_count] = i;
      non_size_asset_count++;
    }
  }
  
  for (int j = 0; j < non_size_asset_count; j++) {
    x[j] = x[indices[j]];
  }

  *indices_pointer = indices;
  *num_of_asset = non_size_asset_count;
  *px = x;
 
  return 0;
}


int import_prices(char* filename, double **prices_pointer, int n, int *indices, int *time_pointer, int max_period) {
  
  FILE *f;
  char b[100];
  int i, ii, j;

  int N, T;
  int t;
  double *p = NULL;

  f = fopen(filename, "r");
  if (f == NULL) {
    return 1;
  }

  fscanf(f, "%s", b);
  fscanf(f, "%s", b);
  N = atoi(b);
  fscanf(f, "%s", b);
  fscanf(f, "%s", b);
  T = atoi(b);
  if (T > max_period)
    t = max_period;
  else
    t = T;

  /** skip the dates line **/
  fscanf(f, "%s", b);
  for (j = 0; j < T; j++)
    fscanf(f, "%s", b);

  p = calloc(n*t, sizeof(double));

  if (p == NULL) {
    return 100;
  }

  ii = 0;
  for (i = 0; i < N; i++) {
    fscanf(f, "%s", b);/** jump over asset name **/
    fscanf(f, "%s", b);/** jump over Adj_close: **/
    for (j = 0; j < T; j++) {
      fscanf(f, "%s", b);
      if (ii<n && i == indices[ii] && j < t)
        p[ii*t + j] = atof(b);
    }
    if (i == indices[ii])
      ii++;
  }
  fclose(f);
  
  *time_pointer = t;

  *prices_pointer = p;
 
  return 0;
}

void printVector(int n, double *vector)
{
  int j;

  for (j = 0; j < n; j++){
    printf(" %g", vector[j]);
  }
  printf("\n");
}




int calculate_average_deltas(double *prices, int num_of_assets, int t, double **delta_pointer) {
  double change;
  double *deltas = NULL;

  deltas = (double *) calloc(num_of_assets, sizeof(double));
  for (int i = 0; i < num_of_assets; i++) {
    deltas[i] = 0;
    for (int k = 0; k < (t - 1); k++) {
      change = (prices[i * t + k + 1] - prices[i * t + k]);
      deltas[i] += change;
    }
    deltas[i] = deltas[i]/(t - 1);
  }

  *delta_pointer = deltas;

  return 0;
}


int calculate_sigmas(double *prices, int num_of_assets, int t, double *deltas, double **sigmas_pointer) {
  double change;
  double *sigmas = NULL;

  sigmas = (double *) calloc(num_of_assets, sizeof(double));
  
  for (int i = 0; i < num_of_assets; i++) {
    sigmas[i] = 0;
    for (int k = 0; k < t - 1; k++) {
      change = (prices[i * t + k + 1] - prices[i * t + k]);
      sigmas[i] += (change - deltas[i]) * (change - deltas[i]);
    }
    sigmas[i] = sigmas[i]/(t - 1); 
    sigmas[i] = sqrt(sigmas[i]);
  }

  *sigmas_pointer = sigmas;

  return 0;
}

void calculate_quantities(int num_of_assets, int t, double budget, double *positions, double *prices, double **quantities_pointer) {
  double *quantities = (double *) calloc(num_of_assets, sizeof(double));
  
  for (int i = 0; i < num_of_assets; i++) {
    quantities[i] = positions[i] * (budget/ prices[i*t + 0]);
  }

  *quantities_pointer = quantities;
 
}