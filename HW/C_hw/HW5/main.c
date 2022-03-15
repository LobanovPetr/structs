#include <stdlib.h>
#include <stdio.h>
#include "head.h"

int main(void)
{
	char str[128];
	char check;
	int size;
	int code;
	int n;
	int * m;
	FILE * f;

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
	scanf("%s", str);
	f = fopen(str, "r");
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

	m = (int *)malloc(sizeof(int) * size);
	for(int * p = m; p < m + size; p++)
	{
		fscanf(f, "%d", p);
	}

	n = fun(m, size);

	printf("New array\n");
	for(int * p = m; p < m + n; p++)
	{
		printf("%d ", *p);
	}
	printf("\nNew size\n");
	printf("%d\n", n);
	PrintToFile(m, n);
	free(m);
	fclose(f);
	printf("You can check answer in file named \"ans.txt\"\n");
}
