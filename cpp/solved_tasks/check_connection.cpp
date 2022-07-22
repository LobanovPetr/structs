#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

/*
 Check if gruph is connected.
 */

void solve()
{
    int n, m, v1, v2;
    cin >> n >> m;
    
    vector<vector<int> > graph(n, vector<int>());
    vector<int> used(n, 0);
    vector<int> STK;
    
    for (int i = 0; i < m; ++i)
    {
        cin >> v1 >> v2;
        graph[--v1].push_back(--v2);
        graph[v2].push_back(v1);
        if (i == 0)
        {
            STK.push_back(v1);
            used[v1] = 1;
        }
    }
    
    while(STK.size())
    {
        label:
        for (auto it : graph[STK.back()])
        {
            if (!used[it])
            {
                STK.push_back(it);
                used[it] = 1;
                goto label;
            }
        }
        STK.pop_back();
    }
    
    for (auto it : used)
    {
        if (it == 0)
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    return;
}

int main()
{
    solve();
}

