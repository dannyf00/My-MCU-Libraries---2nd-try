#ifndef TC_H_INCLUDED
#define TC_H_INCLUDED

enum TC_CURVE {
	TC_CURVE1 = 0,			//thermocouple curve 1
	TC_CURVE2,				//thermocouple curve 2
	TC_CURVE3,				//thermocouple curve 3
	TC_CURVE4				//thermocouple curve 4
};

//nist thermocouple coefficients
/*************************************
* This section contains coefficients of approximate inverse
* functions for type B/E/J/K/N/R/S/T thermocouples for the subranges of
* temperature and voltage listed below. The range of errors of
* the approximate inverse function for each subrange is also given.
* The coefficients are in units of °C and mV and are listed in
* the order of constant term up to the highest order.
* The equation is of the form t_90 = d_0 + d_1*E + d_2*E^2 + ...
*     + d_n*E^n,
* where E is in mV and t_90 is in °C.*/

//structure to hold temperature coefficients
//nist
typedef struct {
	double mV_LOW;			//low-end of the boundary, in mv
	double mV_HIGH;			//high-end of the boundary, in mv
	double coef[10];		//tc coefficient, 9 order (d_0 + d1..9)
} TCCOEF_TYPEDEF;

//structure to hold temperature coefficients
//5th order approximation
typedef struct {
	double mV_LOW;			//low-end of the boundary, in mv
	double mV_HIGH;			//high-end of the boundary, in mv
	double coef[6];			//tc coefficient, 5 order (d_0 + d1..5)
} TCCOEF5_TYPEDEF;

//thermocoupler coefficients
//array split to reduce size
extern const TCCOEF_TYPEDEF TCB_table[];

extern const TCCOEF_TYPEDEF TCE_table[];

extern const TCCOEF_TYPEDEF TCJ_table[];

extern const TCCOEF_TYPEDEF TCK_table[];

extern const TCCOEF_TYPEDEF TCN_table[];

extern const TCCOEF_TYPEDEF TCR_table[];

extern const TCCOEF_TYPEDEF TCS_table[];

extern const TCCOEF_TYPEDEF TCT_table[];

//5th order approximation
/*						//K       	//J       	//R       	//S      	//B      	//E     	//T      	//N     	//Pt100     	//cu50,   	//B<600
float code TC_Atab[11]={-7.5997e-7,	9.6322e-8,	4.8472e-4,	7.3225e-4,	2.4515e-3,	1.3651e-7,	9.9154e-5,	2.8055e-6,	-1.2878e-11,	-1.0896e-9,	205.65};
float code TC_Btab[11]={1.0905e-4,	8.7504e-6,	-2.8158e-2,	-3.6447e-2,	-0.11385,	-3.3295e-5,	-4.9932e-3,	-4.1148e-4,	1.5932e-8,		3.2617e-7,	-1037.8};
float code TC_Ctab[11]={-3.9325e-3,	2.0766e-3,	0.65866,	0.73075,	2.2226,		3.3864e-3,	9.3174e-2,	2.4892e-2,	-6.1794e-6,		-6.751e-5,	1970.3};
float code TC_Dtab[11]={0.017394,	0.062995,	-8.4431,	-8.1816,	-23.776,	-0.17164,	-0.98715,	-0.76438,	2.1231e-3,		7.6826e-3,	-1796};
float code TC_Etab[11]={24.75,		17.726,		136.69,		140.41,		228.37,		16.637,		25.774,		37.309,		2.2614,			4.2719,		1047};
float code TC_Ftab[11]={-0.55944,	3.457,		11.693,		9.6808,		256.77,		0.6252,		1.3639,		1.2499,		-242.75,		-226.06,	60.546};
//由于B型热电偶函数特殊，非线性很大，拟合分为了两段，小于600摄氏度一段，大于600摄氏度一段
float TCRTD(float res,unsigned char type)
//热电偶与热电偶温度转换函数，输入：res（热电偶电压：单位mv或者热点阻电阻值：单位欧姆），type（输入0－9分别对应KJRSBETNPt100Cu50，10对应B型热电偶小于600摄氏度的方程），输出：当前温度；
//{
//        return (TC_Atab[type]*res*res*res*res*res+TC_Btab[type]*res*res*res*res+TC_Ctab[type]*res*res*res+TC_Dtab[type]*res*res+TC_Etab[type]*res+TC_Ftab[type]);
//}
*/

extern const TCCOEF5_TYPEDEF TCB5_table[];

extern const TCCOEF5_TYPEDEF TCE5_table[];
//type j not accurate
extern const TCCOEF5_TYPEDEF TCJ5_table[];

extern const TCCOEF5_TYPEDEF TCK5_table[];

extern const TCCOEF5_TYPEDEF TCN5_table[];

extern const TCCOEF5_TYPEDEF TCR5_table[];

extern const TCCOEF5_TYPEDEF TCS5_table[];

extern const TCCOEF5_TYPEDEF TCT5_table[];

extern const TCCOEF5_TYPEDEF PT100_table[];

extern const TCCOEF5_TYPEDEF CU50_table[];


//thermocouple B/E/J/K/N/R/S/T: calculate temperature from mv
//double TC_mv2c(const TCCOEF_TYPEDEF *tc_curve, unsigned char order, double mv);
double TC_mv2c(const double *coef, unsigned char order, double mv);

