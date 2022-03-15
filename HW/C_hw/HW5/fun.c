#include "head.h"
#include <stdio.h>
#include <stdlib.h>

int fun(int * m, int size)
{
	int i;
	int k = 0;
	for(i = 0; i < size; i++)
	{
		if (m[i] % 2 != 0)
		{
			m[k] = m[i];
			k++;
		}
	}
	for(i = k; i < size; i++)
	{
		m[i] = 0;
	}
	return k;
}

void PrintToFile(int * m, int size)
{
	FILE *f = fopen("ans.txt", "w+");
	for(int *p = m; p < m + size; p++)
		fprintf(f, "%d ", *p);
}

void FindSize(FILE *f, int * size)
{
	int i = 0;
	int a;
	while(fscanf(f, "%d", &a) == 1)
		i++;
	*size = i;
	rewind(f);
}
