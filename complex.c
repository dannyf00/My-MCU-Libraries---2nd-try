#include "complex.h"		//complex numbers

//initialize a complex number
complex *complex_init(complex *x, double real, double imag) {
    x->real = real;
    x->imag = imag;
    return x;
}

//scale a complex number
//cmplx = cmplx * scale
complex *complex_scale(complex *x, double scale) {
    static complex z;
    z.real = x->real * scale;
    z.imag = x->imag * scale;
    return &z;
}

//compliment of a complex
//z = conjugate of x
complex *complex_conj(complex *x) {
    static complex z;
    z.real = x->real;
    z.imag =-x->imag;
    return &z;
}

//return abs^2 of a complex number
double complex_abs2(complex *z) {
    return z->real * z->real + z->imag * z->imag;
}

//return abs of a complex number
double complex_abs(complex *z) {
    return sqrt(z->real * z->real + z->imag * z->imag);
}

//assign a complex number
//z = x
complex *complex_equ(complex *z, complex *x) {
    z->real = x->real;
    z->imag = x->imag;
    return z;
}

//complex additions
//z = x + y
complex *complex_add(complex *z, complex *x, complex *y) {
    z->real = x->real + y->real;
    z->imag = x->imag + y->imag;
    return z;
}

//complex substraction
//z = x - y
complex *complex_sub(complex *z, complex *x, complex *y) {
    z->real = x->real - y->real;
    z->imag = x->imag - y->imag;
    return z;
}


//complex multip
//z = x * y
complex *complex_mult(complex *z, complex *x, complex *y) {
    z->real = x->real * y->real - x->imag * y->imag;
    z->imag = x->real * y->imag + x->imag * y->real;
    return z;
}


//complex division
//z = x / y
complex *complex_div(complex *z, complex *x, complex *y) {
    double tmp;
    //calculate z = x * conjugate(y)
    z->real = x->real * y->real + x->imag * y->imag;
    z->imag = x->imag * y->real - x->real * y->imag ;
    //scalculat the scale / denominator
    tmp = 1.0 / (y->real * y->real + y->imag * y->imag);
    //scale the resulting complex number
    z->real = z->real * tmp;
    z->imag = z->imag * tmp;
    return z;
}

//get the real element of a complex number
double complex_real(complex *z) {
    return z->real;
}

//get the imaginary element of a complex number
double complex_imag(complex *z) {
    return z->imag;
}
