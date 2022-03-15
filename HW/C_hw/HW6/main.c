#include "head.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char s[128];
	char check;
	int size;
	int code;
	FILE * f;
	double * m;

	printf("How do you want to input the data?\n");
	printf("Enter '1' if the first number in the file is length of array.\n");
	printf("Otherwise, enter '2'.\n");

	scanf("%c", &check);
	if (check != '1' && check != '2')
	{
		printf("Your input is wrong\n");
		return -1;
	}

	printf("Enter the name of file\n");
	scanf("%s", s);

	f = fopen(s, "r");
	if (f == NULL) 
	{
		printf("Empty file\n");
		return -1;
	}

	if(check == '1')
	{
		code = fscanf(f, "%d", &size);
		if (code == 0)
		{
			printf("Incorrect size\n");
			return 0;
		}
	}
	else
		FindSize(f, &size);

	m = (double *)malloc(sizeof(double) * size);

	for(double * p = m; p < m + size; p++)
	{
		fscanf(f, "%lf", p);
	}

	change(m, size);
	printf("New array\n");
	for (double * p = m; p < m + size; p++)
	{
		printf("%lf ", *p);
	}
	printf("\n");
	out_arr(m, size);
	free(m);
	fclose(f);
	printf("You can check answer in file named \"ans.txt\"\n");
}
