#include <iostream>
#include "bitmasks.hpp"
#include <ctime>
#include <vector>
#include <set>
using namespace std;


//void check()
//{
//    int N = 100;
//    int dist = 250;
//    for (int j = 0; j < 10; ++j)
//    {
//        int left1 = ((-2) * (rand() % 2) + 1) * (rand() % dist);
//        int right1 = left1 + (rand() % dist + 1);
//
//        int left2 = ((-2) * (rand() % 2) + 1) * (rand() % dist);
//        int right2 = left2 + (rand() % dist + 1);
//
//        vector<pair<int, int> > actions1;
//        vector<pair<int, int> > actions2;
//
//        myset a(left1, right1), b(left2, right2), u, inter;
//        set<int> s1, s2, unite, intersect;
//
////        cout << "left1 " << left1 << " right1 " << right1 << endl;
////        print(a);
////        cout << "left2 " << left2 << " right2 " << right2 << endl;
////        print(b);
//
//        for (int i = left1; i < right1; ++i)
//        {
//            s1.insert(i);
//        }
//        for (int i = left2; i < right2; ++i)
//        {
//            s2.insert(i);
//        }
////
//        for (int i = 0; i < N; ++i)
//        {
//            int act = rand() % 1;
//            int idx = left1 + rand() % (right1 - left1);
//
//            switch (act)
//            {
//                case 1:
//                    a.set(idx);
//                    s1.insert(idx);
//                    break;
//                case 0:
//                    a.erase(idx);
//                    s1.erase(idx);
//                    break;
//            }
////            cout << "act " << act << " idx " << idx << endl;
////            print(a);
////
//            actions1.push_back({act, idx});
//
//            auto m_it = a.begin();
//            auto it = s1.begin();
////            cout << "elements: \n";
//            for (; m_it != a.end() || it != s1.end(); ++m_it, ++it)
//            {
////                cout << *m_it << ' ' << *it << '\n';
//                if (*m_it != *it)
//                {
//                    cout << "does not work!";
//                    return;
//                }
//            }
//        }
////
//        for (int i = 0; i < N; ++i)
//        {
//            int act = rand() % 1;
//            int idx = left2 + rand() % (right2 - left2);
//
//            switch (act)
//            {
//                case 1:
//                    b.set(idx);
//                    s2.insert(idx);
//                    break;
//                case 0:
//                    b.erase(idx);
//                    s2.erase(idx);
//                    break;
//            }
//
//            actions2.push_back({act, idx});
//
//            auto m_it = b.begin();
//            auto it = s2.begin();
//            for (; m_it != b.end() || it != s2.end(); ++m_it, ++it)
//            {
//                if (*m_it != *it)
//                {
//                    cout << "does not work!";
//                    return;
//                }
//            }
//        }
//
//        unite = s1;
//        for (auto it : s2)
//        {
//            unite.insert(it);
//        }
//
//        u = a | b;
////        cout << "a : ";
////        print(a);
////        cout << "b : ";
////        print(b);
////        cout << "u : ";
////        print(u);
//
//        auto m_it = u.begin();
//        auto it = unite.begin();
//        for (; m_it != u.end() || it != unite.end(); ++m_it, ++it)
//        {
//            if (*m_it != *it)
//            {
//                cout << "does not work!";
//                return;
//            }
//        }
//
//
//        for (auto it2 : s2)
//        {
//            if (s1.find(it2) != s1.end())
//            {
//                intersect.insert(it2);
//            }
//        }
//
//        inter = a & b;
////        cout << "inter: ";
////        print(inter);
//        m_it = inter.begin();
//        it = intersect.begin();
//        for (; m_it != inter.end() || it != intersect.end(); ++m_it, ++it)
//        {
//            if (*m_it != *it)
//            {
//                cout << "does not work!";
//                return;
//            }
//        }
//
//
//
//    }
//}

int main()
{
    
    srand(time(NULL));
    
    int dist = 20;
    auto start = clock();
    
    int left1 = ((-2) * (rand() % 2) + 1) * (rand() % dist);
    int right1 = left1 + (rand() % dist + 1);
    
    int left2 = ((-2) * (rand() % 2) + 1) * (rand() % dist);
    int right2 = left2 + (rand() % dist + 1);
    
    myset a(left1, right1), b(left2, right2);
    
    cout << "a : ";
    for (auto it : a)
    {
        cout << it << ' ';
    }
    
    cout << "\nb : ";
    for (auto it : b)
    {
        cout << it << ' ';
    }
    cout << endl;
    
    int N = rand() % 10 + 1;
    
    cout << "do " << N << " actions with a\n";
    cout << endl;
    for (int i = 0; i < N; ++i)
    {
        int act = rand() % 1;
        int idx = left1 + rand() % (right1 - left1);

        switch (act)
        {
            case 1:
                cout << "a.set(" << idx << ")";
                a.set(idx);
                print(a);
                break;
            case 0:
                cout << "a.erase(" << idx << ")";
                a.erase(idx);
                print(a);
                break;
        }
    }
    
    N = rand() % 10 + 1;
    cout << "do " << N << " actions with b\n";
    cout << endl;
    for (int i = 0; i < N; ++i)
    {
        int act = rand() % 1;
        int idx = left2 + rand() % (right2 - left2);

        switch (act)
        {
            case 1:
                cout << "b.set(" << idx << ")";
                b.set(idx);
                print(b);
                break;
            case 0:
                cout << "b.erase(" << idx << ")";
                b.erase(idx);
                print(b);
                break;
        }
    }
    
    cout << endl;
    cout << endl;
    
    cout << "a : ";
    for (auto it : a)
    {
        cout << it << ' ';
    }
    cout << "\na.Min()\n";
    if (a.begin() != a.end())
    {
        cout << a.Min();
    }
    else
    {
        cout << "empty set";
    };
    cout << "\na.Max()\n";
    if (a.begin() != a.end())
    {
        cout << a.Max();
    }
    else
    {
        cout << "empty set";
    };
    cout << "\na.Left()\n";
    cout << a.Left();
    cout << "\na.Right()\n";
    cout << a.Right();
    
    int l = rand() % 10;
    int r = l + rand() % 10;
    
    cout << "\nchange_borders(a, " << l << ", " << r << ")\n";
    change_borders(a, l, r);
    cout << "a: ";
    for (auto it : a)
    {
        cout << it << ' ';
    }
    
    cout << "\nb : ";
    for (auto it : b)
    {
        cout << it << ' ';
    }
    cout << endl;
    
    myset u = a | b;
    
    cout << "a | b\n";
    for (auto it : u)
    {
        cout << it << ' ';
    }
    cout << endl;
    
    myset i = a & b;
    
    cout << "a & b\n";
    for (auto it : i)
    {
        cout << it << ' ';
    }
    cout << endl;
    
    cout << "time " << clock() - start << endl;
}
