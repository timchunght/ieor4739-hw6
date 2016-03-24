#ifndef PNL

#define PNL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NOMEMORY 100

int import_positions(char* filename, double **px, int* num_of_asset, int** indices_pointer, double max);
void PrintVector(int n, double *vector);


#endif
