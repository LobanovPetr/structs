#include<stdexcept>
#include<iostream>

class element;

class CVector
{
private:
    double * arr = NULL;
    size_t size = 0;
    size_t Nsize = 0;
    
    void realoc(size_t);
    void check();
    friend class element;
public:
    
    size_t len() const{return size;}
    CVector(){this->arr = nullptr; size = 0; Nsize = 0;}
    CVector(size_t n);
    CVector(const CVector& v);
    CVector(CVector && v);
    CVector(size_t n_, const double * v) : CVector(n_) {for (size_t i = 0; i < n_; ++i) arr[i] = v[i];};
    void push_back(const double & a);
    void pop_back();
    void print() const;
    element operator[](const unsigned & i);
//    double operator[](const unsigned & i) const;
    CVector& operator=(const CVector& b);
    CVector& operator=(CVector && b);
    CVector operator-(const CVector& b) const;
    CVector operator+(const CVector& b) const;
    double operator*(const CVector& b) const;
    ~CVector(){delete [] arr;}
};

class element
{
    CVector * v = NULL;
    size_t idx = -1;
    double value = 0;
public:
    element(CVector *v, size_t idx, double value) : v(v), idx(idx), value(value){};
    element(const element& c)
    {
        v = c.v;
        idx = c.idx;
        value = c.value;
    }
    double val() const
    {
        return value;
    }
    void operator=(const element& c)
    {
        v = c.v;
        idx = c.idx;
        value = c.value;
    }
    void operator=(const double & a)
    {
        if (v->len() > idx)
        {
            v->arr[idx] = a;
        }
        else
        {
            v->size = idx + 1;
            v->check();
            v->arr[idx] = a;
        }
    }
    
    operator double()
    {
        return value;
    }
};
