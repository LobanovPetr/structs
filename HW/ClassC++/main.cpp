// class of fractions
#include "CRat.hpp"
#include <cstdio>

// N = 5;
int main()
{
    CRat v;
    char filename[256];
    FILE *f;
    int num, den;
    char action;
    fraction ar[N];
    fraction ar_[N];
    CRat v1, v2, v3;
    
    std::cout << "print test file\n";
    std::cin >> filename;
    
    try
    {
        f = fopen(filename, "r");
        if (f == NULL)
        {
            throw -1;
        }
        
        for (int i = 0; i < N; ++i)
        {
            if (!fscanf(f, "%d/%d", &num, &den))
            {
                throw -2;
            }
            ar[i] = fraction(num, den);
        }
        if (!fscanf(f, "\n%c", &action))
        {
            throw -2;
        }
        
        for (int i = 0; i < N; ++i)
        {
            if (!fscanf(f, "%d/%d", &num, &den))
            {
                throw -2;
            }
            ar_[i] = fraction(num, den);
        }
        
        v1 = CRat(ar);
        v2 = CRat(ar_);
        
        switch (action)
        {
            case '+':
                v3 = v1 + v2;
                break;
            case '-':
                v3 = v1 - v2;
                break;
            default:
                throw -2;
                break;
        }
        fclose(f);
        
    } catch (int a)
    {
        if (a == -1)
        {
            std::cerr << "incorrect file name\n";
            return -1;
        }
        fclose(f);
        std::cerr << "incorrect data\n";
        return -1;
    }
    
    
    
    v1.print();
    v2.print();
    
    std::cout << action << std::endl;
    v3.print();
    return 0;
}
