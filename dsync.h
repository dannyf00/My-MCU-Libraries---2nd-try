#ifndef _DSYNC_H_INCLUDED
#define _DSYNC_H_INCLUDED

#include <math.h>						//we use math routines

//global defines
#define DFT_SIZE	256
#define AMP_GAIN	1000.0				//gain on current amplifier
#ifndef PI
#define PI			3.1415926
#endif
#define PIx2		(2*PI)

//global variables

//convert float to int
//no out-of-bound check
void dsync_f2i(float *dat_f, signed int *dat_i, int block_size);

//convert int to float
//no out-of-bound check
void dsync_i2f(signed int *dat_i, float *dat_f, int block_size);

//floating math version
//void de_DC a series
//not used
//void dsyncdedc_f(float *dat, int block_size);

//calculate impedance + phase shift from v/i data
void dsync_f(float *volt, float * amp, float *impedance, float *dphase, int block_size);

//interger versions
//void de_DC a series
//not used
//void dsyncdedc_i(int *dat, int block_size);

//calculate impedance + phase shift from v/i data
void dsync_i(int *volt, int * amp, float *impedance, float *dphase, int block_size);

#endif // DSYNC_H_INCLUDED
