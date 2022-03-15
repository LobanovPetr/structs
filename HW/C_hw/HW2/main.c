#include <stdio.h>
#include "heads.h"

int main()
{
	char str[256];
  	printf("Enter the name of file\n");
  	scanf("%s", str);
	printf("%d\n", min_in_sequence(str));
	return 0;
}
