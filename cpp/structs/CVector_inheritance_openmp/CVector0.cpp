#include "CVector0.hpp"

CVector0::CVector0() : CVector()
{
    return;
}

CVector0::CVector0(const char * s) : CVector(s)
{
    return;
}

int CVector0::output()
{
    std::ofstream out(FileName, std::ios_base::app);
    out << '{';
    for (size_t i = 0; i < size - 1; ++i)
    {
        out << ar[i] << ' ';
    }
    out << ar[size - 1] << '}' << '\n';
    return 0;
}

CVector0 CVector0::operator+(const CVector0& v)
{
    CVector0 toReturn(FileName.c_str());
    double * a = sum(v);
    toReturn.ar = a;
    toReturn.size = size > v.Size() ? size : v.Size();
    return toReturn;
}

CVector0 CVector0::operator-(const CVector0& v)
{
    CVector0 toReturn(FileName.c_str());
    double * a = dif(v);
    toReturn.ar = a;
    toReturn.size = size > v.Size() ? size : v.Size();
    return toReturn;
}
//FabricCVector0::~FabricCVector0() {return;}
