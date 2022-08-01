#include "CVector1.hpp"

CVector1::CVector1() : CVector()
{
    return;
}

CVector1::CVector1(const char * s) : CVector(s)
{
    return;
}

int CVector1::output()
{
    std::ofstream out(FileName, std::ios_base::app);
    out << "⏞" << '\n';
    for (size_t i = 0; i < size - 1; ++i)
    {
        out << ar[i] << '\n';
    }
    out << ar[size - 1] << '\n' << "⏟" << '\n';
    return 0;
}

CVector1 CVector1::operator+(const CVector1 & v)
{
    CVector1 toReturn(FileName.c_str());
    double * a = sum(v);
    toReturn.ar = a;
    toReturn.size = size > v.Size() ? size : v.Size();
    return toReturn;
}

CVector1 CVector1::operator-(const CVector1 & v)
{
    CVector1 toReturn(FileName.c_str());
    double * a = dif(v);
    toReturn.ar = a;
    toReturn.size = size > v.Size() ? size : v.Size();
    return toReturn;
}

//FabricCVector1::~FabricCVector1() { return; }
