#include<vector>

struct bin_heap
{
	int i;
	vector<int> v;
 
	bin_heap(int n)
	{
		i = 0;
		v.resize(n);
	}
 
	void insert(int x)
	{
		int j = i;
		v[i++] = x;
		while (j > 0 && v[(j - 1) / 2] > v[j])
		{
			swap(v[(j - 1) / 2], v[j]);
			j = (j - 1) / 2;
		}
	}
 
	int remove_min()
	{
		if (i == 0)
		{
			return -1;
		}
 
		int res = v[0];
		v[0] = v[--i];
		int j = 0;
		int m;
 
		while (true)
		{
			m = j;
			if (2 * j + 1 < i && v[2 * j + 1] < v[m])
			{
				m = 2 * j + 1;
			}
			if (2 * j + 2 < i && v[2 * j + 2] < v[m])
			{
				m = 2 * j + 2;
			}
			if ( m == j)
			{
				return res;
			}
			else
			{
				swap(v[j], v[m]);
				j = m;
			}
		}
	}
};

