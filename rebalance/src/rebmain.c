
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readdata(char *filename, int *pnumassets, 
	     double **ptargetx, double **pprices, double **pshares);
int RBengine(int numassets, double *targetx, double *prices, double *shares);

int main(int argc, char **argv)
{
  int retcode = 0, numassets;
  double *targetx = NULL, *prices = NULL, *shares = NULL;
  
  if( argc != 2){
    printf("usage: rebalance filename\n"); retcode = 1; goto BACK;
  }

  retcode = readdata(argv[1], &numassets, &targetx,
	     &prices, &shares);
  if(retcode) goto BACK;

  printf("numassets: %d\n", numassets);

  retcode = RBengine(numassets, targetx, prices, shares);


 BACK:
  printf("\nexiting with retcode %d\n", retcode);
  return retcode;
}

int readdata(char *filename, int *pnumassets, 
	     double **ptargetx, double **pprices, double **pshares)
{
  int retcode = 0, j;
  FILE *input;
  char buffer[100];
  int numassets = 0;
  double *targetx = NULL, *prices = NULL, *shares = NULL;
  
  input = fopen(filename, "r");
  if(!input){
    printf("cannot read file %s\n", filename); retcode = 1; goto BACK;
  }
  fscanf(input,"%s", buffer);  
  numassets = atoi(buffer);  printf("  %d assets\n", numassets);

  targetx = (double *)calloc(3*numassets, sizeof(double));
  if(targetx == NULL){
    retcode = 1; goto BACK;
  }
  prices = targetx + numassets;
  shares = prices + numassets;

  for(j = 0; j < numassets; j++){
    fscanf(input,"%s", buffer); /** should be the value j **/
    fscanf(input,"%s", buffer); targetx[j] = atof(buffer);
    fscanf(input,"%s", buffer); prices[j] = atof(buffer);
    fscanf(input,"%s", buffer); shares[j] = atof(buffer); 
  } 

  *pnumassets = numassets;
  *ptargetx = targetx;
  *pprices = prices;
  *pshares = shares;
 BACK:
  return retcode;
}

