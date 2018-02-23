//#include <stdio.h>
#include <stdlib.h>						//we use rand()
#include <math.h>						//we use math functions
#include "ieee1057.h"					//we use ieee1057 prototypes

//measurement configuration
//operating frequency
double f_osc=10000.0;					//sample frequency, in hz
//impedance measurement
double Rm=1000.0;					//measurement resistor, in ohm
//end measurement configuration

#define PI					3.14159265359	//pi
#define _2PI				(2*PI)		//2 * pi

unsigned short voltn[M], curtn[M];				//data samples
FITTED_COSINE_T volt, curt;			//voltage / current vectors
IMPEDANCE_T dut;					//device undertest

//generate adc data
void data_gen(	unsigned short length, 		//length of data
                unsigned short *buffer,		//output data buffer
                double A,					//gain for the sine term
                double B,					//gain for the cosine term
                double C,					//constant
                double error_gain			//gain for the error term
             ) {
    unsigned short n;						//loop index

    //srand(1235);							//seed the random number generator
    for (n=0; n<length; n++) buffer[n]=	A * cos(_2PI * f_osc * n / N) +		//sine term
										B * sin(_2PI * f_osc * n / N) +		//cosine term
                                        C +								//constant
                                        error_gain * (rand() / 32768.0 - 0.5);	//error term, mean = 0.0
    //return;
}

//generate adc data
void data_gen1(	unsigned short length, 		//length of data
                unsigned short *buffer_v,	//output data buffer
                unsigned short *buffer_c	//output data buffer
             ) {
    unsigned short n;						//loop index
	double amplitude = 100;					//osc amplitude
	double theta_v = 10.0 / 360 * _2PI;		//voltage signal

	//set up dut
	dut.Z = 1000;							//dut's impedance
	dut.theta = -45.0 / 360 * _2PI;			//theta. - for capacitance and + for inductance. converting from degrees to radius
	dut.Zr = dut.Z * cos(dut.theta);
	dut.Zi = dut.Z * sin(dut.theta);

    //srand(1235);							//seed the random number generator
    for (n=0; n<length; n++) {
    	buffer_v[n]=	amplitude * cos(_2PI * f_osc * n / N + theta_v) +		//cosine term
                    //B * sin(_2PI * f_osc * n / N) +		//sine term
                    500 +								//constant
                    0.01 * amplitude * (rand() / 32768.0 - 0.5);	//error term, mean = 0.0
    	buffer_c[n]=	- 1* amplitude / dut.Z * Rm * cos(_2PI * f_osc * n / N + theta_v + dut.theta) +		//cosine term. negative due to the opamp being out of phase
                    //B * sin(_2PI * f_osc * n / N) +		//sine term
                    1000 +								//constant
                    0.01 * amplitude * (rand() / 32768.0 - 0.5);	//error term, mean = 0.0
		//printf("buffer_v[%4d] = %10d, buffer_c[%4d] = %10d\n", n, buffer_v[n], n, buffer_c[n]);
    }
    //return;
}

