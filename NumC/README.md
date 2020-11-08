# numc

The goal of the project was to learn about how to make my code optimize code using unrolling, SIMD instructions, OpenMP parallelization, and other techniques to improve the speed of the program.

# IMPLEMENT OUR VERSION OF NUMPY.

# *Implemented*:
### 1) A SLOWER VERSION OF NUMPY
### 2) Matrix functions in C
   #### *Implemented*:
    matirx.c functions add_matirx, sub_matirx, neg_matirx, abs_matirx, pow_matirx.
### 3) Wrote the Python-C interface:
   -I learn about Pyobjects in C
   #### *some inculded* :
      Py_BuildValue
      PyTupleObject
      PyLongObject
      PyFloatObject
      PyListObject
   -I learn about the how C would catch throw and error to python:
   #### *some inculded* :
      PyObject_TypeCheck
      PyErr_SetString
   -I learned about overriding number methods
   #### *Implemented*:  
      numc.c functions Matrix61c_add, Matrix61c_sub, Matrix61c_neg, Matrix61c_abs, Matrix61c_pow.
      these allowed me to be able to use "+", "- (subtraction)", "*" , "- (negation)", "abs()" , "**" to operate of numc.Matrix structs
   #### *UNTILlized compiler flag and linker flag for python setup.py files*:
      "CFLAGS = -g -Wall -std=c99 -fopenmp -mavx -mfma -pthread 
      LDFLAGS = -fopenmp"
      
### 4) The goal of the project was learn about performance: 
###### UNFORTUNEATELY,,, the performance is lacking overall (about 4 times faster than a naive implementation)
-I learned about Intel Intrinsics or SIMD Instructions and about more about OpenMP 
   #### *UNTILlized* :
   void _mm256_storeu_pd (double * mem_addr, __m256d a)
   * __m256d _mm256_set1_pd (double a)
   * __m256d _mm256_set_pd (double e3, double e2, double e1, double e0)
   * __m256d _mm256_loadu_pd (double const * mem_addr)
   * __m256d _mm256_add_pd (__m256d a, __m256d b)
   * __m256d _mm256_sub_pd (__m256d a, __m256d b)
   These are apart of intel intrinsic AVX.
   These helped to remove intrustions. 
-I learned about loop unrolling and other optimzation to remove costly intrustions
   This is sorta data level parallism. 
   

The utilization of loop unrolling, vectorization, and other optimizations can be seen in matirx.c. in functions add_matirx, sub_matirx, neg_matirx, abs_matirx, pow_matirx.

## OVERALL:
This project was kinda hard. Super hard actually. However, I did learn alot from it. 
The mul and power work with the SIMD Inrustions and OpenMP. However there are some cases that I do not not catch. I am un clear about where they are at. I considered I think most edge cases and made sure not to corrupt thr original Matrix. I had to settle for the not optimized mul and power operations. 
I tried my best!! And I learned a lot! what more could I have asked for... i mean more points from the autograder ;-( but i'll live 
## HARDEST PART:
I
t felt like i was learning so many different things. From the way the setup.py file was written. Sometime i'll get a segfault and other time Python would yell at me about a directory it wanted.  Then I hadn't even made my way to utilizing MIDI's or unrolling to code. I wish i had just used MIDI initally but I suppose unrolling really makes it easier.
## Easiest PART:
MAYBE THE MIDI. I kinda liked to think in terms of vectors. This got complicated when the indexes weren't divisiable by four. BUT I WILL LIVE.




