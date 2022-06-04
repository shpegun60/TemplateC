## Templates in C (yes! plain C! Not C++!)
Why using templates?
<br>
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
<br>
Wouldn't it be nicer to type the function just once, by specifying what keyword is "variable", then "instanciating" the function for each possible value of the "variable", and then having a way to call the exact variant of the function? Of course, for a simple function like this one, it wouldn't make much sense. But think about a much, much longer function. Or set of functions...
<br>
This is what templates do. In C++ there is a template keyword that allows to do just that. The downsides is that it is sometimes hard to port. And it does not exist in C.
<br>
Here's a technique to emulate the use of templates in C. It only uses the standard C preprocessor and it is, as far as I know, ANSI C89-compliant. And it works in C++, too. It is also very useful for OpenCL, which has a fully working pre-processor but no templates.
<br>
Note: Over the year, this simple blog post has been cited in many places, translated into Russian, quoted on Greek, Chinese, Finnish forums. Wow! I was contacted and asked whether I "discovered' this technique. No, I do not claim to have invented this trick, because I saw it while digging in code. However, I have found that it is not widely known despite its obvious usefulness, hence the tutorial.
<br>
<br>
<br>
## Templates in C
Ingredient 1: a concatenation macro<br>First, we need to declare a couple of macros. Those macros need to be included in every file that makes use of templates. To make things easier we will declare them in a .h file called "templates.h":
```c
#ifndef TEMPLATES_H_
#define TEMPLATES_H_

#define CAT(X,Y) X##_##Y
#define TEMPLATE(X,Y) CAT(X,Y)

#endif
```