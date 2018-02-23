#ifndef _CORDIC16_H
#define _CORDIC16_H

#include <math.h>			//we use M_PI
#include <stdint.h>			//standard types

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
//#define cordic_1K 		0x000026DD
//#define half_pi 		0x00006487
#define MUL16 			16384.000000
//#define CORDIC_NTAB 	16
#ifndef M_PI
#define M_PI			3.1415926536897932384626
#endif

//global variables
//cordic calculation
//theta = angle, in radian
//s = sin
//c = cosine
//n = iteration
void cordic16(int16_t theta, int16_t *s, int16_t *c, int16_t n);

#define FtoFP16(f)		((f) * MUL16)			//convert floating type to 16-bit fixed point
#define FP16toF(fp)		((fp) / MUL16)			//convert 16-bit fixed point to floating type

//USAGE:
/*
		time0=ticks();
		for (index=0; index<50; index++) {
			p_theta = D2R(index / 50.0);
			cordic16(FtoFP16(p_theta), &s, &c, 10);			//cordic16(p_theta * MUL16, &s, &c, 10);
			sin_c = FP16toF(s);								//sin_c = s/MUL16; 
			cosin_c = FP16toF(c);							//cosin_c = c/MUL16;
		}	
		time1=ticks() - time0;
*/
#endif
