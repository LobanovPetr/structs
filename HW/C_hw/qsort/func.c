#include "func.h"

int prepare(double * ar, int l, int r)
{
    int idx = l + 1 + rand() % (r - l - 1); // generate random index
    int start = idx;
    for (int i = idx - 1; i > l; --i)
    {
        if (i == idx - 1 && ar[i] > ar[idx])
        {
            double p = ar[i];
            ar[i] = ar[idx];
            ar[idx] = p;
            idx = idx - 1;
        }
        else if (i < idx - 1 && ar[i] > ar[idx])
        {
            double p = ar[idx - 1];
            ar[idx - 1] = ar[idx];
            ar[idx] = ar[i];
            ar[i] = p;
            idx = idx - 1;
        }
    }
    for (int i = start + 1; i < r; ++i)
    {
        if (i == idx + 1 && ar[i] < ar[idx])
        {
            double p = ar[i];
            ar[i] = ar[idx];
            ar[idx] = p;
            idx = idx + 1;
        }
        else if (i > idx + 1 && ar[i] < ar[idx])
        {
            double p = ar[idx + 1];
            ar[idx + 1] = ar[idx];
            ar[idx] = ar[i];
            ar[i] = p;
            idx = idx + 1;
        }
    }
    return idx;
}

void quick_sort(double * ar, int l, int r)
{
    if (r - l <= 2)
    {
        return;
    }
    else
    {
        int q = prepare(ar, l, r);
        quick_sort(ar, l, q);
        quick_sort(ar, q, r);
    }
}
