#include <stdio.h>
#include "heads.h"

int find_quantity_between_first_and_second(char *str){
	double x, y, z;
	int n;
	FILE *f;
	n = 0;
	f = fopen(str, "r");
	if (f == NULL) return -1;
	fscanf(f, "%lf%lf", &x, &y);
	z = (x > y)? x : y;
	x = (y > x)? x : y;// x - min
	y = z;// y - max
	while(fscanf(f, "%lf", &z)== 1){
		n += (y > z  && z > x) ? 1 : 0;
	}
	fclose(f);
	return n;
}
