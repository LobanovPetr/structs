// BTree pointers to char *
#include <iostream>
#include <set>
#include <ctime>
#include "B_tree.hpp"

std::string generate_random_string(size_t size)
{
    std::string toReturn;
    for (size_t i = 0; i < size; ++i)
    {
        toReturn.push_back((rand() % 10) + '0');
    }
    return toReturn;
}

int main()
{
    srand(time(NULL));
    size_t N = 15;
    size_t strSize = 2;
    BTree tr(2);
    BNode * x;
    std::string ar[15];
    size_t idx;
    
    for (size_t i = 0; i < N; ++i)
    {
        ar[i] = generate_random_string(strSize);
    }
    
    printf("insert\n");
    for (size_t i = 0; i < N; ++i)
    {
        if (rand() % 2)
        {
            std::cout << ar[i] << '\n';
            tr.insert(ar[i].c_str());
        }
    }
    
    std::cout << "\ntree size " << tr.size();
    std::cout << "\niterator\n";
    for (auto it = tr.begin(); it != tr.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    
    std::cout << "\nback iterator\n";
    for (auto it = tr.rbegin(); it != tr.rend(); --it)
    {
        std::cout << *it << ' ';
    }
    std::cout << "\n\n";
    
    for (size_t i = 0; i < N; ++i)
    {
        if (rand() % 2)
        {
            idx = rand() % N;
            std::cout << "\nerase "<< ar[idx] << '\n';
            tr.remove(ar[idx].c_str());
            
            std::cout << "\ntree size " << tr.size();
            std::cout << "\niterator\n";
            for (auto it = tr.begin(); it != tr.end(); ++it)
            {
                std::cout << *it << ' ';
            }
            
            std::cout << "\nback iterator\n";
            for (auto it = tr.rbegin(); it != tr.rend(); --it)
            {
                std::cout << *it << ' ';
            }
            
            std::cout << "\n\nstruct\n";
            tr.print_struct();
            std::cout << "\n\n";
            continue;
        }
        idx = rand() % N;
        std::cout << "\ninsert " << ar[idx] << '\n';
        tr.insert(ar[idx].c_str());
        
        std::cout << "\ntree size " << tr.size();
        std::cout << "\niterator\n";
        for (auto it = tr.begin(); it != tr.end(); ++it)
        {
            std::cout << *it << ' ';
        }
        
        std::cout << "\nback iterator\n";
        for (auto it = tr.rbegin(); it != tr.rend(); --it)
        {
            std::cout << *it << ' ';
        }
        
        std::cout << "\n\nstruct\n";
        tr.print_struct();
        std::cout << "\n\n";
        
    }
    tr.clear();
    N = 1000;
    
    size_t tm;
    
    for (int i = 0; i < 4; ++i)
    {
        N *= 10;
        std::vector<std::string> a(N);
        for (size_t i = 0; i < N; ++i)
        {
            a[i] = generate_random_string(strSize);
        }
        std::cout << std::endl << "insert and erase "<< N << " elements" << std::endl;
        
        for (size_t i = 0; i < N/4; ++i)
        {
            tr.insert(a[i].c_str());
        }
        
        std::cout << "We have already inserted " << N / 4 << " elements." << "\nInsert " << N/2 << " elements.\n";
        tm = clock();
        for (size_t i = N/4; i < (3 * N)/4; ++i)
        {
            tr.insert(a[i].c_str());
        }
        printf("%f\n", (double)(clock() - tm) / CLOCKS_PER_SEC);
        
        std::cout << "erase " << N / 4 << " elements.\n";
        tm = clock();
        for (size_t i = 0; i < N/4; ++i)
        {
            tr.remove(a[i].c_str());
        }
        printf("%f\n", (double)(clock() - tm) / CLOCKS_PER_SEC);
        
        std::cout << "remove left elements.\n";
        
        tm = clock();
        for (size_t i = N/4; i < (3 * N)/4; ++i)
        {
            tr.remove(a[i].c_str());
        }
        
        printf("%f\n", (double)(clock() - tm) / CLOCKS_PER_SEC);
    }
    
    return 0;
}
