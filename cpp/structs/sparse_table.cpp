#include <iostream>
#include <vector>
#include <functional>
#include <utility>

using namespace std;

template<class key_t, class f_t = std::function<key_t(const key_t&, const key_t&)>>
class sparse_table
{
    vector<vector<key_t>> table;
    vector<int> bin_logs;
    f_t fun;
    public:
    sparse_table(const vector<key_t>& v, f_t fun=f_t()) : fun(fun)
    {
        int n = v.size();
        int tmp=1;
        bin_logs.resize(n+1);
        bin_logs[0]=-1;
        for (int i=1; i<=n; ++i)
        {
            if (i==tmp)
            {
                tmp<<=1;
                bin_logs[i]=bin_logs[i-1]+1;
            }
            else
            {
                bin_logs[i]=bin_logs[i-1];
            }
        }
        table.push_back(v);
        for (int t=2; t<=n; t<<=1)
        {
            int level= bin_logs[t];
            vector<key_t> tmp_level;
            for (int i=0; i+t<=n; ++i)
            {
                tmp_level.push_back(fun(table[level-1][i], table[level-1][i+(t>>1)]));
            }
            table.push_back(std::move(tmp_level));
        }
    }
    key_t query(int l, int r) // half_interval
    {
        if (l<0 || r>table[0].size() || r<=l)
        {
            std::cout<<"wrong boundaries"<<std::endl;
            return key_t();
        }
        int size=bin_logs[r-l];
        return fun(table[size][l], table[size][r-(1<<size)]);
    }
    key_t query2(int l, int s)
    {
        if (l+s<=table[0].size()) return query(l, l+s);
        return fun(query(l, table[0].size()), query(0, l+s-table[0].size()));
    }
    void dislay()
    {
        for (auto& it1: table)
        {
            for (auto& it2: it1)
            {
                std::cout<<it2<<" ";
            }
            std::cout<<std::endl;
        }
    }
    
};


void solve()
{
    int n; 
    cin>>n;
    vector<int> a(n);
    for (auto& it : a)
    cin>>it;
    sparse_table<int> t(a, [](const int& x_, const int& y_)
    {
        int x=x_, y=y_;
        while (y)
        {
            int t=y;
            y=x%y;
            x=t;
        }
        return x;
    });
    int res=t.query2(0,n);
    int ans=1;
    while (t.query2(0,ans)!=res)
    {
        ++ans;
    }
    for (int i=1; i<n; ++i)
    {
        while (t.query2(i,ans)!=res)
        ++ans;
    }
    cout<<ans-1<<endl;
}

int main()
{
    int t;
    cin>>t;
    for (int i=0; i<t; ++i)
    solve();
    return 0;
}
