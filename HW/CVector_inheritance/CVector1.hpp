#include "CVector.hpp"

#ifndef CVECTOR1
#define CVECTOR1
//IN ROW
class CVector1: public CVector
{
    std::string FileName;
public:
    CVector1();
    CVector1(const char *);
    CVector1 operator+(const CVector1&);
    CVector1 operator-(const CVector1&);
    virtual int output();
    ~CVector1() {return;}
};

class FabricCVector1: public FabricCVector
{
public:
    virtual CVector* create(const char * s) {return new CVector1(s);}
//    ~FabricCVector1();
};

#endif
