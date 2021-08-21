#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <ctime>

using namespace std;

struct Forest
{
    std::vector<int> parents;
    std::vector<std::list<int> > lists;
    std::vector<int> ranks;
    int size;
    
    Forest(int s)
    {
        size = s;
        for (int i = 0; i < s; ++i)
        {
            make_class();
        }
    }
    
    void make_class()
    {
        int i = parents.size();
        parents.push_back(i);
        std::list<int> k;
        k.push_back(i);
        lists.push_back(k);
        ranks.push_back(1);
    }
    
    int find(int x)
    {
        if (x >= parents.size()) return -1;
        int tmp = x;
        while (parents[x] != x) {
            x = parents[x];
        }
        
        while (tmp != x)
        {
            int tmp2 = parents[tmp];
            parents[tmp] = x;
            tmp = tmp2;
        }
    
        return x;
    }
    
    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        
        if (x == y) return;
        size--;
        if (ranks[x] > ranks[y])
        {
            parents[y] = x;
        }
        else
        {
            parents[x] = y;
            if (ranks[x] == ranks[y])
            {
                ++ranks[y];
            }
        }
        
        lists[x].merge(std::move(lists[y]));
    }
};

int test(Forest &f, int size)
{
    int command;
    
    for (int i = 0 ; i < size; ++i)
    {
        command = rand() % 3;
        
        switch (command)
        {
//            case 0:
//                std::cout << "make class" << std::endl;
//                f.make_class();
//                ++size;
//                break;
            case 1:
            {
                int to_find = rand() % size;
//                std::cout << "find main of " << to_find << std::endl;
//                std::cout << "it is " << f.find(to_find) << std::endl;
                break;
            }
                
            case 2:
            {
                int x = rand() % size;
                int y = rand() % size;
//                std::cout << "unite " << x << " with " << y << std::endl;
                f.unite(x, y);
                break;
            }
        }
    }
    
    return 1;
}

int main()
{
    int n, m1, m2, tmp1, tmp2;

    cin >> n >> m1 >> m2;

    Forest f1(n), f2(n);

    for (int i = 0; i < m1; ++i)
    {
        cin >> tmp1 >> tmp2;
        f1.unite(tmp1 - 1, tmp2 - 1);
    }

    for (int i = 0; i < m2; ++i)
    {
        cin >> tmp1 >> tmp2;
        f2.unite(tmp1 - 1, tmp2 - 1);
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (j == i)
            {
                continue;
            }
            if (f1.find(i) != f1.find(j) && f2.find(i) != f2.find(j))
            {
                f1.unite(i, j);
                f2.unite(i, j);
                cout << i << ' ' << j << endl;
            }
        }
    }
    
    return 0;
}
