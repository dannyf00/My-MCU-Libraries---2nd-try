/************************************************************************
	fft.h

    FFT Audio Analysis
    Copyright (C) 2011 Simon Inns

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Email: simon.inns@gmail.com

************************************************************************/

#ifndef _FFT_H
#define _FFT_H

#include <math.h>
#include <stdint.h>

typedef struct {
    int16_t real,imag;
} compx;                                    //����һ������ṹ

//#define FFT_N			128			//number of data points in fft

//see if standard int types are defined
//#ifndef int8_t
//#include <stdint.h>
//typedef char int8_t;
//typedef short int16_t;
//typedef long int32_t;
//typedef unsigned char uint8_t;
//typedef unsigned short uint16_t;
//typedef unsigned long uint32_t;
//#endif

// Function prototypes
//Output
//fr/fi contains the real and imaginary parts;
//take their square root to get the amplitude
//[0]=is the DC offset
//[1..FFT_N] contain the 1/2 * amplitude
//void fft_fix(/*short*/int16_t fr[], /*short*/int16_t fi[], /*short*/int16_t m);
void fft_fix(compx *f, /*short*/int16_t m);

//usage examples
/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fft_fix.h"

#define FFT_N			(1<<FFT_LOG2N)
#define FFT_LOG2N		5
#define FREQENCY		3

short real[FFT_N], imag[FFT_N], f[FFT_N];

int main() {
    int i;
    int t0, t1;

    printf("Hello world!\n");
    srand(time(NULL));						//initialize the random number generator

    for (i=0; i<FFT_N; i++) {
        real[i]=	1000+
                    10000*sin(2*3.1415926*3*i/FFT_N)+
                    1000*sin(2*3.1415926*4*i/FFT_N)+
                    100*sin(2*3.1415926*5*i/FFT_N)+
                    10*sin(2*3.1415926*6*i/FFT_N)+
                    10*(rand()/32768.0 - 0.5);
        imag[i]=0;
        printf("i=%4d, real=%6d\n", i, real[i]);
    }

    t0=clock();
    for (i=0; i<1; i++) fft_fix(real, imag, FFT_LOG2N);		//500 ticks / 100000
    t1=clock();
    printf("t0=%5d, t1=%5d, t1-t0=%5d\n\r", t0, t1, t1-t0);

    for (i=0; i<FFT_N/2; i++) {
        printf("i=%4d, real=%6d, imag = %6d, amp=%8.2f\n", i, real[i], imag[i], sqrt(real[i]*real[i]+imag[i]*imag[i]));

    }
    return 0;
}
*/
#endif
