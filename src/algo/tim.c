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
void calculate_deterministic_probabilities(double* probabilities, int asset_count) {

	for (int k = 0; k <= asset_count; k++) {
		for (int k_prime = 0; k_prime < k; k_prime++) {

			probabilities[(k)*(asset_count+1) + (k_prime)] = 0.0;

		}
		probabilities[(k)*(asset_count+1) + (k)] = 1.0;
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
