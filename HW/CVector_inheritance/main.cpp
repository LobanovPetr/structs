#include <iostream>
#include "CVector0.hpp"
#include "CVector1.hpp"


FabricCVector* f[2];

int main()
{
    f[0] = new FabricCVector0;
    f[1] = new FabricCVector1;
    CVector ** ar = CVector::create("1.txt", f);
    int n = CVector::getCount();
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
