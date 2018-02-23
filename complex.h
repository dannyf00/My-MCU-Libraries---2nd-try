#ifndef _COMPLEX_H
#define _COMPLEX_H


#include <math.h>           //we use sqrt in complex_abs

//complex data type
typedef struct {
    double real;            //real element of a complex number
    double imag;            //imaginary element of a complex number
} complex;                  //complex data type

//initialize a complex number
complex *complex_init(complex *x, double real, double imag);

//scale a complex number
//cmplx = cmplx * scale
complex *complex_scale(complex *x, double scale);

//compliment of a complex
//z = conjugate of x
complex *complex_conj(complex *x);

//return abs^2 of a complex number
double complex_abs2(complex *z);

//return abs of a complex number
double complex_abs(complex *z);

//assign a complex number
//z = x
complex *complex_equ(complex *z, complex *x);

//complex additions
//z = x + y
complex *complex_add(complex *z, complex *x, complex *y);

//complex substraction
//z = x - y
complex *complex_sub(complex *z, complex *x, complex *y);


//complex multip
//z = x * y
complex *complex_mult(complex *z, complex *x, complex *y);


//complex division
//z = x / y
complex *complex_div(complex *z, complex *x, complex *y);

//get the real element of a complex number
double complex_real(complex *z);

//get the imaginary element of a complex number
double complex_imag(complex *z);

#endif
