#include "CVector.hpp"

void CVector::realoc(size_t n)
{
    double * tmp = new double[n]();
    for (size_t i = 0; i < std::min(Nsize, size); ++i)
    {
        tmp[i] = arr[i];
    }
    if (Nsize > 0)
    {
        delete [] arr;
    }
    arr = tmp;
    return;
}

void CVector::check()
{
    if (size > Nsize)
    {
        realoc(2 * size);
        Nsize = 2 * size;
    }
    if (size * 4 < Nsize)
    {
        realoc(size * 2);
        Nsize = size * 2;
    }
}


CVector::CVector(size_t n)
{
    Nsize = 0;
    size = n;
    realoc(size * 2);
    Nsize = size * 2;
}

void CVector::push_back(const double & a)
{
    size++;
    check();
    arr[size - 1] = a;
    return;
}

void CVector::pop_back()
{
    if (size == 0)
    {
        return;
    }
    size--;
    if (size == 0)
    {
        return;
    }
    check();
}

element CVector::operator[](const unsigned & i)
{
    if (i < size)
    {
        return element(this, i, arr[i]);
    }
    else
    {
        return element(this, i, 0);
    }
}

CVector::CVector(const CVector& v) : CVector(v.len())
{
    for (size_t i = 0; i < size; ++i)
    {
        arr[i] = v.arr[i];
    }
}

CVector::CVector(CVector && v)
{
    arr = v.arr;
    size = v.len();
    Nsize = v.Nsize;
    
    v.arr = nullptr;
    v.size = 0;
    v.Nsize = 0;
}

void CVector::print() const
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

CVector& CVector::operator=(const CVector&a)
{
    if(&a == this)
    {
        return *this;
    }
    if (size != a.len())
    {
        delete [] arr;
        size = a.len();
        Nsize = 2 * size;
        arr = new double[Nsize]();
    }
    
    for (size_t i = 0; i < size; ++i)
    {
        arr[i] = a.arr[i];
    }
    return *this;
}

CVector& CVector::operator=(CVector && a)
{
    if (arr != nullptr)
    {
        delete [] arr;
    }
    size = a.len();
    arr = a.arr;
    Nsize = a.Nsize;
    
    a.size = 0;
    a.Nsize = 0;
    a.arr = nullptr;
    return *this;
}

CVector CVector::operator+(const CVector&a) const
{
    if(a.len() != size)
    {
        throw std::length_error("incorrect vectors sizes");
    }
    CVector tmp(a.len());
    for (int i = 0; i < a.len(); ++i)
    {
        tmp[i] = arr[i] + a.arr[i];
    }
    return tmp;
}

CVector CVector::operator-(const CVector&a) const
{
    if(a.len() != size)
    {
        throw std::length_error("incorrect vectors sizes");
    }
    CVector tmp(a.len());
    for (int i = 0; i < a.len(); ++i)
    {
        tmp[i] = arr[i] - a.arr[i];
    }
    return tmp;
}

double CVector::operator*(const CVector&a) const
{
    if(a.len() != size)
    {
        throw std::length_error("incorrect vectors sizes");
    }
    double ans = 0;
    for (int i = 0; i < size; ++i)
    {
        ans += arr[i]*a.arr[i];
    }
    return ans;
}

std::ostream& operator<<(std::ostream& out, const element& el)
{
    out << el.val();
    return out;
};