//application macors
//default to 9th order calculation
#define TCBmv2c(mv)		TCB9_mv2c(mv)
#define TCEmv2c(mv)		TCE9_mv2c(mv)
#define TCJmv2c(mv)		TCJ9_mv2c(mv)
#define TCKmv2c(mv)		TCK9_mv2c(mv)
#define TCNmv2c(mv)		TCN9_mv2c(mv)
#define TCRmv2c(mv)		TCR9_mv2c(mv)
#define TCSmv2c(mv)		TCS9_mv2c(mv)
#define TCTmv2c(mv)		TCT9_mv2c(mv)

//application macros - 9th order / maximum order
#define TCB9_mv2c(mv)	(((mv) < TCB_table[TC_CURVE1].mV_HIGH)?TC_mv2c(TCB_table[TC_CURVE1].coef, 9, mv):TC_mv2c(TCB_table[TC_CURVE2].coef, 9, mv))
#define TCE9_mv2c(mv)	(((mv) < TCE_table[TC_CURVE1].mV_HIGH)?TC_mv2c(TCE_table[TC_CURVE1].coef, 9, mv):TC_mv2c(TCE_table[TC_CURVE2].coef, 9, mv))
#define TCJ9_mv2c(mv)	(((mv) < TCJ_table[TC_CURVE1].mV_HIGH)?TC_mv2c(TCJ_table[TC_CURVE1].coef, 9, mv):(((mv) < TCJ_table[TC_CURVE2].mV_HIGH)?TC_mv2c(TCJ_table[TC_CURVE2].coef, 9, mv):TC_mv2c(TCJ_table[TC_CURVE3].coef, 9, mv)))
#define TCK9_mv2c(mv)	(((mv) < TCK_table[TC_CURVE1].mV_HIGH)?TC_mv2c(TCK_table[TC_CURVE1].coef, 9, mv):(((mv) < TCK_table[TC_CURVE2].mV_HIGH)?TC_mv2c(TCK_table[TC_CURVE2].coef, 9, mv):TC_mv2c(TCK_table[TC_CURVE3].coef, 9, mv)))
#define TCN9_mv2c(mv)	(((mv) < TCN_table[TC_CURVE1].mV_HIGH)?TC_mv2c(TCN_table[TC_CURVE1].coef, 9, mv):(((mv) < TCN_table[TC_CURVE2].mV_HIGH)?TC_mv2c(TCN_table[TC_CURVE2].coef, 9, mv):TC_mv2c(TCN_table[TC_CURVE3].coef, 9, mv)))
#define TCR9_mv2c(mv)	(((mv) < TCR_table[TC_CURVE1].mV_HIGH)?TC_mv2c(TCR_table[TC_CURVE1].coef, 9, mv):(((mv) < TCR_table[TC_CURVE2].mV_HIGH)?TC_mv2c(TCR_table[TC_CURVE2].coef, 9, mv):(((mv) < TCR_table[TC_CURVE3].mV_HIGH)?TC_mv2c(TCR_table[TC_CURVE3].coef, 9, mv):TC_mv2c(TCR_table[TC_CURVE4].coef, 9, mv))))
#define TCS9_mv2c(mv)	(((mv) < TCS_table[TC_CURVE1].mV_HIGH)?TC_mv2c(TCS_table[TC_CURVE1].coef, 9, mv):(((mv) < TCS_table[TC_CURVE2].mV_HIGH)?TC_mv2c(TCS_table[TC_CURVE2].coef, 9, mv):(((mv) < TCS_table[TC_CURVE3].mV_HIGH)?TC_mv2c(TCS_table[TC_CURVE3].coef, 9, mv):TC_mv2c(TCS_table[TC_CURVE4].coef, 9, mv))))
#define TCT9_mv2c(mv)	(((mv) < TCT_table[TC_CURVE1].mV_HIGH)?TC_mv2c(TCT_table[TC_CURVE1].coef, 9, mv):TC_mv2c(TCT_table[TC_CURVE2].coef, 9, mv))

//5th order approximation
#define TCB5_mv2c(mv)	TC_mv2c(TCB5_table[TC_CURVE1].coef, 5, mv)
#define TCE5_mv2c(mv)	TC_mv2c(TCE5_table[TC_CURVE1].coef, 5, mv)
#define TCJ5_mv2c(mv)	TC_mv2c(TCJ5_table[TC_CURVE1].coef, 5, mv)
#define TCK5_mv2c(mv)	TC_mv2c(TCK5_table[TC_CURVE1].coef, 5, mv)
#define TCN5_mv2c(mv)	TC_mv2c(TCN5_table[TC_CURVE1].coef, 5, mv)
#define TCR5_mv2c(mv)	TC_mv2c(TCR5_table[TC_CURVE1].coef, 5, mv)
#define TCS5_mv2c(mv)	TC_mv2c(TCS5_table[TC_CURVE1].coef, 5, mv)
#define TCT5_mv2c(mv)	TC_mv2c(TCT5_table[TC_CURVE1].coef, 5, mv)
#define TCPT100_mv2ohm(mv)	TC_mv2c(TCPT100_table[TC_CURVE1].coef, 5, mv)
#define TCCU50_mv2ohm(mv)	TC_mv2c(TCCU50_table[TC_CURVE1].coef, 5, mv)


#endif // TC_H_INCLUDED
