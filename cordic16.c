#include "cordic16.h"				//we use fixed point cordic - 16bit

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
#define cordic_1K 		0x000026DD
#define half_pi 		0x00006487
//#define MUL16 			16384.000000
#define CORDIC_NTAB 	16

//global variables
//fixed point cordic look-up table
static int16_t cordic_ctab [] = {
	0x00003243, 0x00001DAC, 0x00000FAD, 0x000007F5, 
	0x000003FE, 0x000001FF, 0x000000FF, 0x0000007F, 
	0x0000003F, 0x0000001F, 0x0000000F, 0x00000007, 
	0x00000003, 0x00000001, 0x00000000, 0x00000000, 
};

//cordic calculation
//theta = angle, in radian
//s = sin
//c = cosine
//n = iteration
void cordic16(int16_t theta, int16_t *s, int16_t *c, int16_t n) {
  int16_t k, d, tx, ty, tz;
  int16_t x=cordic_1K,y=0,z=theta;
  
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
