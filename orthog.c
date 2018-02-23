#include "orthog.h"						//orthogoal approach to detect rms + phase

//global defines

//global variables
float sin_tbl[DFT_SIZE], cos_tbl[DFT_SIZE];

//void de_DC a series
//not used
static void dedc_f(float *dat, int block_size) {
	int i;
	float avg=0;
	for (i=0; i<block_size; i++) avg += dat[i];	//calculate the sum
	avg = avg / block_size;						//calculate the average
	for (i=0; i<block_size; i++) dat[i] -= avg;	//de-dc the sample
}

//initialize the sin / cos tables
void orthoginit_f(int block_size) {
	int i;
	float radian;
	for (i=0; i<block_size; i++) {
		radian=(float) i / block_size*PIx2;
		sin_tbl[i]=sin(radian);
		cos_tbl[i]=cos(radian);
	}
}

//calculate rms, and phase shift relative to a 0 degree signal
void orthogrms_f(float *dat, float *rms, float *phase, int block_size) {
	int i;
	float tmp, tmp_real=0, tmp_imag=0;

	//deDC the series
	dedc_f(dat, block_size);
	for (i=0; i<block_size; i++) {
		tmp=dat[i];						//to save time
		tmp_real+=tmp * sin_tbl[i];		//calculate the real part
		tmp_imag+=tmp * cos_tbl[i];		//calculate the imaginary part
	}
	*rms = sqrt((tmp_real * tmp_real + tmp_imag * tmp_imag));
	*phase = atan2(tmp_imag, tmp_real);
	//if (tmp_real * tmp_imag < 0) *phase += PI;
	//if (*phase<0) *phase += PI;
	//if (*phase>PI)*phase -= PI;
	//printf("tmp_real = %10.4f, tmp_imag = %10.4f\n\r", tmp_real, tmp_imag);
}

//user sees this routine only
//calculate impedance and phase
void orthog_f(float * volt, float *amp, float *impedance, float *phase, int block_size) {
	float volt_rms, volt_phase;
	float amp_rms, amp_phase;
	orthogrms_f(volt, &volt_rms, &volt_phase, block_size);	//calculate volt's rms and phase (vs. reference signal)
	orthogrms_f(amp, &amp_rms, &amp_phase, block_size);		//calculate amp's rms and phase (vs. reference signal)
	*impedance = volt_rms / amp_rms * AMP_GAIN;				//calculate impedance
	*phase = volt_phase - amp_phase;						//calculate relative phase shift
	if (*phase > PI/2) *phase -=PIx2;						//limit phase to +/-90 degrees
	if (*phase <-PI/2) *phase +=PIx2;
}
