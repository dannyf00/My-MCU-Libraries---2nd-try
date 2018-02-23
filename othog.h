#ifndef _ORTHOG_H_INCLUDED
#define _ORTHOG_H_INCLUDED

#include <math.h>						//we use math routines

//global defines
#define DFT_SIZE	256
#define AMP_GAIN	1000.0				//gain on current amplifier
#ifndef PI
#define PI			3.1415926
#endif
#define PIx2		(2*PI)


//global variables
//extern float sin_tbl[DFT_SIZE], cos_tbl[DFT_SIZE];

//initialize the sin / cos tables
void othoginit_f(int block_size);

//calculate impedance and phase
void othog_f(float * volt, float *amp, float *impedance, float *phase, int block_size);

#endif // OTHOG_H_INCLUDED
