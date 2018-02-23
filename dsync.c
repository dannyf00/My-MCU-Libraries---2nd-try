#include "dsync.h"						//we use digital synchornous detector

//global defines

//global variables

//convert float to int
//no out-of-bound check
void dsync_f2i(float *dat_f, signed int *dat_i, int block_size) {
	do {
	*dat_i++ = *dat_f++;
	} while (block_size--);
}

//convert int to float
//no out-of-bound check
void dsync_i2f(signed int *dat_i, float *dat_f, int block_size) {
	do {
	*dat_f++ = *dat_i++;
	} while (block_size--);
}

//void de_DC a series
//not used
static void dedc_f(float *dat, int block_size) {
	int i;
	float avg=0;
	for (i=0; i<block_size; i++) avg += dat[i];	//calculate the sum
	avg = avg / block_size;						//calculate the average
	for (i=0; i<block_size; i++) dat[i] -= avg;	//de-dc the sample
}

//calculate impedance + phase shift from v/i data
void dsync_f(float *volt, float * amp, float *impedance, float *dphase, int block_size) {
	int i;
	float va=0;							//volt * amp
	float v_rms=0;						//v_rms
	float a_rms=0;						//a_rms
	float v, a;

	//de-DC the data series
	dedc_f(volt, block_size);
	dedc_f(amp, block_size);
/*	//de-DC the data series - for speed
	v_rms=a_rms=0;						//use those variables to de-DC the volt / amp series
	for (i=0; i<block_size; i++) {
		v_rms+=volt[i];					//sum up the series
		a_rms+=amp[i];					//sum up the series
	}
	v_rms /= block_size;				//calculate the average
	a_rms /= block_size;
	for (i=0; i<block_size; i++) {
		volt[i]-=v_rms;					//de-DC
		amp[i] -=a_rms;
	}
	v_rms = a_rms = 0;					//reset v_rms/a_rms
*/
	//for (i=0; i<block_size; i++) printf("i=%10d, volt=%10.4f, curt=%10.4f\n\r", i, volt[i], amp[i]);
	//return;
	for (i=0; i<block_size; i++) {
		v=volt[i];						//to save time
		a=(float)amp[i] / AMP_GAIN;
		va+=v*a;						//va product
		v_rms+=v*v;						//v*v
		a_rms+=(float)a*a;				//a*a
		//printf("i=%10d, v=%10.4f, a=%10.4f, va=%10.4f, v_rms=%10.4f, a_rms=%10.4f\n\r", i, v, a, va, v_rms, a_rms);
	};
	//printf("sum:va=%10.4f, v_rms=%10.4f, a_rms=%10.4f\n\r", va, v_rms, a_rms);
	va /= block_size;					//calculate the averages
	v_rms = sqrt(v_rms / block_size);
	a_rms = sqrt(a_rms / block_size);
	//printf("avg:va=%10.4f, v_rms=%10.4f, a_rms=%10.4f\n\r", va, v_rms, a_rms);
	*impedance=v_rms / a_rms;			//impedance
	*dphase=acos(va / (v_rms * a_rms));	//calculate phase shift
	//printf("va=%10.4f, v_rms=%10.4f, a_rms=%10.4f\n\r", va, v_rms, a_rms);
	//printf("impedance=%10.4f, dphase=%10.4f\n\r", *impedance, *dphase);

}

//void de_DC a series
//not used
static void dedc_i(int *dat, int block_size) {
	int i;
	float avg=0;
	for (i=0; i<block_size; i++) avg += dat[i];	//calculate the sum
	avg = avg / block_size;						//calculate the average
	for (i=0; i<block_size; i++) dat[i] -= avg;	//de-dc the sample
}

//calculate impedance + phase shift from v/i data
void dsync_i(int *volt, int * amp, float *impedance, float *dphase, int block_size) {
	int i;
	float va=0;							//volt * amp
	float v_rms=0;						//v_rms
	float a_rms=0;						//a_rms
	float v, a;

	//de-DC the data series
	dedc_i(volt, block_size);
	dedc_i(amp, block_size);
/*	//de-DC the data series - for speed
	v_rms=a_rms=0;						//use those variables to de-DC the volt / amp series
	for (i=0; i<block_size; i++) {
		v_rms+=volt[i];					//sum up the series
		a_rms+=amp[i];					//sum up the series
	}
	v_rms /= block_size;				//calculate the average
	a_rms /= block_size;
	for (i=0; i<block_size; i++) {
		volt[i]-=v_rms;					//de-DC
		amp[i] -=a_rms;
	}
	v_rms = a_rms = 0;					//reset v_rms/a_rms
*/
	//for (i=0; i<block_size; i++) printf("i=%10d, volt=%10.4f, curt=%10.4f\n\r", i, volt[i], amp[i]);
	//return;
	for (i=0; i<block_size; i++) {
		v=volt[i];						//to save time
		a=(float)amp[i] / AMP_GAIN;
		va+=v*a;						//va product
		v_rms+=v*v;						//v*v
		a_rms+=1.0*a*a;						//a*a
		//printf("i=%10d, v=%10.4f, a=%10.4f, va=%10.4f, v_rms=%10.4f, a_rms=%10.4f\n\r", i, v, a, va, v_rms, a_rms);
	};
	//printf("sum:va=%10.4f, v_rms=%10.4f, a_rms=%10.4f\n\r", va, v_rms, a_rms);
	va /= block_size;					//calculate the averages
	v_rms = sqrt(v_rms / block_size);
	a_rms = sqrt(a_rms / block_size);
	//printf("avg:va=%10.4f, v_rms=%10.4f, a_rms=%10.4f\n\r", va, v_rms, a_rms);
	*impedance=v_rms / a_rms;			//impedance
	*dphase=acos(va / (v_rms * a_rms));	//calculate phase shift
	//printf("impedance=%10.4f, dphase=%10.4f\n\r", *impedance, *dphase);

}
