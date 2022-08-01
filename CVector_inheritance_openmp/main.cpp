#include <iostream>
#include <omp.h>
#include "CVector0.hpp"
#include "CVector1.hpp"
#include <chrono>
#define N 10000    // max len of vector
#define dist 100  // max value
#define V 1000    // num of vectors
#define thr 4   // num of threads

void genVectors(std::string, int n);
char a[2][32] = {{"2.txt\0"}, {"3.txt\0"}};

void genVectors(std::string FileName, int n)
{
    std::ofstream out(FileName);
    int type;
    int file;
    int size;
    for (int i = 0; i < n; ++i)
    {
        type = rand() % 2;
        file = rand() % 2;
        size = rand() % N + 1;
        out << type << ' ' << a[file] << ' ' << size << ' ';
        for (int i = 0; i < size; ++i)
            out << rand() % dist << ' ';
        out << '\n';
    }
}


FabricCVector* f[2];

int main()
{
    f[0] = new FabricCVector0;
    f[1] = new FabricCVector1;
    
    srand(time(NULL));
    auto begin = std::chrono::steady_clock::now();
    genVectors("1.txt", V);
    auto end = std::chrono::steady_clock::now();
    std::cout << "generate " << V << " vectors ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " msec"<< std::endl;
    
    begin = std::chrono::steady_clock::now();
    CVector ** ar = CVector::create("1.txt", f);
    end = std::chrono::steady_clock::now();
    std::cout << "read vectors ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " msec" << std::endl;
    size_t n = 0;
    n = CVector::getCount();
    CVector0 v0("4.txt");
    CVector1 v1("4.txt");
    CVector0 v0tmp("4.txt");
    CVector1 v1tmp("4.txt");
    std::ofstream out("4.txt");
    out.close();
    std::cout.setf(std::ios::fixed);
    std::cout << "sum:\n";
    std::cout << "1 thread ";
    begin = std::chrono::steady_clock::now();
    #pragma omp parallel num_threads(1) private(v0tmp, v1tmp)
    {
        #pragma omp for
        for (size_t i = 0; i < n; ++i)
        {
                if (ar[i]->type())
                {
                    v1tmp = v1tmp + *dynamic_cast<CVector1*>(ar[i]);
                }
                else
                {
                    v0tmp = v0tmp + *dynamic_cast<CVector0*>(ar[i]);
                }
        }
        #pragma omp critical
        {
            v0 = v0 + v0tmp;
            v1 = v1 + v1tmp;
        }
    }
    end = std::chrono::steady_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " msec" << std::endl;
    
    v0.output();
    v1.output();
    
    v0 = CVector0("4.txt");
    v1 = CVector1("4.txt");
    v0tmp = CVector0("4.txt");
    v1tmp = CVector1("4.txt");
    
    std::cout << "2 thread ";
    begin = std::chrono::steady_clock::now();
    #pragma omp parallel num_threads(2) private(v0tmp, v1tmp)
    {
        #pragma omp for
        for (size_t i = 0; i < n; ++i)
        {
                if (ar[i]->type())
                {
                    v1tmp = v1tmp + *dynamic_cast<CVector1*>(ar[i]);
                }
                else
                {
                    v0tmp = v0tmp + *dynamic_cast<CVector0*>(ar[i]);
                }
        }
        #pragma omp critical
        {
            v0 = v0 + v0tmp;
            v1 = v1 + v1tmp;
        }
    }
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " msec" << std::endl;
    
    v0.output();
    v1.output();
    
    v0 = CVector0("4.txt");
    v1 = CVector1("4.txt");
    v0tmp = CVector0("4.txt");
    v1tmp = CVector1("4.txt");
    
    std::cout << "4 thread ";
    begin = std::chrono::steady_clock::now();
    #pragma omp parallel num_threads(4) private(v0tmp, v1tmp)
    {
        #pragma omp for
        for (size_t i = 0; i < n; ++i)
        {
                if (ar[i]->type())
                {
                    v1tmp = v1tmp + *dynamic_cast<CVector1*>(ar[i]);
                }
                else
                {
                    v0tmp = v0tmp + *dynamic_cast<CVector0*>(ar[i]);
                }
        }
        #pragma omp critical
        {
            v0 = v0 + v0tmp;
            v1 = v1 + v1tmp;
        }
    }
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " msec" << std::endl;
    
    v0.output();
    v1.output();
    
    
    
    #pragma omp parallel for num_threads(thr)
    for (size_t i = 0; i < n; ++i)
    {
        ar[i]->output();
        delete ar[i];
    }
    
    
    delete [] ar;
    free(f[0]);
    free(f[1]);
    return 0;
}
