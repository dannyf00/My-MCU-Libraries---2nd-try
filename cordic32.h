#ifndef _CORDIC32_H
#define _CORDIC32_H

#include <math.h>			//we use M_PI
#include <stdint.h>

// CORDIC based SIN and COS in 16 bit signed fixed point math
// Based on http://www.dcs.gla.ac.uk/~jhw/cordic/
// Pito 11/2016, for Maple Mini @72MHz
// Function is valid for arguments in range -pi/2 -- pi/2
// For values pi/2--pi: value = half_pi-(theta-half_pi) and similarly for values -pi---pi/2
//
// 1.0 = 16384
// 1/k = 0.6072529350088812561694
// pi = 3.1415926536897932384626
// Some useful Constants

//global defines
//#define cordic_1K 		0x26DD3B6A
//#define half_pi 		0x6487ED51
#define MUL32 			1073741824.000000
//#define CORDIC_NTAB 	32
#ifndef M_PI
#define M_PI			3.1415926536897932384626
#endif

//global variables
//cordic calculation
//theta = angle, in radian
//s = sin
//c = cosine
//n = iteration
void cordic32(int32_t theta, int32_t *s, int32_t *c, int32_t n);

#define FtoFP32(f)		((f) * MUL32)			//convert floating type to 32-bit fixed point
#define FP32toF(fp)		((fp) / MUL32)			//convert 32-bit fixed point to floating type

//USAGE:
/*
		time0=ticks();
		for (index=0; index<50; index++) {
			p_theta = D2R(index / 50.0);
			cordic32(FtoFP32(p_theta), &s, &c, 10);	//cordic32(p_theta * MUL32, &s, &c, 10);
			sin_c = FP32toF(s);						//sin_c = s/MUL32; 
			cosin_c = FP32toF(c);					//cosin_c = c/MUL32;
		}	
		time1=ticks() - time0;
*/
#endif
