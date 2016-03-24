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
  char *filename = "./positions.txt";
  double max = 1e-10;
  double *x = NULL;
  int *indices = NULL; 
  printf("hello world\n");
  int code = import_positions(filename, &x, &num_of_asset, &indices, max);
  if(code != 0) {
    return code;
  }
  printf("x: %g\n", *x);
  PrintVector(num_of_asset, x);


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
    return NOMEMORY;
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



void PrintVector(int n, double *vector)
{
  int j;

  for (j = 0; j < n; j++){
    printf(" %g", vector[j]);
  }
  printf("\n");
}







