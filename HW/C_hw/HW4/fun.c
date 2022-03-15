#include "head.h"
#include <stdio.h>
#include <stdlib.h>

double * concat(double * m1, int size1, double * m2, int size2)
{
	double * m3 = (double *)malloc(sizeof(double) * (size1 + size2));
	int k = 0, l1 = 0, l2 = 0;
	for(; k < size1 + size2; k++)
	{
		if (l1 == size1)
		{
			for(; k < size1 + size2; k++)
			{
				m3[k] = m2[l2];
				l2++;
			}
			break;
		}
		if (l2 == size2)
		{
			for(; k < size1 + size2; k++)
			{
				m3[k] = m1[l1];
				l1++;
			}
			break;
		}
		if (m1[l1] > m2[l2])
		{
			m3[k] = m2[l2];
			l2++;
		}
		else
		{
			m3[k] = m1[l1];
			l1++;
		}
	}
	return m3;
}
