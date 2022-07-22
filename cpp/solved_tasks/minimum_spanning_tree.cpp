#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

//vector<pair<int, int> > rle(const string & s)
//{
//    vector <pair<int, int> > tmp; // first - char code, second - number
//    for (int i = 0; i < s.size(); ++i)
//    {
//        int j = i + 1;
//        while (j < s.size() && s[j] == s[i]) ++j;
//        tmp.push_back({s[i] - 'a', j - i});
//        i = j - 1;
//    }
//
//    return tmp;
//}

template<typename T, typename B>
ostream& operator<< (std::ostream& out, const pair<T, B> & p)
{
    out << "{" << p.first << ", " << p.second << "}";
    return out;
}

struct union_find
{
    vector<size_t> parents;
    vector<size_t> ranks;
    size_t size;
    
    union_find(): parents(), ranks(), size(0){};
    union_find(size_t size_): parents(size_), ranks(size_, 0), size(size_)
    {
        for (size_t i = 0; i < size; ++i)
        {
            parents[i] = i;
        }
    }
    void add_new()
    {
        parents.push_back(size);
        ranks.push_back(0);
        size++;
    }
    size_t get(size_t x)
    {
        if (x >= size)
        {
            throw;
        }
        vector<size_t> idx;
        while(parents[x] != x)
        {
            idx.push_back(x);
            x = parents[x];
        }
        
        for (auto &it : idx)
        {
            parents[it] = x;
        }
        
        return x;
    }
    void join(size_t x, size_t y)
    {
        if ( (x = get(x)) ==  (y = get(y)))
        {
            return;
        }
        if (ranks[x] > ranks[y]) // rank[x] < rank[y]
        {
            swap(x, y);
        }
        parents[x] = y;
        if (ranks[x] == ranks[y])
        {
            ranks[y]++;
        }
    }
};


struct bin_heap
{
    int i;
    vector<pair<int, pair<int, int> > > v;
    
    bin_heap(int n)
    {
        i = 0;
        v.resize(n, pair<int, pair<int, int> >());
    }
 
    void insert(pair<int, pair<int, int> > x)
    {
        int j = i;
        v[i++] = x;
        while (j > 0 && v[(j - 1) / 2] > v[j])
        {
            swap(v[(j - 1) / 2], v[j]);
            j = (j - 1) / 2;
        }
    }
 
    pair<int, pair<int, int> > remove_min()
    {
        if (i == 0)
        {
            return {-1, {-1, -1}};
        }
 
        pair<int, pair<int, int> > res = v[0];
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



void solve()
{
    int n, m;
    cin >> n >> m;
    int b, e, w;
    size_t ans = 0;
    
    union_find T(n);
    bin_heap H(m);
    
    for (int i = 0; i < m; ++i)
    {
        cin >> b >> e >> w;
        H.insert({w, {b, e}});
    }
    
    
    for (int i = 0; i < m; ++i)
    {
        auto t = H.remove_min();
//        cout << "weight " << t.first << " (" << t.second.first << ", " << t.second.second << ")\n";
        if (T.get(t.second.first - 1) != T.get(t.second.second - 1))
        {
            ans += t.first;
            T.join(t.second.first - 1, t.second.second - 1);
        }
    }
    cout << ans << endl;
    
}

int main()
{
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    solve();
    
    solve();
}

