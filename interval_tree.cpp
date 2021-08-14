#include<iostream>
#include<vector>
#include<functional>
#include<utility>
using namespace std;

template <typename T>
class interval_tree
{
	std::vector<T> V;
	T (*fun)(const T&x, const T&y);
	int size;
public:
	interval_tree(const std::vector<T> & v, T fun_(const T&x_, const T&y_))
	{
		int n = v.size();
		fun = fun_;
		size = 1;
		for (; size < n; size *= 2){}

		V.resize(2 * size - 1, 0);
		for (int i = 0; i < n; ++i)
		{
			set(i, v[i]);
		}
	}

private:
	T query_(int l, int r, int lx, int rx , int x)
	{
		int m;
		if (lx >= r || rx <= l)
		{
			return T();
		}
		if (lx >= l && rx <= r)
		{
			return V[x];
		}
		m = (lx + rx) / 2;
		T tmp1 = query_(l, r, lx, m, 2 * x + 1);
		T tmp2 = query_(l, r, m, rx, 2 * x + 2);
		return fun(tmp1, tmp2);
	}
public:
	T query(int l, int r)
	{
		return query_(l + size - 1, r + size - 1, size - 1, 2 * size - 1, 0);
	}

	void set(int idx, T val)
	{
		idx += size - 1;
		V[idx] = val;
		while (idx != 0)
		{
			idx = (idx - 1) / 2;
			V[idx] = fun(V[idx * 2 + 1], V[idx * 2 + 2]); 
		}
	}

	void display()
	{
		for (int i = size - 1; i < 2 * size - 1; ++i)
		{
			std::cout << V[i] << ' ';
		}
		std::cout << std::endl;
	}
};

int sum(const int &x = 0, const int &y = 0)
{
	return x + y;
}

int gcd(const int &a, const int &b)
{
	return (b == 0) ? a : gcd(b, a%b);
}

int main()
{
	std::vector<int> a(10, 1);

	// interval_tree<int> t(a, sum);
	// t.display();

	// std::cout << t.query(0, 6) << std::endl;
	// t.display();
	// t.set(0, 10);
	// t.display();
	// std::cout << t.query(0, 6) << std::endl;

	interval_tree<int> t(a, gcd);
	t.set(0, 5);
	t.set(1, 15);
	t.set(2, 16);
	t.set(3, 8);
	t.display();

	std::cout << t.query(0, 2) << std::endl;
	std::cout << t.query(2, 4) << std::endl;
	
}

