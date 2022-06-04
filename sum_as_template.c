#ifdef T

#include "templates.h"

int TEMPLATE(sum,T) (int n, T *a, T *b)
{
	/* computes a:=a+b where a and b are two arrays of length n */
	for(int i = 0; i < n; ++i) {
		a[i] += b[i];
	}
}

#endif  /* T */