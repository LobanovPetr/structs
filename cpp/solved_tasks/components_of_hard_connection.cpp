#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

/*
 Find componenst of hard connetion.
 */

void solve()
{
    int n, m, v1, v2, tmp;
    cin >> n >> m;
    
    vector<vector<int> > graph(n, vector<int>());
    vector<vector<int> > back_graph(n, vector<int>());
    vector<int> vertex_to_component(n, 0);
    vector<int> dfs_exit;
    
    vector<int> used(n, 0);
    vector<int> STK;
    
    for (int i = 0; i < m; ++i)
    {
        cin >> v1 >> v2;
        graph[--v1].push_back(--v2);
        back_graph[v2].push_back(v1);
    }
    
    for (int i = 0; i < n; ++i)
    {
        if (used[i])
        {
            continue;
        }
        STK.push_back(i);
        used[i] = 1;
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
            dfs_exit.push_back(STK.back());
            STK.pop_back();
        }
    }
    used.assign(n, 0);
    
    int cur_component = 0;
    for (auto it = dfs_exit.rbegin(); it != dfs_exit.rend(); ++it)
    {
        if (!used[*it])
        {
            cur_component++;
            STK.push_back(*it);
            used[*it] = 1;
            vertex_to_component[*it] = cur_component;
            while(STK.size())
            {
                label1:
                for (auto it1 : back_graph[STK.back()])
                {
                    if (!used[it1])
                    {
                        STK.push_back(it1);
                        used[it1] = 1;
                        vertex_to_component[it1] = cur_component;
                        goto label1;
                    }
                }
                STK.pop_back();
            }
        }
    }
    
    cout << *max_element(vertex_to_component.begin(), vertex_to_component.end());
    cout << endl;
    
    for (auto it : vertex_to_component)
    {
        cout << it << ' ';
    }
    cout << endl;
    
    return;
}

int main()
{
    solve();
}

