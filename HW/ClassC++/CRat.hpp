#pragma once
#include<cstdio>
#include<iostream>
#define N 5

int gcd(int p_, unsigned int q_);

class fraction
{
    int p;
    unsigned int q;
    
public:
    fraction(): p(0), q(1){}
    fraction(int p_, unsigned int q_)
    {
        int tmp;
        if (q_ == 0)
        {
            std::cerr << "Error: zero devision\n";
            exit(1);
        }
        
        tmp = gcd(std::abs(p_), q_);
        p = p_ / tmp;
        q = q_ / tmp;
    }
    int numerator() const
    {
        return p;
    }
    unsigned int denominator() const
    {
        return q;
    }
    
    fraction operator+(const fraction &a);
    fraction operator-(const fraction &a);
    fraction& operator=(const fraction &a)
    {
        p = a.numerator();
        q = a.denominator();
        return *this;
    }
};

class CRat
{
    fraction vec[N];
    
public:
    CRat()
    {
        fraction tmp(0, 1);
        for (int i = 0; i < N; ++i)
        {
            vec[i] = tmp;
        }
    }
    CRat(fraction * vec_)
    {
        for (int i = 0; i < N; ++i)
        {
            vec[i] = vec_[i];
        }
    }
    
    fraction operator[] (const unsigned int i) const
    {
        return vec[i];
    }
    
    void print() const
    {
        for (int i = 0; i < N; ++i)
        {
            printf("%d/%u \t", vec[i].numerator(), vec[i].denominator());
        }
        printf("\n");
        return;
    }
    
    CRat operator+ (const CRat &a)
    {
        fraction r[N];
        for (int i = 0; i < N; ++i)
        {
            r[i] = vec[i] + a[i];
        }
        CRat v(r);
        return v;
    }
    
    CRat operator- (const CRat &a)
    {
        fraction r[N];
        for (int i = 0; i < N; ++i)
        {
            r[i] = vec[i] - a[i];
        }
        CRat v(r);
        return v;
    }
    
    CRat &operator=(const CRat &a)
    {
        for (int i = 0; i < N; ++i)
        {
            vec[i] = a[i];
        }
        return *this;
    }
};
