#include<iostream>
#define tp 8 // size of uchar in bits
const unsigned char MAX = 255;
const unsigned char b1 = 128;
const unsigned char MIN = 0;


class myset;
int my_mod(int);
int change_borders(myset & a, int l, int r);
void print(const myset & a);

class myset // [)
{
public:
    unsigned char * bitmask;
    int from;
    int to;
    int left;
    int right;
    
public:
    class iterator
    {
        int idx;
        int from;
        int to;
        int left;
        int right;
        unsigned char * bitmask;
        friend class myset;
    public:
        iterator(){}
        iterator(int from, int to, unsigned char * bitmask);
        iterator& operator++();
        bool operator==(const iterator & b) const {return b.idx == idx;};
        bool operator!=(const iterator & b) const {return b.idx != idx;};
        int operator* () const {return idx;}
    };
    
    myset(){bitmask = NULL; from = 0; to = 0; left = 0; right = 0;};
    int size() const {return to - from;};
    myset(int stop);  // make set of elements from 0 to stop
    myset(const myset& b);
    
    iterator begin() const {iterator res(from, to, bitmask); return res;}
    
    iterator end() const;
    
    myset(int start, int stop, bool empty = 0); // make a set of elements from start to stop
    bool contains(int num) const; // check if "num" in the set
    void clear(); // clear set
    
    int set(int num);
    int erase(int num);
    
    int Min() const;
    int Max() const;
    int Left() const {return from;}
    int Right() const {return to;}
    
    ~myset(){free(bitmask); from = 0; to = 0; left = 0; right = 0;};
    
    myset& operator= (const myset& b);
    myset operator & (const myset& b) const;
    myset operator | (const myset & b) const;
};
