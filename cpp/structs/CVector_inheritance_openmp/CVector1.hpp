#include "CVector.hpp"

#ifndef CVECTOR1
#define CVECTOR1
//IN ROW
class CVector1: public CVector
{
public:
    CVector1();
    CVector1(const char *s);
    CVector1 operator+(const CVector1&);
    CVector1 operator-(const CVector1&);
    virtual int output() override;
    virtual int type() override {return 1;}
    ~CVector1() {return;}
};

class FabricCVector1: public FabricCVector
{
public:
    virtual CVector* create(const char * s) {return new CVector1(s);}
};

#endif
