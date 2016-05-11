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

void calculate_deterministic_probabilities(double* probabilities, int asset_count) {

	for (int k = 0; k <= asset_count; k++) {
		for (int k_prime = 0; k_prime < k; k_prime++) {

			probabilities[(k)*(asset_count+1) + (k_prime)] = 0.0;

		}
		probabilities[(k)*(asset_count+1) + (k)] = 1.0;
	}

	return;
}
