#include <stdio.h>
#include "heads.h"

#define N 250000

int main()
{
	char str[256];
 	printf("Enter the name of file\n");
	scanf("%s", str);
	printf("%d\n",find_quantity_between_first_and_second(str));
	return 0;
}