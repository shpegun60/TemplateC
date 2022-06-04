#ifndef T
    #error T should be defined
#else

#include "templates.h"

void TEMPLATE(sum,T) (int n, T *a, T *b)
{
    /* computes a:=a+b where a and b are two arrays of length n */
    for(int i = 0; i < n; ++i) {
        a[i] += b[i];
    }
}

#undef T

#endif /* T */
