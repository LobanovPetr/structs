#include "head.h"
#include <stdio.h>
#include <stdlib.h>

void change(double * m, int size)
{
	double min1 = m[0];
	double min2 = m[1];

	if (min1 > min2)
	{
		double k = min1;
		min1 = min2;
		min2 = k;
	}
	for(double * p = m; p < m + size; p++)
	{
		if (*p < min1)
		{
			min2 = min1;
			min1 = *p;
		}
		if (min1 < *p && *p < min2)
		{
			min2 = *p;
		}
	}
	for(double * p = m; p < m + size; p++)
	{
		if(*p > min1)
		{
			continue;
		}
		else
		{
			*p = min2;
		}
	}
}

void out_arr(double * m, int size)
{
	FILE * f = fopen("ans.txt", "w+");
	for(double *p = m; p < m + size; p++)
		fprintf(f, "%lf ", *p);
}

void FindSize(FILE *f, int * size)
{
	int i = 0;
	double a;
	while(fscanf(f, "%lf", &a) == 1)
		i++;
	*size = i;
	rewind(f);
}
