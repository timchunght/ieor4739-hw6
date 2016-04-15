
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gurobi_c.h>

int RBengine(int numassets, double *targetx, double *prices, double *shares)
{
  int retcode = 0, j, n;
  double value;

  GRBenv   *env = NULL;
  GRBmodel *model = NULL;
  char **names, bigname[100];
  double *x, *obj, *ub, *lb, *cval, rhs;
  int *cind, i;
  

  value = 0;
  for(j = 0; j < numassets; j++)
    value += prices[j]*shares[j];

  printf("Portfolio value: %g\n", value);

  for(j = 0; j < numassets; j++)
    printf("asset %4d at weight %.6f target %.6f\n",
	   j, prices[j]*shares[j]/value, targetx[j]);


  retcode = GRBloadenv(&env, "engine.log");
  if (retcode) goto BACK;

  n = 2*numassets; /* total number of variables **/

  /* Create initial model */
  retcode = GRBnewmodel(env, &model, "factors", n,
			NULL, NULL, NULL, NULL, NULL);
  if (retcode) goto BACK;

  names = (char **) calloc(n, sizeof(char *));
  x = (double *)calloc(4*n, sizeof(double));
  if(!names || !x){
    printf("no memory\n"); retcode = 1; goto BACK;
  }
  obj = x + n;
  ub = obj + n;
  lb = ub + n;
  for(j = 0; j < n; j++){
    names[j] = (char *)calloc(10, sizeof(char));
    if(names[j] == NULL){
      retcode = 1; goto BACK;
    }
    if(j < numassets)
      sprintf(names[j],"d%dplus", j);
    else
      sprintf(names[j],"d%dminus", j - numassets);

    if( j < numassets){
      ub[j] = 1e10; /** overkill **/
      obj[j] = prices[j];
    }
    else{
      ub[j] = shares[j - numassets];
      obj[j] = prices[j - numassets];
    }
  }
  
  /* initialize variables */
  for(j = 0; j < n; j++){
    retcode = GRBsetstrattrelement(model, "VarName", j, names[j]);
    if (retcode) goto BACK;

    retcode = GRBsetdblattrelement(model, "Obj", j, obj[j]);
    if (retcode) goto BACK;

    retcode = GRBsetdblattrelement(model, "LB", j, lb[j]);
    if (retcode) goto BACK;

    retcode = GRBsetdblattrelement(model, "UB", j, ub[j]);
    if (retcode) goto BACK;

  }

  retcode = GRBupdatemodel(model);
  if (retcode) goto BACK;

  /** add constraints **/

  cind = (int *) calloc(n, sizeof(int));
  cval = (double *) calloc(n, sizeof(double));
  if(!cind || !cval){
    printf("no memory\n"); retcode = 1; goto BACK;
  }


  for(j = 0; j < numassets; j++){
    /** constraint 1a for asset j **/
    rhs = 0;
    sprintf(bigname,"1a_%d",j);
    for (i = 0; i < numassets; i++){
      if(i != j){
	cval[i] = -targetx[j]*prices[i];
	cval[i + numassets] = targetx[j]*prices[i];
	rhs += targetx[j]*prices[i]*shares[i];
      }
      else{
	cval[j] = prices[j]*(1 - targetx[j]);
	cval[j + numassets] = -prices[j]*(1 - targetx[j]);
	rhs += targetx[j]*prices[i]*shares[i] - prices[j]*shares[j];
      }
      cind[i] = i;
      cind[i + numassets] = i + numassets;
    }
    retcode = GRBaddconstr(model, 2*numassets, cind, cval, GRB_EQUAL, rhs, bigname);
    if (retcode) goto BACK;

  }

  retcode = GRBupdatemodel(model);
  if (retcode) goto BACK;


  /** optional: write the problem **/

  retcode = GRBwrite(model, "rebalance.lp");
  if (retcode) goto BACK;
  
 BACK:  
  return retcode;
}


  
