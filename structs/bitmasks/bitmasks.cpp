#include "bitmasks.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

int my_mod(int x)
{
    return (tp + (x % 8)) % tp;
}

void print(const myset & a)
{
    cout << endl;
    for (auto it : a)
    {
        cout << it << ' ';
    }
    cout << endl;
}

myset myset::operator & (const myset& b) const
{
    if (to <= b.from || b.to <= from)
    {
        return myset();
    }

    int l = max(b.from, from), r = min(to, b.to);
    
    myset tmp(l, r, 1);
    
    for (int i = 0; i < (tmp.right - tmp.left) / tp; ++i)
    {
        tmp.bitmask[i] = bitmask[(tmp.left - left)/tp + i] & b.bitmask[(tmp.left - b.left)/tp + i];
    }
    
    return tmp;
}

myset myset::operator | (const myset & b) const
{
    int l = min(b.from, from), r = max(b.to, to);
    
//    cout << "this left " << this->left << " this right " << this->right << "\n";
//    cout << "b left " << b.left << " b right " << b.right << "\n";
    
    myset tmp(l, r, 1);
    
    for (int i = 0; i < (right - left)/tp ; ++i)
    {
        tmp.bitmask[(left - tmp.left)/tp + i] = bitmask[i];
    }
    
    for (int i = 0; i < (b.right - b.left)/tp; ++i)
    {
        tmp.bitmask[(b.left - tmp.left)/tp + i] |= b.bitmask[i];
    }
    
    return tmp;
    
}

int myset::set(int num)
{
    if (num < to && num >= from)
    {
        bitmask[(num - left) / tp] |= (b1 >> my_mod(num));
        return 0;
    }
    else
    {
        return -1;
    }
}
myset::myset(int start, int stop, bool empty) : from(start), to(stop)
{
    if (stop <= start)
    {
        bitmask = NULL;
        from = 0;
        to = 0;
        left = 0;
        right = 0;
        return;
    }
    left = start - my_mod(start);
    right = stop + tp - my_mod(stop);
    
    bitmask = (unsigned char *)malloc((right - left) / tp);
    bitmask[((right - left) / tp) - 1] = MAX;
    bitmask[0] = (((empty)?MIN:MAX) >> (start - left));
    for (int i = 1; i < ((right - left) / tp) - 1; ++i)
    {
        bitmask[i] = ((empty)?MIN:MAX);
    }
    bitmask[((right - left) / tp) - 1] &= (((empty)?MIN:MAX) << (tp - my_mod(to)));
}


bool myset::contains(int num) const
{
    if(num < to && num >= from)
    {
        return bitmask[(num - left) / tp] & (b1 >> my_mod(num));
    }
    else return false;
}

myset& myset::operator=(const myset& b)
{
    if(&b == this)
    {
        return *this;
    }
    free(bitmask);
    left = b.left;
    right = b.right;
    from = b.from;
    to = b.to;
    
    bitmask = (unsigned char *)malloc((right - left) / tp);
    
    for (int i = 0; i < (right - left)/tp; ++i)
    {
        bitmask[i] = b.bitmask[i];
    }
    return * this;
}

void myset::clear()
{
    free(bitmask);
    from = 0; to = 0;
    left = 0; right = 0;
}

int myset::erase(int num)
{
    if (num < to && num >= from)
    {
        bitmask[(num - left) / tp] &= (~(b1 >> my_mod(num)));
        return 0;
    }
    else
    {
        return -1;
    }
}

myset::myset(const myset& b)
{
    left = b.left;
    right = b.right;
    from = b.from;
    to = b.to;
    if (from >= to)
    {
        bitmask = NULL;
        return;
    }
    
    bitmask = (unsigned char *)malloc((right - left) / tp);
    
    memcpy(bitmask, b.bitmask, (right - left) / tp);
}

myset::myset(int stop): from(0), to(stop)
{
    left = 0;
    right = stop + tp - my_mod(stop);
    bitmask = (unsigned char * )malloc((right - left) / tp);
    for (int i = 0; i < (right - left) / tp - 1; ++i)
    {
        bitmask[i] = MAX;
    }
    bitmask[(right - left) / tp - 1] = (MAX << (tp - my_mod(to)));
}

myset::iterator::iterator(int from, int to, unsigned char * bitmask): from(from), to(to), bitmask(bitmask)
{
    left = from - my_mod(from);
    right = to + my_mod(to);
    idx = from;
    while(idx < to && !(bitmask[(idx - left) / tp] & (b1 >> (my_mod(idx))))) ++idx;
}

myset::iterator& myset::iterator::operator++()
{
    ++idx;
    while(idx < to && !(bitmask[(idx - left) / tp] & (b1 >> (my_mod(idx))))) ++idx;
    return *this;
}

int myset::Min() const
{
    if (begin() == end())
        throw -1;
    else
        return *begin();
}

int myset::Max() const
{
    int max;
    if (begin() == end())
    {
        throw -1;
    }
    for (auto it = begin(); it != end(); ++it)
    {
        max = *it;
    }
    return max;
}


myset::iterator myset::end() const
{
    iterator res;
    res.from = from;
    res.to = to;
    res.idx = to;
    res.bitmask = bitmask;
    res.left = left;
    res.right = right;
    return res;
}
int change_borders(myset & a, int l, int r)
{
    if (r <= l)
        a = myset();
    myset tmp1 = myset(l, r);
    myset tmp2 = myset(l, r, 1);
    tmp1 = a & tmp1;
    a = tmp1 | tmp2;
    return 1;
    
}
