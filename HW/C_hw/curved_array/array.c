#include "array.h"

void add(struct array* a, int x)
{
    if(a->cur_size < a->size)
    {
        a->ptr[a->cur_size] = x;
        a->cur_size++;
    }
    else
    {
        printf("Can't add element\n");
    }
}

void del(struct array* a)
{
    if(a->ptr != NULL)
    {
        free(a->ptr);
    }
    else
    {
        printf("Can't delete array\n");
    }
}

struct array * create(int size)
{
    struct array * a = (struct array *)(malloc(sizeof(struct array)));
    a->ptr = (int *)malloc(sizeof(int) * size);
    a->size = size;
    a->cur_size = 0;
    return a;
}

struct array * delete_el(struct array * arr, int idx)
{
    if (arr->size > idx)
    {
        for (int i = idx; i < arr->size - 1; i++)
        {
            arr->ptr[i] = arr->ptr[i + 1];
        }
        if (arr->size == 1)
        {
            free(arr->ptr);
        }
        else
        {
        arr->ptr = (int *)realloc(arr->ptr, sizeof(struct array) * (arr->size - 1));
        }
        arr->size--;
    }
    else
    {
        printf("incorrect idx");
    }
    return arr;
}

void print(struct array* a)
{
    for (int i = 0; i < a->size; i++)
    {
        printf("%d\t\t", a->ptr[i]);
    }
    printf("\n");
}
