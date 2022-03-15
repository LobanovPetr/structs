#include "CVector0.hpp"

CVector0::CVector0(): CVector(), FileName() {}

CVector0::CVector0(const char * s) : CVector(), FileName(s) {};

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
    toReturn.size = size;
    return toReturn;
}

CVector0 CVector0::operator-(const CVector0& v)
{
    CVector0 toReturn(FileName.c_str());
    double * a = dif(v);
    toReturn.ar = a;
    toReturn.size = size;
    return toReturn;
}

//FabricCVector0::~FabricCVector0() {return;}
