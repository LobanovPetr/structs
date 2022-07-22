#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

void solve()
{
    int n, s, f;
    cin >> n >> s >> f;
    f--;
    vector<int> dist(n, INT_MAX);
    vector<int> used(n, false);
    dist[--s] = 0;
    
    vector<vector<int> > edjency(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> edjency[i][j];
        }
    }
    
    for (int i = 0; i < n; ++i)
    {
        int MIN = INT_MAX;
        int vertex = -1;
        for (int j = 0; j < n; ++j)
        {
            if ((dist[j] < MIN) && (!used[j]))
            {
                MIN = dist[j];
                vertex = j;
            }
        }
        if (vertex == -1)
        {
            break;
        }
        used[vertex] = true;
        for (int j = 0; j < n; ++j)
        {
            if ((vertex != j) && (edjency[vertex][j] != -1))
            {
                dist[j] = min(dist[j], dist[vertex] + edjency[vertex][j]);
            }
        }
    }
    cout << ((dist[f] == INT_MAX)?-1:dist[f]) << '\n';
    
}

int main()
{
    solve();
}

