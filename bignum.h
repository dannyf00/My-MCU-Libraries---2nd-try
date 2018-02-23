#ifndef BIGNUM_H_INCLUDED
#define BIGNUM_H_INCLUDED

//#include "bignum.h"						//we use bignum routines

/*	bignum.c
	Implementation of large integer arithmetic: addition, subtraction,
		multiplication, and division.

	begun: February 7, 2002
	by: Steven Skiena
*/

/*
Copyright 2003 by Steven S. Skiena; all rights reserved.

Permission is granted for use in non-commerical applications
provided this copyright notice remains intact and unchanged.

This program appears in my book:

"Programming Challenges: The Programming Contest Training Manual"
by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.

See our website www.programming-challenges.com for additional information.

This book can be ordered from Amazon.com at

http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/

*/


#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#define	MAXDIGITS	100		/* maximum length bignum */

#define PLUS		1		/* positive sign bit */
#define MINUS		-1		/* negative sign bit */

typedef struct {
        char digits[MAXDIGITS];         /* represent the number */
	int signbit;			/* 1 if positive, -1 if negative */
        int lastdigit;			/* index of high-order digit */
} bignum;


#if 0
void print_bignum(bignum *n);
#else
char *print_bignum(char *str, bignum *n);
#endif

void int_to_bignum(int s, bignum *n);

void initialize_bignum(bignum *n);


int max(int a, int b);

//*	c = a +-/* b;

void add_bignum(bignum *a, bignum *b, bignum *c);


void subtract_bignum(bignum *a, bignum *b, bignum *c);

int compare_bignum(bignum *a, bignum *b);

void zero_justify(bignum *n);


/* multiply n by 10^d */
void digit_shift(bignum *n, int d);

void multiply_bignum(bignum *a, bignum *b, bignum *c);

void divide_bignum(bignum *a, bignum *b, bignum *c);
#endif // BIGNUM_H_INCLUDED
