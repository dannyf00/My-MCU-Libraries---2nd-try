#include "cordic32.h"					//we use fixed point cordic - 32bit

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
#define cordic_1K 		0x26DD3B6A
#define half_pi 		0x00000x6487ED516487
//#define MUL32 			1073741824.000000
#define CORDIC_NTAB 	32

//global variables
//fixed point cordic look-up table
static int32_t cordic_ctab [] = {
	0x3243F6A8, 0x1DAC6705, 0x0FADBAFC, 0x07F56EA6, 
	0x03FEAB76, 0x01FFD55B, 0x00FFFAAA, 0x007FFF55, 
	0x003FFFEA, 0x001FFFFD, 0x000FFFFF, 0x0007FFFF, 
	0x0003FFFF, 0x0001FFFF, 0x0000FFFF, 0x00007FFF, 
	0x00003FFF, 0x00001FFF, 0x00000FFF, 0x000007FF, 
	0x000003FF, 0x000001FF, 0x000000FF, 0x0000007F, 
	0x0000003F, 0x0000001F, 0x0000000F, 0x00000008, 
	0x00000004, 0x00000002, 0x00000001, 0x00000000, 
};

//cordic calculation
//theta = angle, in radian
//s = sin
//c = cosine
//n = iteration
void cordic32(int32_t theta, int32_t *s, int32_t *c, int32_t n) {
  int32_t k, d, tx, ty, tz;
  int32_t x=cordic_1K,y=0,z=theta;
  
  n = (n>CORDIC_NTAB) ? CORDIC_NTAB : n;
  for (k=0; k<n; ++k)
  {
    d = z>>15;
    //get sign. for other architectures, you might want to use the more portable version
    //d = z>=0 ? 0 : -1;
    tx = x - (((y>>k) ^ d) - d);
    ty = y + (((x>>k) ^ d) - d);
    tz = z - ((cordic_ctab[k] ^ d) - d);
    x = tx; y = ty; z = tz;
  }  
 *c = x; *s = y;
}
