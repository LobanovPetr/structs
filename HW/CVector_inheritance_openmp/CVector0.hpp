#include "CVector.hpp"

#ifndef CVECTOR0
#define CVECTOR0
//IN ROW
class CVector0: public CVector
{
    std::string FileName;
public:
    CVector0();
    CVector0(const char *);
    CVector0 operator+(const CVector0&);
    CVector0 operator-(const CVector0&);
    CVector0& operator=(const CVector0&);
    virtual int output();
    virtual int type() {return 0;}
    ~CVector0() {return;}
};

class FabricCVector0: public FabricCVector
{
public:
    virtual CVector* create(const char * s) {return new CVector0(s);}
//    ~FabricCVector0();
};

#endif
