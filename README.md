## TemplateC
This project for try template implementation in C, original article: http://arnold.uthar.net/index.php?n=Work.TemplatesC
<br>
<br>
## Templates in C (yes! plain C! Not C++!)
<br>
# Why using templates?
<br>
Imagine you have to write a set of functions in C, which differ only by a few keywords (typically type keywords). For instance, let's say we want to write a function computing the sum of two arrays of length n, for floats, doubles, and ints (null pointers tests are left out for the sake of clarity):
<br>