//ieee-std-1057, non-matrix 3 parameter sine curve fitting
//ieee-std-1057 1994, P19
void ieee1057_3(unsigned short length,		//sample data length
                unsigned short * buffer,	//input sample data buffer
                FITTED_COSINE_T * output	//vector data output
               ) {
    double tmp;								//temperary variable
    unsigned short n;						//index
    double alphan, betan;					//sine / cosine terms
    double sum_yn=0, sum_alphan=0, sum_betan=0;	//define the sums, on P19
    double sum_alphanxbetan=0, sum_alphan2=0, sum_betan2=0;	//define the sums, on P19
    double sum_ynxalphan=0, sum_ynxbetan=0, sum_yn2=0;	//define the sums, on P19
    double Xn, Xd;								//temp variables used in calculation

    //calculate signal sums
    for (n=0; n<length; n++) {
        //calculate alpha / beta
        tmp = _2PI * f_osc * n / N;
        alphan=cos(tmp/*_2PI * f_osc * n / N*/);
        betan=sin(tmp/*_2PI * f_osc * n / N*/);

        //caulate the sums
        sum_yn += buffer[n];
        sum_alphan += alphan;
        sum_betan += betan;
        sum_alphanxbetan += alphan * betan;
        sum_alphan2 += alphan * alphan;
        sum_betan2 += betan * betan;
        sum_ynxalphan += buffer[n] * alphan;
        sum_ynxbetan += buffer[n] * betan;
        sum_yn2 += ((double)buffer[n]) * buffer[n];	//to avoid overflow
    }

    //calculate An/Ad
    Xn = 	(sum_ynxalphan - sum_alphan * sum_yn / M) / (sum_alphanxbetan - sum_alphan * sum_betan / M) -
            (sum_ynxbetan - sum_betan * sum_yn / M) / (sum_betan2 - sum_betan * sum_betan / M);
    Xd =	(sum_alphan2 - sum_alphan * sum_alphan / M) / (sum_alphanxbetan - sum_alphan * sum_betan / M) -
            (sum_alphanxbetan - sum_betan * sum_alphan / M) / (sum_betan2 - sum_betan * sum_betan / M);
    output->A = Xn / Xd;
    Xn =	(sum_ynxalphan - sum_alphan * sum_yn / M) / (sum_alphan2 - sum_alphan * sum_alphan / M) -
            (sum_ynxbetan - sum_betan * sum_yn / M) / (sum_alphanxbetan - sum_betan * sum_alphan / M);
    Xd =	(sum_alphanxbetan - sum_alphan * sum_betan / M) / (sum_alphan2 - sum_alphan * sum_alphan / M) -
            (sum_betan2 - sum_betan * sum_betan / M) / (sum_alphanxbetan - sum_betan * sum_alphan / M);
    output->B = Xn / Xd;
    output->C = sum_yn / M - output->A * sum_alphan / M - output->B * sum_betan / M;

    //alternative output
    output->A0 = sqrt(output->A * output->A + output->B * output->B);
    output->theta = atan(-output->B / output->A);
    //output->theta += (output->A < 0)? PI: 0;
}

//calculate impedance (Zdut)
//measurement approach: autobalancing bridge
//connection:
//
//            - volt (sampling point)                - curt (sampling point)
//            |                                      |
//            |                                      |
//            |    ------               ------       |
// Vosc---------- | Zdut |-------------|  Rm  |-------
// (freq=f_osc)    ------      |        ------       |
//                             |                     |
//                             |       |------|      |
//                             |-------|-     |      |
//                                     |Amp  O|------|
//                             |-------|+     |
//                             |       |------|
//                           Vbias
//                             |
//                             |
//                            --- (GND)
//                             -
//
void impedance(FITTED_COSINE_T * voltage, FITTED_COSINE_T * current, IMPEDANCE_T * dut) {
    //double tmp;								//temperary variable

    //calculate current through Rm
    //tmp = current.A0 / Rm;
    dut->Z = voltage->A0 * Rm / current->A0;		// tmp;
    dut->theta = /*-*/(current->theta - voltage->theta);	//eliminate '-' as the current signal is out of phase.
    dut->Zi= dut->Z * sin(dut->theta);
    dut->Zr= dut->Z * cos(dut->theta);
    dut->Q = tan(fabs(dut->theta));

    //calculate L or C
    if (dut->theta < 0) {					//capacitive load
        dut->LC = -1.0 / (dut->Zi * _2PI * f_osc);	//calculate C, in f
    } else {
        dut->LC = dut->Zi / (_2PI * f_osc);	//calculate L, in H
    }
}

//perform the calculation for dut's impedance / LCR parameters
void Z_measure(	unsigned short length,		//length of data sample
				unsigned short *voltage,	//voltage data array
				unsigned short *current,	//current data array
				IMPEDANCE_T *dut) 			//device data measurement. Output
				{
	//FITTED_COSINE_T volt, curt;			//temp variables.
	ieee1057_3(length, voltage, &volt);	//covert the voltage
	ieee1057_3(length, current, &curt);		//covert the current
	//curt.theta = - curt.theta;					//current signal measured 180 degrees opposite
	impedance(&volt, &curt, dut);				//calculate the impedance
}

