## Templates in C (yes! plain C! Not C++!)
#### Init
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