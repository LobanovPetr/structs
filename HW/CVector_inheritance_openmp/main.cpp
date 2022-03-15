#include <iostream>
#include <omp.h>
#include "CVector0.hpp"
#include "CVector1.hpp"
#include <ctime>
#define N 5     // max len of vector
#define dist 5  // max value
#define V 5    // num of vertex
#define thr 6   // num of threads
char a[2][32] = {{"2.txt\0"}, {"3.txt\0"}};

void genVectors(char* FileName, int n)
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
    
    genVectors("1.txt", V);
    CVector ** ar = CVector::create("1.txt", f);
    int n = 0;
    n = CVector::getCount();
    CVector0 v0("4.txt");
    CVector1 v1("4.txt");
    std::ofstream out("4.txt");
    out.close();
    std::cout.setf(std::ios::fixed);
    auto start = clock();
    #pragma omp parallel for num_threads(thr) reduction(+:v0, v1)
    {
        for (size_t i = 0; i < n; ++i)
        {
            if (ar[i]->type())
                v1 = dynamic_cast<CVector1*>(ar[i])->operator+(v1);
            else
                v0 = dynamic_cast<CVector0*>(ar[i])->operator+(v0);
        }
    }
    
    std::cout << (double)(clock() - start)/CLOCKS_PER_SEC << std::endl;
    for (size_t i = 0; i < n; ++i)
    {
        ar[i]->output();
        delete ar[i];
    }
    
    v0.output();
    v1.output();
    delete [] ar;
    free(f[0]);
    free(f[1]);
    return 0;
}
