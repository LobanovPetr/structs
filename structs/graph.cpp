#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<stack>

using namespace std;

struct graph
{
	unordered_map<int, unordered_set<int> > E;

	graph(int m)
	{
		int v1, v2;
		for (int i = 0; i < m; ++i)
		{
			cin >> v1 >> v2;
			E[v1].insert(v2);
		}
	}


	bool find_cycle()
	{
		unordered_set<int> visited;

		for(const auto &a : E)
		{
			if (visited.find(a.first) != visited.end())
			{
				continue;
			}
			stack<int> stk;
			unordered_set<int> tmp;
			visited.insert(a.first);
			stk.push(a.first);
			tmp.insert(a.first);
			while(!stk.empty())
			{
				label:
				for (const auto &it : E[stk.top()])
				{
					if (tmp.find(it) != tmp.end())
					{
						return true;
					}
					if (visited.find(it) != visited.end())
					{
						continue;
					}
					stk.push(it);
					tmp.insert(it);
					visited.insert(it);
					goto label;
				}
				tmp.erase(stk.top());
				stk.pop();

			}
		}
		return false;
	}


};

int main()
{
	graph g(5);
	std::cout << "start looking for cycles" << std::endl;
	std::cout << g.find_cycle() << std::endl;

}