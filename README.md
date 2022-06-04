## About:
This project for try template implementation on C, original article: http://arnold.uthar.net/index.php?n=Work.TemplatesC with some errors removed and some edits added.

#### sum_as_template.c, .h:
```c
#ifndef T
#error T should be defined
#else
…
#undef T
#endif
```
<br>
In this wording:
<br>
1. We get a readable error if T is not declared
<br>
2. At the beginning of the file, you can immediately see what needs to be declared
<br>
3. Connecting this whole thing will be simplified:
<br>

#### all_possible_sums.c, .h:
```c
// just in case
#ifdef T
	#undef T
#endif

#define T float
#include "sum_as_template.h"

// and here we know that undef is done

#define T double
#include "sum_as_template.h"

#define T int
#include "sum_as_template.h"
```

## Templates in C (yes! plain C! Not C++!)

#### Why using templates?
Imagine you have to write a set of functions in C, which differ only by a few keywords (typically type keywords). For instance, let's say we want to write a function computing the sum of two arrays of length n, for floats, doubles, and ints (null pointers tests are left out for the sake of clarity):
```c
void sum_float(int n, float *a, float *b)
{
	/* computes a:=a+b where a and b are two arrays of length n */
	for(int i = 0; i < n; ++i) {
		a[i] += b[i];
	}
}

void sum_double(int n, double *a, double *b)
{
	/* computes a:=a+b where a and b are two arrays of length n */
	for(int i = 0; i < n; ++i) {
		a[i] += b[i];
	}
}

void sum_int(int n, int *a, int *b)
{
	/* computes a:=a+b where a and b are two arrays of length n */
	for(int i = 0; i < n; ++i) {
		a[i] += b[i];
	}
}
```
<br>
Wouldn't it be nicer to type the function just once, by specifying what keyword is "variable", then "instanciating" the function for each possible value of the "variable", and then having a way to call the exact variant of the function? Of course, for a simple function like this one, it wouldn't make much sense. But think about a much, much longer function. Or set of functions...
<br>
This is what templates do. In C++ there is a template keyword that allows to do just that. The downsides is that it is sometimes hard to port. And it does not exist in C.
<br>
Here's a technique to emulate the use of templates in C. It only uses the standard C preprocessor and it is, as far as I know, ANSI C89-compliant. And it works in C++, too. It is also very useful for OpenCL, which has a fully working pre-processor but no templates.
<br>

`Note:` Over the year, this simple blog post has been cited in many places, translated into Russian, quoted on Greek, Chinese, Finnish forums. Wow! I was contacted and asked whether I "discovered' this technique. No, I do not claim to have invented this trick, because I saw it while digging in code. However, I have found that it is not widely known despite its obvious usefulness, hence the tutorial.

## Templates in C

#### Ingredient 1: a concatenation macro
First, we need to declare a couple of macros. Those macros need to be included in every file that makes use of templates. To make things easier we will declare them in a .h file called "templates.h":
#### templates.h:
```c
#ifndef __TEMPLATES_C_LANG_H_
#define __TEMPLATES_C_LANG_H_

#define CAT(X,Y) X##_##Y
#define TEMPLATE(X,Y) CAT(X,Y)

#endif /*__TEMPLATES_C_LANG_H_*/
```
The goal of macro `TEMPLATE(X,Y)` is to have a keyword that enables us to concatenate X and Y with an underscore in between, like this: `X_Y`, so that writing `TEMPLATE(function,type)` may translate to `function_type`.
<br>
The `##` operator is a C preprocessor directive which allows to concatenate two tokens. The reason we can't use only a single `#define TEMPLATE(X,Y) X##Y` macro is that if X is itself a macro constant, it will not be replaced by its value (the details of this question and the details behind the hack to make it work anyway may be found here (self-referential macros https://gcc.gnu.org/onlinedocs/gcc-4.8.5/cpp/Self-Referential-Macros.html) and here (argument prescan https://gcc.gnu.org/onlinedocs/cpp/Argument-Prescan.html)).

#### Ingredient 2: the functions to "templatize"
Ok, so now we want to write a .c and a .h corresponding to the functions we'd like to have as templates, right? Let's write them. To denote the variable type keyword, we use letter 'T'. This will be #defined later on in the tutorial.
<br>
First the .h:
#### sum_as_template.h:
```c
#ifndef T
    #error T should be defined
#else

#include "templates.h"

void TEMPLATE(sum,T) (int n, T *a, T *b);

#undef T

#endif /* T */
```
Notice we don't guard the .h against multiple inclusion by using the standard `#ifndef HEADER_H_` stuff. This is intentional. We'll see later why. On the other hand, the `#ifdef T` test is optional, but very useful to guard against any unlawful inclusion in the case T isn't defined, so the compiler doesn't throw a fit and starts hissing at you.
<br>
And now the .c:
#### sum_as_template.c:
```c
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
```

#### Mix everything in a bowl...
Now we really want to instanciate the `sum` function so that all its variants exist (`sum_float`, `sum_double`, etc). We create another set of .h and .c files:
<br>
The following .c file is the one we will compile just as another .c in the project:
#### all_possible_sums.c
```c
#include "all_possible_sums.h"

#ifdef T
    #undef T
#endif

#define T float
#include "sum_as_template.c"

#define T double
#include "sum_as_template.c"

#define T int
#include "sum_as_template.c"
```
`Note:` on GCC, `#undef T` would have been enough without the `#ifdef T` / `#endif` around it; but Visual C++ (at least up to version 7) does not like it...
<br>
The following .h is the one we'll include in any .c where a variant of the `sum_...` function is used.
#### all_possible_sums.h
```c
#ifndef ALL_POSSIBLE_SUMS_H_ 
#define ALL_POSSIBLE_SUMS_H_ 

#ifdef T
    #undef T
#endif

#define T float
#include "sum_as_template.h"

#define T double
#include "sum_as_template.h"

#define T int
#include "sum_as_template.h"


#endif /*ALL_POSSIBLE_SUMS_H_*/
```
This time we understand why we didn't guard sum_as_template.h against multiple inclusions: it is included once per type...

#### ...and serve as it is!
We're all set now! Let's use the templates in an example:
#### templateTest.c:
```c
#include "templateTest.h"
#include "all_possible_sums.h"

void templatetest()
{
    int ai[3] = {1,2,3};
    int bi[3] = {4,5,6};
    double af[3] = {1.0,2.0,3.0};
    double bf[3] = {1.5,2.5,3.5};
	
    TEMPLATE(sum,int)(3,ai,bi);
    TEMPLATE(sum,double)(3,af,bf);
}

```
That's all, folks!

## The last word
What about complex types, you may ask? What if I want to make a template where "T" is to be replaced by, say, "unsigned long long"? Wouldn't the compiler complain that it does not know about `void sum_unsigned long long()`?
<br>
The answer is yes, but there's a workaround: typedef the offending, "multi-worded" type into a "single-worded" type, like this:
<br>
`typedef unsigned long long uint64;`
<br>
Then use `TEMPLATE(sum,uint64)` instead of `TEMPLATE(sum,unsigned long long)`. Voilà!