#ifndef COMPLEX_MATH_H_INCLUDED
#define COMPLEX_MATH_H_INCLUDED

//hardware configuration
#define USE_PRINTF					//define if you want to use complex_printf
//end hardware configuration

#ifdef USE_PRINTF
#include <stdio.h>					//only if printf is to be used
#endif

//global defines
typedef struct {
	double real;
	double imag;
} COMPLEX_t;			//complex data type

//global variable

//add complex numbers
//c = a + b
void complex_add(COMPLEX_t *c, COMPLEX_t *a, COMPLEX_t *b);

//subtract complex numbers
//c = a - b
void complex_sub(COMPLEX_t *c, COMPLEX_t *a, COMPLEX_t *b);

//multiply complex numbers
//c = a * b
void complex_mult(COMPLEX_t *c, COMPLEX_t *a, COMPLEX_t *b);

//absolute value complex numbers
//|a|^2
double complex_abs2(COMPLEX_t *a);

//absolute value of a complex number
#define complex_abs(a)			sqrt(complex_abs2(a))

//scale a complex number
//c = c * scale
void complex_scale(COMPLEX_t *c, double scale);

//initialize a complex number
//a = real + i * imag
void complex_init(COMPLEX_t *a, double real, double imag);

//divide complex numbers
//c = a / b
void complex_div(COMPLEX_t *c, COMPLEX_t *a, COMPLEX_t *b);

//print complex
void complex_printf(COMPLEX_t *a);

#endif // COMPLEX_MATH_H_INCLUDED
