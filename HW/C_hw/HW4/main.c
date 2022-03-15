#include "head.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char s[128];
	printf("Enter the name of file\n");
	scanf("%s", s);
	FILE *f = fopen(s, "r");
	if (f == NULL) return -1;
	int size1, size2; 
	fscanf(f, "%d" , &size1);
	double * a = (double *)malloc(sizeof(double) * size1);
	double * p;

	for (p = a; p < a + size1; p++)
	{
		fscanf(f, "%lf", p);
	}

	fscanf(f, "%d", &size2);
	double * b = (double *)malloc(sizeof(double) * size2);

	for(p = b; p < b + size2; p++)
	{
		fscanf(f, "%lf", p);
	}

	double * c = concat(a, size1, b, size2);

	for(p = c; p < c + size2 + size1; p++)
	{
		printf("%.2lf ", *p);
	}
	printf("\n");
	fclose(f);
	free(a);
	free(b);
	free(c);
	return 0;
}
