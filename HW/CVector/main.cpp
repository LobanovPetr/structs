#include<iostream>
#include "CVector.hpp"
#include<ctime>

int main()
{
    srand(time(NULL));
    int size = rand() % 10;
    std::cout << "size is " << size << std::endl;
    CVector a;
    CVector b;
    CVector t;
    CVector tmp;


    for (int i = 0; i < size; ++i)
    {
        a.push_back(100.0 + rand() % 100 + float(rand() % 100) / 1000 );
        b.push_back(100.0 + rand() % 100 + float(rand() % 100) / 1000 );
    }

    std::cout << "first array" << std::endl;
    a.print();
    std::cout << "second array" << std::endl;
    b.print();

    std::cout << "product: ";
    std::cout << a * b << std::endl;
    t = a + b;
    std::cout << "sum:" << std::endl;
    t.print();

    int k = rand() % 10;

    std::cout << "add "<< k << " numbers at the end of sum" << std::endl;

    for (int i = 0; i < k; ++i)
    {
        t.push_back(rand() % 20);
    }
    t.print();

    k = rand() % 30;
    std::cout << "delete "<< k <<" elemets form the end" << std::endl;
    for (int i = 0; i < k; ++i)
    {
        t.pop_back();
    }
    t.print();
    
    CVector m;
    
    
    std::cout << "\nexample of use []\nm = ";
    m.print();
    std::cout << "m[10] = 5\n";
    m[10] = 5;
    
    
    
    std::cout << "m = ";
    for (int i = 0; i < m.len(); ++i)
    {
        std::cout << m[i] << ' ';
    }
    std::cout << std::endl;
    
    double c = m[12];
    std::cout << "c = m[12]\n";
    std::cout << "c = "<< c << std::endl;
    std::cout << "m = ";
    m.print();
    
//    const double c = a[1000];
//
//    std::cout << a.len() << std::endl;
//
//    std::cout << c << std::endl;
//
//
//    std::cout << '\n';
    return 0;
}
