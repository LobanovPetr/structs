#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <map>
#include <climits>
#include <ctime>

using namespace std;

int N = 100;
int M = 10;
int ANS = 0;

int cheker(vector<int>& a, vector<int> & b)
{
    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < b.size(); ++j)
        {
            if (a[i] == b[j])
            {
                return 1;
            }
        }
    }
    return 0;
}

vector<int> merge_sort(vector<int> & a, int l, int r)
{
    int m = (l + r) / 2;
    vector<int> res;
    
    if (r - l == 1)
    {
        res = {a[l]};
        return res;
    }
    auto left = merge_sort(a, l, m + 1);
    auto right = merge_sort(a, m + 1, r);
    
    res.resize(left.size() + right.size());
    
    auto first = left.begin();
    auto second = right.begin();
    auto iter = res.begin();
    
    for (; first != left.end() && second != right.end();)
    {
        if (*first < *second)
        {
            *iter = *first;
        }
        else
        {
            *iter = *second;
            ANS += (left.end() - first);
        }
        ++iter;
    }
    
    for (; first != left.end(); ++first, ++iter)
    {
        *iter = *first;
    }
    for (; second != right.end(); ++second, ++iter)
    {
        *iter = *second;
    }
    return res;
}

void solve()
{
    vector<int> a;
    int n = rand() % N + 1;
    a.resize(n);
    int count = 0;
    for (auto & it : a)
    {
        it = count++;
    }
    for (int i = n - 1; i > -1; --i)
    {
        swap(a[i], a[rand() % (i + 1)]);
    }
    
    cout << "a: ";
    for (const auto & it : a)
    {
        cout << it << ' ';
    }
    cout << "\n";
    
    a = merge_sort(a, 0, a.size());
    
    cout << "a: ";
    for (const auto & it : a)
    {
        cout << it << ' ';
    }
    cout << "\n";
    
}

int main()
{
    solve();
    return 0;
}

