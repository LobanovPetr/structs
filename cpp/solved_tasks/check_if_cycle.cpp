#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

/*
 Check if there are cycles.
 */

void solve()
{
    int n, m, v1, v2, tmp;
    cin >> n;
    
    vector<vector<int> > graph(n, vector<int>());
    vector<int> used(n, 0);
    vector<int> STK;
    vector<int> vertex_in_stack(n, 0);
    
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> tmp;
            if (tmp > 0)
            {
                graph[i].push_back(j);
            }
        }
    }
    
    for (int i = 0; i < n; ++i) // through component of connection
    {
        if(!used[i])
        {
            STK.push_back(i);
            vertex_in_stack[i] = 1;
            used[i] = 1;
            while(STK.size())
            {
                label:
                for (auto it : graph[STK.back()])
                {
                    if (vertex_in_stack[it])
                    {
                        cout << 1 << endl;
                        return;
                    }
                    if (!used[it])
                    {
                        STK.push_back(it);
                        used[it] = 1;
                        vertex_in_stack[it] = 1;
                        goto label;
                    }
                }
                vertex_in_stack[STK.back()] = 0;
                STK.pop_back();
            }
        }
    }
    cout << 0 << endl;
    return;
}

int main()
{
    solve();
}

