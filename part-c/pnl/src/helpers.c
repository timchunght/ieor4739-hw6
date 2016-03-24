
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