#include<iostream>

using namespace std;


const int n = 10;
int t[n] = {0};
int a[n] = {0, 1, 2, 3, 4, 5, 6, 7, 9, 10};

int p(int x)
{
	return (x & (x + 1));
}

int sum(int r)
{
	int res = 0;
	r = r - 1;

	while(r >= 0)
	{
		res += t[r];
		r = p(r) - 1;
	}
	return res;
}

int sum(int l, int r)
{
	return sum(r) - sum(l);
}

void inc(int i, int v)
{
	int j = i;
	while (j < n)
	{
		t[j]+= v;
		j = (j | (j + 1));
	}
}



int main()
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = p(i); j <= i; ++j)
		{
			t[i] += a[j];
		}
	}
	for (int i = 0; i < n; ++i)
	{
		cout << a[i] << ' ';
	}
	cout << endl;

	cout << sum(0, 6) << endl;
	inc(5, 10);
	cout << sum(8, 9) << endl;

}