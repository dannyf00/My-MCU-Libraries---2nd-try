#ifndef FFT_H_INCLUDED
#define FFT_H_INCLUDED

#include <math.h>					//sin()/cos()
#include <stdio.h>					//int16_t
#include <stdint.h>					//int16_t

/*********************************************************************
                         快速福利叶变换C函数
函数简介：此函数是通用的快速傅里叶变换C语言函数，移植性强，以下部分不依
          赖硬件。此函数采用联合体的形式表示一个复数，输入为自然顺序的复
          数（输入实数是可令复数虚部为0），输出为经过FFT变换的自然顺序的
          复数
使用说明：使用此函数只需更改宏定义FFT_N的值即可实现点数的改变，FFT_N的
          应该为2的N次方，不满足此条件时应在后面补0
函数调用：FFT(s);
作    者：吉帅虎
时    间：2010-2-20
版    本：Ver1.0
参考文献：

**********************************************************************/
//fft configuration
#define USE_FFT_TWD_LUT														//if pre-calculated twiddle factors are used
#define FFT_LOG2N	8
#define FFT_N 		(1ul<<FFT_LOG2N)											//128	                                                  //定义福利叶变换的点数
#define FFT_TYPE	double
//end fft configuration

#define PI 			3.1415926535897932384626433832795028841971               //定义圆周率值

typedef struct {
    FFT_TYPE real,imag;
} compx;                                    //定义一个复数结构
//struct compx s[FFT_N];                                              //FFT输入和输出：从S[1]开始存放，根据大小自己定义

//calculat the look-up table - used only if USE_FFT_TWD_LUT is commented out
void lut_cal(void);

/*****************************************************************
函数原型：void FFT(struct compx *xin,int N)
函数功能：对输入的复数组进行快速傅里叶变换（FFT）
输入参数：*xin复数结构体组的首地址指针，struct型
*****************************************************************/
void fft_float(int16_t FFTi_LOG2N, compx *xin);
void fft_float2(int16_t FFTi_LOG2N, compx *xin);

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fft_float.h"

#define FFT_N			(1<<FFT_LOG2N)
#define FFT_LOG2N		5

compx s[FFT_N];

int main(void) {
    int i;
    int t0, t1;

    srand(time(NULL));
    //generate the data
    for(i=0; i<FFT_N; i++) {                       	//给结构体赋值
        s[i].real =	1.0+ \
        			2.0*cos(2*PI*1*(3.6/360+1.0*i/FFT_N))+ \
        			3.0*cos(2*PI*4*(1.8/360+1.0*i/FFT_N))+ \
        			4.0*cos(2*PI*6*(1.8/360+1.0*i/FFT_N))+ \
        			0.51*(rand()/32768.0 - 0.5); 		//实部为正弦波FFT_N点采样，赋值为1
        s[i].imag=0;                                //虚部为0
    }

	//print out the time-domain data
	printf("time-domain data...\n");
	for (i=0; i<FFT_N; i++)
		printf("i=%4d, real = %10.7f, imag = %10.7f, amp= %10.5f\n", i, s[i].real, s[i].imag, sqrt(s[i].real*s[i].real + s[i].imag*s[i].imag));

	//perform fft
    t0=clock();
    for (i=0; i<1; i++) fft_float(s, FFT_N);                                        	//进行快速福利叶变换	11212 clicks / 100000
    t1=clock();
    printf("t0=%5d, t1=%5d, t1-t0=%5d\n\r", t0, t1, t1-t0);

	//printf the fft data
	//printf("post-FFT data...\n");
	for (i=0; i<FFT_N/2; i++)
		printf("i=%4d, real = %10.7f, imag = %10.7f, amp= %10.5f\n", i, s[i].real/FFT_N, s[i].imag/FFT_N, sqrt(s[i].real*s[i].real + s[i].imag*s[i].imag)/((i==0)?FFT_N:(FFT_N/2)));

    //for(i=0; i<FFT_N; i++)                         	//求变换后结果的模值，存入复数的实部部分
       //s[i].real=sqrt(s[i].real*s[i].real+s[i].imag*s[i].imag);

	//printf the fft data
	//printf("mod-FFT data...\n");
	//for (i=0; i<FFT_N; i++)
		//printf("i=%4d, amp = %10.7f\n", i, s[i].real, s[i].imag);
    //while(1);
    return 0;
}
*/

#endif // FFT_H_INCLUDED
