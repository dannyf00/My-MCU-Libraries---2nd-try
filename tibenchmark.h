#ifndef TIBENCHMARK_H_INCLUDED
#define TIBENCHMARK_H_INCLUDED

//benchmark configuration
//#define BENCHMARK_FIR							//comment out if main_fir() is not being benchmarked
//#define BENCHMARK_DHRY							//comment out if main_dhry() is not being benchmarked
//#define BENCHMARK_WHET							//comment out if main_whet() is not being benchmarked
#define DHRY_LOOPS 100 /* Use this for slow or 16 bit machines */
//end benchmark configuration

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <stdint.h>
//if <stdint.h> isn't available
//typedef unsigned short uint16_t;				//if uint16_t isn't defined
//typedef unsigned long  uint32_t;				//if uint32_t isn't defined



//benchmark a function for a set number of times
void benchmark(void (*func)(void), uint32_t cnt);

/*******************************************************************************
*
* Name : 8-bit Math
* Purpose : Benchmark 8-bit math functions.
*
*******************************************************************************/
//typedef unsigned char UInt8;
//typedef unsigned short UInt16;
//typedef unsigned long UInt32;

void main_8bitmath(void);

/*******************************************************************************
*
* Name : 8-bit 2-dim Matrix
* Purpose : Benchmark copying 8-bit values.
*
*******************************************************************************/
void main_8bit2dmatrix(void);

/*******************************************************************************
*
* Name : 8-bit Switch Case
* Purpose : Benchmark accessing switch statement using 8-bit value.
*
*******************************************************************************/
void main_8bitswitchcase(void);

/*******************************************************************************
*
* Name : 16-bit Math
* Purpose : Benchmark 16-bit math functions.
*
*******************************************************************************/
void main_16bitmath(void);

/*******************************************************************************
*
* Name : 16-bit 2-dim Matrix
* Purpose : Benchmark copying 16-bit values.
*
*******************************************************************************/
void main_16bit2dmatrix(void);

/*******************************************************************************
*
* Name : 16-bit Switch Case
* Purpose : Benchmark accessing switch statement using 16-bit value.
*
*******************************************************************************/
void main_16bitswitchcase(void);

/*******************************************************************************
*
* Name : 32-bit Math
* Purpose : Benchmark 32-bit math functions.
*
*******************************************************************************/
#include <math.h>
void main_32bitmath(void);

/*******************************************************************************
*
* Name : Floating-point Math
* Purpose : Benchmark floating-point math functions.
*
*******************************************************************************/
void main_fpmath(void);

/*******************************************************************************
*
* Name : Matrix Multiplication
* Purpose : Benchmark multiplying a 3x4 matrix by a 4x5 matrix.
* Matrix contains 16-bit values.
*
*******************************************************************************/
void main_matrixmul(void);

/*******************************************************************************
*
* Name : FIR Filter
* Purpose : Benchmark an FIR filter. The input values for the filter
* is an array of 51 16-bit values. The order of the filter is
* 17.
*
*******************************************************************************/
//#ifdef MSP430
//#include "msp430x14x.h"
//#endif
#include <math.h>
#define FIR_LENGTH 17
void main_fir(void);

/*******************************************************************************
*
* Name : Dhrystone
* Purpose : Benchmark the Dhrystone code. This benchmark is used to gauge
* the performance of the microcontroller in handling pointers,
* structures and strings.
*
*******************************************************************************/
#include <stdio.h>
#include <string.h>
void main_dhry(void);

/*******************************************************************************
*
* Name : Whetstone
* Purpose : Benchmark the Whetstone code. The code focuses on scientific
* functions such as sine, cosine, exponents and logarithm on
* fixed and floating point numbers.
*
*******************************************************************************/
void main_whet (void);

#endif // TIBENCHMARK_H_INCLUDED
