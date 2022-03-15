#ifndef array_h
#define array_h

#include <stdio.h>
#include <stdlib.h>

struct array
{
    int * ptr;
    int size;
    int cur_size;
};

struct array * delete_el(struct array * arr, int idx);
void add(struct array* a, int x);
void del(struct array* a);
struct array * create(int size);
void print(struct array* a);

#endif /* array_h */
