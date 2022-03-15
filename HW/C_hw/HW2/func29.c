#include "heads.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 0.000000000000000000000000000001

int min_in_sequence(char * str){
  FILE * f;
  double x, min;
  int pos = 0, i = 0;
  f = fopen(str, "r");
  if (f == NULL) return -1;
  fscanf(f, "%lf", &min);
  i++;
  while(fscanf(f, "%lf", &x) == 1){
    if (x > min)
    {
    	i++;
    	continue;
    }
    else
    {
    	pos = i;
    	min = x;
    }
    i++;
  }
  fclose(f);
  return pos;
}
