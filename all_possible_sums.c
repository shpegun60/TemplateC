#include "all_possible_sums.h"

#ifdef T
    #undef T
#endif

#define T float
#include "sum_as_template.c"

#ifdef T
    #undef T
#endif

#define T double
#include "sum_as_template.c"

#ifdef T
    #undef T
#endif

#define T int
#include "sum_as_template.c"

