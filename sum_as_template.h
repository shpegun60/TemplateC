#ifndef T
    #error T should be defined
#else

#include "templates.h"

void TEMPLATE(sum,T) (int n, T *a, T *b);

#undef T

#endif
