#include "CRat.hpp"

int gcd(int p, unsigned int q)
{
    
    for(;p != 0 && q != 0;)
    {
        if (p > q)
        {
            p %= q;
        }
        else
        {
            q %= p;
        }
    }
    return p + q;
}

fraction fraction::operator+(const fraction &a)
{
    int p_ = a.numerator();
    int q_ = a.denominator();
    
    fraction r;
    if (q_ == q)
    {
        r = fraction(p_ + p, q);
    }
    else
    {
        r = fraction(p_ * q + p * q_, q_ * q);
    }
    return r;
}

fraction fraction::operator-(const fraction &a)
{
    int p_ = a.numerator();
    int q_ = a.denominator();
    
    fraction r;
    
    if (q_ == q)
    {
        r = fraction(p - p_, q);
    }
    else
    {
        r = fraction(q_ * p - q * p_, q_ * q);
    }
    return r;
}
