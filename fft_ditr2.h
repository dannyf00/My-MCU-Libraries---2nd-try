#ifndef FFT_DITR2_H_INCLUDED
#define FFT_DITR2_H_INCLUDED

//#include "config.h"
#include <math.h>						//if lut_twd to be precalculated or generated. not used if lut_twd is precalculated
//#include <stdlib.h>					//we use rand()
#include <stdio.h>						//if printf is used
//#include <time.h>
//#include "fft_float.h"				//we use fft_floating point math

//hardware configuration
#define FFT_LOG2N			5
//#define USE_FFT_TWD_LUT				//use twddle factor array. comment out if to calculate twiddle factor using fft_cal()
//end hardware configuration

//global defines
#define FFT_N				(1ul<<FFT_LOG2N)		//2^n data points
#ifndef M_PI
  #define M_PI				3.14159265358979323846264338327950288
#endif

//global variables
//extern double lut_twd[FFT_N];						//twiddle factors


//douglas jones' fft_ditr2 modified to use look-up tables for sin/con calculations
void fft_ditr2(/*int n, */int m, double *x, double *y);

/**********************************************************/
/* fft.c                                                  */
/* (c) Douglas L. Jones                                   */
/* University of Illinois at Urbana-Champaign             */
/* January 19, 1992                                       */
/*                                                        */
/*   fft: in-place radix-2 DIT DFT of a complex input     */
/*                                                        */
/*   input:                                               */
/* n: length of FFT: must be a power of two               */
/* m: n = 2**m                                            */
/*   input/output                                         */
/* x: double array of length n with real part of data     */
/* y: double array of length n with imag part of data     */
/*                                                        */
/*   Permission to copy and use this program is granted   */
/*   under a Creative Commons "Attribution" license       */
/*   http://creativecommons.org/licenses/by/1.0/          */
/**********************************************************/
void fft_ditr2dj(/*int n, */int m, double *x, double *y);

//brutal force FFT - source unknown
//complex data type for the brutal force fft
typedef struct {
	double real, imag;
} compx;

//brutal force FFT, source unknown
void fft_float(int n, compx *xin);

//calculate the look-up tables
//n=FFT_N but only half of the cycle (FFT_N/2) is calculated
//results are saved in lut_twd[]
void lut_cal(void);


#endif // FFT_DITR2_H_INCLUDED
