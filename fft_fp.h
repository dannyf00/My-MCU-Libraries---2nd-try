#ifndef FFT_FP_H_INCLUDED
#define FFT_FP_H_INCLUDED

#include <math.h>
#include <stdint.h>

//fft_fp configuration
//#define FFT_N			128
//end fft_fp configuration

//make sure uint8/16/32_t types are included
//#ifndef uint8_t
//#include <stdint.h>
//typedef char int8_t;
//typedef short int16_t;
//typedef long int32_t;
//typedef unsigned char uint8_t;
//typedef unsigned short uint16_t;
//typedef unsigned long uint32_t;
//#endif

#define FFT_TYPE		int16_t								//16-bit type
#define PI 				3.1415926535897932384626433832795028841971               //定义圆周率值
#define FFT_FORWARD		0
#define FFT_INVERSE		1

typedef struct {
    FFT_TYPE real, imag;
} compx;

//source: http://www.jjj.de/fft/fftpage.html

/* fix_fft.c - Fixed-point in-place Fast Fourier Transform  */
/*
  All data are fixed-point short integers, in which -32768
  to +32768 represent -1.0 to +1.0 respectively. Integer
  arithmetic is used for speed, instead of the more natural
  floating-point.

  For the forward FFT (time -> freq), fixed scaling is
  performed to prevent arithmetic overflow, and to map a 0dB
  sine/cosine wave (i.e. amplitude = 32767) to two -6dB freq
  coefficients. The return value is always 0.

  For the inverse FFT (freq -> time), fixed scaling cannot be
  done, as two 0dB coefficients would sum to a peak amplitude
  of 64K, overflowing the 32k range of the fixed-point integers.
  Thus, the fix_fft() routine performs variable scaling, and
  returns a value which is the number of bits LEFT by which
  the output must be shifted to get the actual amplitude
  (i.e. if fix_fft() returns 3, each value of fr[] and fi[]
  must be multiplied by 8 (2**3) for proper scaling.
  Clearly, this cannot be done within fixed-point short
  integers. In practice, if the result is to be used as a
  filter, the scale_shift can usually be ignored, as the
  result will be approximately correctly normalized as is.

  Written by:  Tom Roberts  11/8/89
  Made portable:  Malcolm Slaney 12/15/94 malcolm@interval.com
  Enhanced:  Dimitrios P. Bouras  14 Jun 2006 dbouras@ieee.org
*/


/*
  Henceforth "short" implies 16-bit word. If this is not
  the case in your architecture, please replace "short"
  with a type definition which *is* a 16-bit word.
*/

/*
  Since we only use 3/4 of N_WAVE, we define only
  this many samples, in order to conserve data space.
*/

/*
  FIX_MPY() - fixed-point multiplication & scaling.
  Substitute inline assembly for hardware-specific
  optimization suited to a particluar DSP processor.
  Scaling ensures that result remains 16-bit.
*/

/*
  fix_fft() - perform forward/inverse fast Fourier transform.
  fr[n],fi[n] are real and imaginary arrays, both INPUT AND
  RESULT (in-place FFT), with 0 <= n < 2**m; set inverse to
  0 for forward transform (FFT), or 1 for iFFT.
*/
//int fix_fft(compx f[]/*short fr[], short fi[]*/, int16_t inverse, int16_t FFT_N);
int fft_fp(compx f[]/*short fr[], short fi[]*/, int16_t inverse, int16_t FFT_N);

//#define fft_fp	fix_fft

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fft_fp.h"

#define FFT_N			(1<<FFT_LOG2N)
#define FFT_LOG2N		5

compx *s;

int main(void) {
    int i;
    int t0, t1;

    //allocate the space
    s=malloc(FFT_N * sizeof(s[0]));

    //generate the data
    for(i=0; i<FFT_N; i++) {                       	//给结构体赋值
        s[i].real =	1000.0+ \
                    200.0*cos(2*PI*1*(3.6/360+1.0*i/FFT_N))+ \
                    3000.0*cos(2*PI*2*(1.8/360+1.0*i/FFT_N))+ \
                    4000.0*cos(2*PI*5*(1.8/360+1.0*i/FFT_N))+ \
                    1.0e1*rand()/RAND_MAX; 		//实部为正弦波FFT_N点采样，赋值为1
        s[i].imag=	1.0e1*rand()/RAND_MAX;                                //虚部为0
    }

    //print out the time-domain data
    printf("time-domain data...\n");
    for (i=0; i<FFT_N; i++)
        printf("i=%4d, real = %10d, imag = %10d, amp= %10.3f\n", i, s[i].real, s[i].imag, sqrt(s[i].real*s[i].real + s[i].imag*s[i].imag));

    //perform fft
    t0=clock();
    for (i=0; i<1; i++) fft_fp(s, FFT_FORWARD, FFT_N);                                        	//进行快速福利叶变换 750 clicks / 100000
    t1=clock();
    printf("t0=%5d, t1=%5d, t1-t0=%5d\n\r", t0, t1, t1-t0);					//750 clicks / 100000 rounds

    //printf the fft data
    //printf("post-FFT data...\n");
    for (i=0; i<FFT_N/2; i++)
        printf("i=%4d, real = %10d, imag = %10d, amp= %10.3f\n", i, s[i].real, s[i].imag, sqrt(s[i].real*s[i].real + s[i].imag*s[i].imag));

    //for(i=0; i<FFT_N; i++)                         	//求变换后结果的模值，存入复数的实部部分
    //s[i].real=sqrt(s[i].real*s[i].real+s[i].imag*s[i].imag);

    //printf the fft data
    //printf("mod-FFT data...\n");
    //for (i=0; i<FFT_N; i++)
    //printf("i=%4d, amp = %10.3f\n", i, s[i].real, s[i].imag);
    //while(1);

    return 0;
}
*/
#endif // FFT_FP_H_INCLUDED
