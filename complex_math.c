#include "complex_math.h"				//we use complex math

//global defines

//global variable

//add complex numbers
//c = a + b
void complex_add(COMPLEX_t *c, COMPLEX_t *a, COMPLEX_t *b) {
	c->real = a->real + b->real;
	c->imag = a->imag + b->imag;
}

//subtract complex numbers
//c = a - b
void complex_sub(COMPLEX_t *c, COMPLEX_t *a, COMPLEX_t *b) {
	c->real = a->real - b->real;
	c->imag = a->imag - b->imag;
}

//multiply complex numbers
//c = a * b
void complex_mult(COMPLEX_t *c, COMPLEX_t *a, COMPLEX_t *b) {
	c->real = a->real * b->real - a->imag * b->imag;
	c->imag = a->real * b->imag + a->imag * b->real;
}

//absolute value complex numbers
//|a|^2
double complex_abs2(COMPLEX_t *a) {
	return (a->real * a->real + a->imag * a->imag);
}

//absolute value of a complex number
#define complex_abs(a)			sqrt(complex_abs2(a))

//scale a complex number
//c = c * scale
void complex_scale(COMPLEX_t *c, double scale) {
	c->real = c->real * scale;
	c->imag = c->imag * scale;
}

//initialize a complex number
//a = real + i * imag
void complex_init(COMPLEX_t *a, double real, double imag) {
	a->real = real;
	a->imag = imag;
}

//divide complex numbers
//c = a / b
void complex_div(COMPLEX_t *c, COMPLEX_t *a, COMPLEX_t *b) {
	float tmp = 1.0 / complex_abs2(b);
	c->real = a->real * b->real + a->imag * b->imag;
	c->imag = a->real * (-b->imag) + a->imag * b->real;
	c->real = c->real * tmp;
	c->imag = c->imag * tmp;
}

//print complex
void complex_printf(COMPLEX_t *a) {
	if (a->imag > 0) printf("%f + i * %f", a->real, a->imag);
	else printf("%f - i * %f", a->real, -a->imag);
}

