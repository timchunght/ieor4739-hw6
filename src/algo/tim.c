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


void calculate_squareinv_probabilities(double* probabilities, int shares_count) {

	double a;
	double s;

	for (int k = 0; k <= shares_count; k++) {
		for (int kp = 0; kp <= k; kp++) {
			a = (double)(k - kp + 1);
			a = 1.0/(a*a);
		
			probabilities[(k)*(shares_count+1) + (kp)] = a;
		}
	}

	for (int k = 0; k <= shares_count; k++) {
		s = 0.0;
		for (int kp = 0; kp <= k; kp++)
			
			s += probabilities[(k)*(shares_count+1) + (kp)];

		for (int kp = 0; kp <= k; kp++) {

			probabilities[(k)*(shares_count+1) + (kp)] /=s;
		}
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
	int *path = (int*)calloc(T*(N+1), sizeof(int));
	double *d = (double*)calloc(N+1, sizeof(double));
	

	// execute alpha_log priceshifts func
	calculate_alpha_log_priceshifts(d, N, alpha);

	// selectively execute one of the probabilities func based on arg
	// calculate_deterministic_probabilities(probabilities, N);
	calculate_squareinv_probabilities(probabilities, N);
	
	tim_optimize(N, T, probabilities, optimal, path, d);
	tim_calculate_deterministic_profit(N, T, probabilities, optimal, path, d);
	return 0;
}


// takes double arrs and execute optimization logic
int tim_optimize(int N, int T, double *probabilities, double *optimal, int *path, double *d) {
	
	double predicted_revenue;
	double max_predicted_revenue;
	int max_index;
	int k, kp;

	int t = T-1;
	
	max_predicted_revenue = 0.0;
	for (int n = 0; n <= N; n++) {
		predicted_revenue = 0.0;
		k = n; 
		for (kp = 0; kp <= k; kp++) {
			predicted_revenue += get_probability(probabilities, N, kp, k) * (double)kp;
		}
		predicted_revenue *= d[k];
		if (predicted_revenue > max_predicted_revenue) {
			max_predicted_revenue = predicted_revenue;
		}

		F(optimal, N, t, n) = max_predicted_revenue;
		FP(path, N, t, n) = n;
	}

	for (int t = T-2; t >= 0; t--) {
		
		for (int n = 0; n <= N; n++) {
			max_predicted_revenue = 0.0;
			max_index = 0;
			for (k = 0; k <= n; k++) {
				
				// find sum
				predicted_revenue = 0.0;
				for (kp = 0; kp <= k; kp++) {
					predicted_revenue += get_probability(probabilities, N, kp, k) * ((double)kp + F(optimal, N, t + 1, n - kp));
				}
				predicted_revenue *= d[k];
				// check if it is best; update if yes
				if (predicted_revenue > max_predicted_revenue) {
					max_predicted_revenue = predicted_revenue;
					max_index = k;
				}
			}
			// find the max
			F(optimal, N, t, n) = max_predicted_revenue;
			FP(path, N, t, n) = max_index;
			
		}
	}

	return 0;
}


double tim_calculate_deterministic_profit(int N, int T, double *probabilities, double *optimal, int *path, double *d) {
	
// 	#define F(optimal, N, t, n) optimal[(t)*(N+1) + (n)]
// #define FP(path, N, t, n) path[(t)*(N+1) + (n)]
	double profit;
	double new_price;
	int sell_amount;
	int left = N;

	profit = 0.0;
	new_price = 1.0;
	for (int t = 0; t <= T-1; t++) {
		sell_amount = FP(path, N, t, left);

		printf("Step %d: Optimal: %g, Sell Amount: %d", t, F(optimal, N, t, left), sell_amount);

		left = left - sell_amount;

		// compute profit along the path
		new_price *= d[sell_amount];

		
		printf(", price: %g, transaction value: %g", new_price, new_price * (double)sell_amount);
	

		profit += new_price * (double)sell_amount;
	
		printf("\n");
	}

	printf("Maximum Profit: %g\n", profit);

	return profit;
}
