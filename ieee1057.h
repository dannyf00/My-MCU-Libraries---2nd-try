#ifndef IEEE1057_H_INCLUDED
#define IEEE1057_H_INCLUDED

//configuration
#define M		100						//number of data samples, unsigned short
#define N 		(M * f_osc / 10)				//sample per period

//specified in ieee1057.c
//operating frequency
//double f_osc=10000.0;					//sample frequency, in hz
//impedance measurement
//double Rm=1000.0;					//measurement resistor, in ohm
//end configuration

//#define PI					3.14159265359	//pi
//#define _2PI				(2*PI)		//2 * pi

typedef struct {
    double A, B, C;			//fitted cosine wave: yn = A * cosine(wt) + B * sine(wt) + C
    double A0, theta;		//fitted cosine wave: yn = A0 * cosine(wt + theta) + C
} FITTED_COSINE_T;

typedef struct {
    double Z;				//parallel / serial impedance
    double Zr, Zi;			//parallel/serial impmedance, real and imaginary
    //double Sr, Si;		//serial impedance, real and imaginary
    double theta;			//angles
    double Q;				//Q factor
    double LC;				//dut's resistance, L(uh) or C(ph)
} IMPEDANCE_T;

extern unsigned short voltn[M], curtn[M];				//data samples
//FITTED_COSINE_T volt, curt;			//voltage / current vectors
//double f_osc=10000.0;					//sample frequency, in hz

//impedance measurement
//double Rm=1000.0;					//measurement resistor, in ohm
extern IMPEDANCE_T dut;					//device undertest

//generate adc data
void data_gen(	unsigned short length, 		//length of data
                unsigned short *buffer,		//output data buffer
                double A,					//gain for the sine term
                double B,					//gain for the cosine term
                double C,					//constant
                double error_gain			//gain for the error term
             );

//generate adc data
void data_gen1(	unsigned short length, 		//length of data
                unsigned short *buffer_v,	//output data buffer
                unsigned short *buffer_c	//output data buffer
             );

//ieee-std-1057, non-matrix 3 parameter sine curve fitting
//ieee-std-1057 1994, P19
void ieee1057_3(unsigned short length,		//sample data length
                unsigned short * buffer,	//input sample data buffer
                FITTED_COSINE_T * output	//vector data output
               );

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
void impedance(FITTED_COSINE_T * voltage, FITTED_COSINE_T * current, IMPEDANCE_T * dut);

//perform the calculation for dut's impedance / LCR parameters
void Z_measure(	unsigned short length,		//length of data sample
				unsigned short *voltage,	//voltage data array
				unsigned short *current,	//current data array
				IMPEDANCE_T *dut 			//device data measurement. Output
				);

#endif // IEEE1057_H_INCLUDED
