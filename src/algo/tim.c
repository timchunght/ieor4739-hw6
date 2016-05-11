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
	double *optimal = (double*)calloc(T*(N+1), sizeof(double));
	double *path = (int*)calloc(T*(N+1), sizeof(int));
	double *d = (double*)calloc(N+1, sizeof(double));
	

	calculate_alpha_log_priceshifts(d, N, alpha);
	calculate_deterministic_probabilities(probabilities, N);
	
	tim_optimize(N, T, probabilities, optimal, path, d);
	return 0;
}


// takes double arrs and execute optimization logic
int tim_optimize(int N, int T, double *probabilities, double *optimal, double *path, double *d) {
	
	double expected_revenue;
	double best_expected_revenue;
	int best_index;

	double profit;
	double newprice;
	int sell, k, kp;

	int t = T-1;
	
	printf("t = %d\n", t); fflush(stdout);
	best_expected_revenue = 0.0;
	for (int n = 0; n <= N; n++) {
		expected_revenue = 0.0;
		k = n; 
		for (kp = 0; kp <= k; kp++) {
			expected_revenue += get_probability(probabilities, N, kp, k) * (double)kp;
		}
		expected_revenue *= d[k];
		if (expected_revenue > best_expected_revenue) {
			best_expected_revenue = expected_revenue;
		}

		F(optimal, N, t, n) = best_expected_revenue;
		FP(path, N, t, n) = n;
	}

	for (int t = T-2; t >= 0; t--) {
		
		printf("t = %d\n", t); fflush(stdout);
		
		for (int n = 0; n <= N; n++) {
			best_expected_revenue = 0.0;
			best_index = 0;
			for (k = 0; k <= n; k++) {
				
				// find sum
				expected_revenue = 0.0;
				for (kp = 0; kp <= k; kp++) {
					expected_revenue += get_probability(probabilities, N, kp, k) * ((double)kp + F(optimal, N, t + 1, n - kp));
				}
				expected_revenue *= d[k];
				// check if it is best; update if yes
				if (expected_revenue > best_expected_revenue) {
					best_expected_revenue = expected_revenue;
					best_index = k;
				}
			}
			// find the max
			F(optimal, N, t, n) = best_expected_revenue;
			FP(path, N, t, n) = best_index;
			
		}
	}

	return 0;
}

