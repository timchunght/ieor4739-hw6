
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tim.h"

int main(int argc, char **argv)
{
  
  printf("hello, tim\n");
  // caller();
  int N = 1000;
  int T = 10;
  double alpha = 0.001;

  tim_orchestrator(N, T, alpha, "deterministic"); 
  return 0;
}




