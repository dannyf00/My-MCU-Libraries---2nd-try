#ifndef BENCHMARK_TI_H_INCLUDED
#define BENCHMARK_TI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

//typedef unsigned char UInt8;

//run bencharmk a few times
unsigned long benchmark(int count, void (*f_ptr)(void));

//TI MSP430 competitive benchmark - http://www.ti.com/lit/an/slaa205c/slaa205c.pdf
/*******************************************************************************
*
* Name : 8-bit Math
* Purpose : Benchmark 8-bit math functions.
*
*******************************************************************************/

void main_8(void);

/*******************************************************************************
*
* Name : 8-bit 2-dim Matrix
* Purpose : Benchmark copying 8-bit values.
*
*******************************************************************************/
void main_8m (void);

/*******************************************************************************
*
* Name : 8-bit Switch Case
* Purpose : Benchmark accessing switch statement using 8-bit value.
*
*******************************************************************************/
void main_8sw(void);

/*******************************************************************************
*
* Name : 16-bit Math
* Purpose : Benchmark 16-bit math functions.
*
*******************************************************************************/
void main_16(void);

/*******************************************************************************
*
* Name : 16-bit 2-dim Matrix
* Purpose : Benchmark copying 16-bit values.
*
*******************************************************************************/
void main_16m(void);

/*******************************************************************************
*
* Name : 16-bit Switch Case
* Purpose : Benchmark accessing switch statement using 16-bit value.
*
*******************************************************************************/
void main_16sw(void);

/*******************************************************************************
*
* Name : 32-bit Math
* Purpose : Benchmark 32-bit math functions.
*
*******************************************************************************/
void main_32(void);

/*******************************************************************************
*
* Name : Floating-point Math
* Purpose : Benchmark floating-point math functions.
*
*******************************************************************************/
void main_f(void);

/*******************************************************************************
*
* Name : Matrix Multiplication
* Purpose : Benchmark multiplying a 3x4 matrix by a 4x5 matrix.
* Matrix contains 16-bit values.
*
*******************************************************************************/
void main_mmlt(void);

/*******************************************************************************
*
* Name : FIR Filter
* Purpose : Benchmark an FIR filter. The input values for the filter
* is an array of 51 16-bit values. The order of the filter is
* 17.
*
*******************************************************************************/
void main_fir(void);

#endif // BENCHMARK_TI_H_INCLUDED
