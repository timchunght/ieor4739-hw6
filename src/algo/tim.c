#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include "tim.h" 



int sample()
{
  
  printf("input %d\n", 123);

  return 0;

}

int caller()
{
  
  sample();

  return 0;

}

// this function alters the probabilities  array ([double]) passed in
void calculate_deterministic_probabilities(double* probabilities, int shares_count) {

	for (int k = 0; k <= shares_count; k++) {
		for (int k_prime = 0; k_prime < k; k_prime++) {

			probabilities[(k)*(shares_count+1) + (k_prime)] = 0.0;

		}
		probabilities[(k)*(shares_count+1) + (k)] = 1.0;
	}

	return;
}

// this function alters the d array ([double]) passed in
void calculate_alpha_log_priceshifts(double* d, int shares_count, double alpha) {


	for (int n = 0; n <= shares_count; n++) {
		d[n] = 1.0 - alpha*log(1.0 + (double)n);
	}

	return;
}

int tim_resources_allocate(int N, int T, double alpha) {

	printf("shares_count: %d, T (periods): %d\n", N, T);

	double *probabilities = (double*)calloc((N+1)*(N+1), sizeof(double));
	// double *optimal = (double*)calloc(T*(N+1), sizeof(double));
	// double *path = (int*)calloc(T*(N+1), sizeof(int));
	double *d = (double*)calloc(N+1, sizeof(double));
	

	calculate_alpha_log_priceshifts(d, N, alpha);
	calculate_deterministic_probabilities(probabilities, N);
	
	return 0;
}
