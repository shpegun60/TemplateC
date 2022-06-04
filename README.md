## Templates in C (yes! plain C! Not C++!)
###Why using templates?
Imagine you have to write a set of functions in C, which differ only by a few keywords (typically type keywords). For instance, let's say we want to write a function computing the sum of two arrays of length n, for floats, doubles, and ints (null pointers tests are left out for the sake of clarity):
```c
void sum_float(int n, float *a, float *b)
{
/* computes a:=a+b where a and b are two arrays of length n */
int i;
for(i=0;i<n;i++) a[i]+=b[i];
}

void sum_double(int n, double *a, double *b)
{
/* computes a:=a+b where a and b are two arrays of length n */
int i;
for(i=0;i<n;i++) a[i]+=b[i];
}

void sum_int(int n, int *a, int *b)
{
/* computes a:=a+b where a and b are two arrays of length n */
int i;
for(i=0;i<n;i++) a[i]+=b[i];
}
```