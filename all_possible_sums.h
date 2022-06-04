#ifndef ALL_POSSIBLE_SUMS_H_ 
#define ALL_POSSIBLE_SUMS_H_ 

#include "templates.h"

#ifdef T
	#undef T
#endif

#define T float
#include "sum_as_template.h"

#ifdef T
	#undef T
#endif

#define T double
#include "sum_as_template.h"

#ifdef T
	#undef T
#endif

#define T int
#include "sum_as_template.h"

#endif /*ALL_POSSIBLE_SUMS_H_*/