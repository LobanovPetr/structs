#include "CVector.hpp"

size_t CVector::count = 0;

size_t CVector::getCount()
{
    return count;
}

void CVector::clear()
{
    delete [] ar;
    ar = nullptr;
    size = 0;
}

void CVector::copy(const CVector& v)
{
    size = v.size;
    ar = new double[size];
    for (size_t i = 0; i < size; ++i)
    {
        ar[i] = v.ar[i];
    }
}

CVector::CVector()
{
    count++;
    ar = nullptr;
    size = 0;
}

CVector::CVector(const CVector& v): CVector()
{
    count++;
    copy(v);
}

CVector::CVector(CVector && v): CVector()
{
    ar = v.ar;
    size = v.size;
    v.ar = nullptr;
    v.size = 0;
}

CVector::~CVector()
{
    count--;
    clear();
}

CVector& CVector::operator=(const CVector& v)
{
    clear();
    copy(v);
    return *this;
}

CVector& CVector::operator=(CVector&& v)
{
    clear();
    ar = v.ar;
    size = v.size;
    v.ar = nullptr;
    v.size = 0;
    return *this;
}

double& CVector::operator[](const size_t idx)
{
    double * tmp = nullptr;
    if (idx >= size)
    {
        tmp = new double[idx + 1]();
        for (size_t i = 0; i < size; ++i)
        {
            tmp[i] = ar[i];
        }
        delete [] ar;
        ar = tmp;
        size = idx + 1;
    }
    return ar[idx];
}

CVector** CVector::create(const char * FileName, FabricCVector ** f)
{
    CVector ** toReturn = nullptr;
    std::ifstream in(FileName);
    std::string s;
    std::string FileToWrite;
    std::stringstream ss;
    size_t toReturnCurSize = 0;
    size_t toReturnCurIdx = 0;
    CVector * tmp = nullptr;
    int type;
    size_t size;
    
    while(std::getline(in, s))
    {
//        std::stringstream ss(s);
//        std::cout << s << std::endl;
        ss.clear();
        ss << s;
        ss >> type;
//        std::cout << "type " << type << ' ';
        ss >> FileToWrite;
        if (type != 0 && type != 1)
        {
            throw std::runtime_error("incorrect file");
        }
        std::ofstream out(FileToWrite);
        tmp = (f[type])->create(FileToWrite.c_str());
        if (toReturnCurIdx >= toReturnCurSize)
        {
            CVector ** P = new CVector* [toReturnCurSize * 2 + 1];
            for (size_t i = 0; i < toReturnCurSize; ++i)
            {
                P[i] = toReturn[i];
            }
            delete [] toReturn;
            toReturn = P;
            toReturnCurSize = toReturnCurSize * 2 + 1;
        }
        toReturn[toReturnCurIdx++] = tmp;
        ss >> size;
//        std::cout <<"size " << size << ' ';
        tmp->operator[](size - 1);
        for (size_t i = 0; i < size; ++i)
        {
            ss >> tmp->operator[](i);
//            std::cout << tmp->operator[](i) << ' ';
        }
//        std::cout << std::endl;
        
    }
    
    return toReturn;
}

size_t CVector::Size() const
{
    return size;
}

double * CVector::sum(const CVector & v)
{
    double * toReturn = nullptr;
    if (size != v.Size())
    {
        throw std::length_error("lengths are different");
    }
    toReturn = new double[size];
    for (size_t i = 0; i < size; ++i)
    {
        toReturn[i] = ar[i] + v.ar[i];
    }
    return toReturn;
}

double * CVector::dif(const CVector & v)
{
    double * toReturn = nullptr;
    if(size != v.Size())
    {
        throw std::length_error("lengths are different");
    }
    toReturn = new double[size];
    for (size_t i = 0; i < size; ++i)
    {
        toReturn[i] = ar[i] - v.ar[i];
    }
    return toReturn;
}

double CVector::operator*(const CVector & v)
{
    double toReturn = 0;
    if(size != v.Size())
    {
        throw std::length_error("lengths are different");
    }
    for (size_t i = 0; i < size; ++i)
    {
        toReturn = ar[i] * v.ar[i];
    }
    return toReturn;
}
