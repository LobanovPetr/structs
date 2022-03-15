#include "heads.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 0.000000000000000000000000000001

int min_in_sequence(char * str){
  FILE * f;
  double pre, next;
  int i = 0;
  f = fopen(str, "r");
  if (f == NULL) return -1;
  fscanf(f, "%lf", &pre);
  while(fscanf(f, "%lf", &next) == 1)
  {
    if (next > pre)
      {
        i++;
      }
    pre = next;
  }
  return i;
}
