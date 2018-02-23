#ifndef DFT_H_INCLUDED
#define DFT_H_INCLUDED

//
// dft2.c - Basic, but slightly more efficient DFT
// Written by Ted Burke
// Last updated 10-12-2013
//
// To compile:
//    gcc dft2.c -o dft2.exe
//
// To run:
//    dft2.exe
//

#include <stdint.h>						//use float

// N is assumed to be greater than 4 and a power of 2
#define _DFT16_N	16					//***cannot be changed***
#define _DFT32_N	32					//***cannot be changed***
#define _DFT64_N	64					//***cannot be changed***
#define _DFT_PIx2 	(3.1415926*2)		//6.2832		//PIx2
extern const float _DFT16_TF[];			//64-point twiddle factors
extern const float _DFT32_TF[];			//64-point twiddle factors
extern const float _DFT64_TF[];			//64-point twiddle factors

//64 point dft-floating point
//x[64]: real input data
//Xre[64]: real output real elements
//Xim[64]: real output imaginary elements
//P[64]: real output power elements
void dft16(float *x, float *Xre, float *Xim); float dft16_power(float *x, float *Xre, float *Xim, float *P);
void dft32(float *x, float *Xre, float *Xim); float dft32_power(float *x, float *Xre, float *Xim, float *P);
void dft64(float *x, float *Xre, float *Xim); float dft64_power(float *x, float *Xre, float *Xim, float *P);

#endif // DFT64_H_INCLUDED
