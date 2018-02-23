#include "benchmark_ti.h"			//ti benchmark

unsigned long benchmark(int count, void (* f_ptr)(void)) {
	unsigned long clock_start, clock_end;

	//clock_start=clock();				//take the starting clock
	//do {f_ptr();} while (count--);		//runt he benchmark
	while (count--) f_ptr();
	//clock_end=clock();					//take the ending clock

	return clock_end-clock_start;
}


//TI MSP430 competitive benchmark - http://www.ti.com/lit/an/slaa205c/slaa205c.pdf
/*******************************************************************************
*
* Name : 8-bit Math
* Purpose : Benchmark 8-bit math functions.
*
*******************************************************************************/
typedef unsigned char UInt8;
UInt8 add8(UInt8 a, UInt8 b) {
    return (a + b);
}
UInt8 mul8(UInt8 a, UInt8 b) {
    return (a * b);
}
UInt8 div8(UInt8 a, UInt8 b) {
    return (a / b);
}
void main_8(void) {
    volatile UInt8 result[4];
    result[0] = 12;
    result[1] = 3;
    result[2] = add8(result[0], result[1]);
    result[1] = mul8(result[0], result[2]);
    result[3] = div8(result[1], result[2]);
    return;
}
//SLAA205C–June 2006–Revised January 2009 MSP430 Competitive Benchmarking 17
//Submit Documentation Feedback
//B.2.2 8-bit 2-dim matrix.c
//Benchmarking Application Source Code www.ti.com
/*******************************************************************************
*
* Name : 8-bit 2-dim Matrix
* Purpose : Benchmark copying 8-bit values.
*
*******************************************************************************/
//typedef unsigned char UInt8;
const UInt8 m1[16][4] = {
    {0x12, 0x56, 0x90, 0x34},
    {0x78, 0x12, 0x56, 0x90},
    {0x34, 0x78, 0x12, 0x56},
    {0x90, 0x34, 0x78, 0x12},
    {0x12, 0x56, 0x90, 0x34},
    {0x78, 0x12, 0x56, 0x90},
    {0x34, 0x78, 0x12, 0x56},
    {0x90, 0x34, 0x78, 0x12},
    {0x12, 0x56, 0x90, 0x34},
    {0x78, 0x12, 0x56, 0x90},
    {0x34, 0x78, 0x12, 0x56},
    {0x90, 0x34, 0x78, 0x12},
    {0x12, 0x56, 0x90, 0x34},
    {0x78, 0x12, 0x56, 0x90},
    {0x34, 0x78, 0x12, 0x56},
    {0x90, 0x34, 0x78, 0x12}
};
void main_8m (void) {
    int i, j;
    volatile UInt8 m2[16][4], m3[16][4];
    for(i = 0; i < 16; i++) {
        for(j=0; j < 4; j++) {
            m2[i][j] = m1[i][j];
            m3[i][j] = m2[i][j];
        }
    }
    return;
}
//18 MSP430 Competitive Benchmarking SLAA205C–June 2006–Revised January 2009
//Submit Documentation Feedback
//B.2.3 8-bit switch case.c
//www.ti.com Benchmarking Application Source Code
/*******************************************************************************
*
* Name : 8-bit Switch Case
* Purpose : Benchmark accessing switch statement using 8-bit value.
*
*******************************************************************************/
//typedef unsigned char UInt8;
UInt8 switch_case_8(UInt8 a) {
    UInt8 output;
    switch (a) {
    case 0x01:
        output = 0x01;
        break;
    case 0x02:
        output = 0x02;
        break;
    case 0x03:
        output = 0x03;
        break;
    case 0x04:
        output = 0x04;
        break;
    case 0x05:
        output = 0x05;
        break;
    case 0x06:
        output = 0x06;
        break;
    case 0x07:
        output = 0x07;
        break;
    case 0x08:
        output = 0x08;
        break;
    case 0x09:
        output = 0x09;
        break;
    case 0x0a:
        output = 0x0a;
        break;
    case 0x0b:
        output = 0x0b;
        break;
    case 0x0c:
        output = 0x0c;
        break;
    case 0x0d:
        output = 0x0d;
        break;
    case 0x0e:
        output = 0x0e;
        break;
    case 0x0f:
        output = 0x0f;
//SLAA205C–June 2006–Revised January 2009 MSP430 Competitive Benchmarking 19
//Submit Documentation Feedback
//Benchmarking Application Source Code www.ti.com
        break;
    case 0x10:
        output = 0x10;
        break;
    } /* end switch*/
    return (output);
}
void main_8sw(void) {
    volatile UInt8 result;
    result = switch_case_8(0x10);
    return;
}
//20 MSP430 Competitive Benchmarking SLAA205C–June 2006–Revised January 2009
//Submit Documentation Feedback
//B.2.4 16-bit math.c
//www.ti.com Benchmarking Application Source Code
/*******************************************************************************
*
* Name : 16-bit Math
* Purpose : Benchmark 16-bit math functions.
*
*******************************************************************************/
typedef unsigned short UInt16;
UInt16 add16(UInt16 a, UInt16 b) {
    return (a + b);
}
UInt16 mul16(UInt16 a, UInt16 b) {
    return (a * b);
}
UInt16 div16(UInt16 a, UInt16 b) {
    return (a / b);
}
void main_16(void) {
    volatile UInt16 result[4];
    result[0] = 231;
    result[1] = 12;
    result[2] = add16(result[0], result[1]);
    result[1] = mul16(result[0], result[2]);
    result[3] = div16(result[1], result[2]);
    return;
}
//SLAA205C–June 2006–Revised January 2009 MSP430 Competitive Benchmarking 21
//Submit Documentation Feedback
//B.2.5 16-bit 2-dim matrix.c
//Benchmarking Application Source Code www.ti.com
/*******************************************************************************
*
* Name : 16-bit 2-dim Matrix
* Purpose : Benchmark copying 16-bit values.
*
*******************************************************************************/
//typedef unsigned short UInt16;
const UInt16 m1_16[16][4] = {
    {0x1234, 0x5678, 0x9012, 0x3456},
    {0x7890, 0x1234, 0x5678, 0x9012},
    {0x3456, 0x7890, 0x1234, 0x5678},
    {0x9012, 0x3456, 0x7890, 0x1234},
    {0x1234, 0x5678, 0x9012, 0x3456},
    {0x7890, 0x1234, 0x5678, 0x9012},
    {0x3456, 0x7890, 0x1234, 0x5678},
    {0x9012, 0x3456, 0x7890, 0x1234},
    {0x1234, 0x5678, 0x9012, 0x3456},
    {0x7890, 0x1234, 0x5678, 0x9012},
    {0x3456, 0x7890, 0x1234, 0x5678},
    {0x9012, 0x3456, 0x7890, 0x1234},
    {0x1234, 0x5678, 0x9012, 0x3456},
    {0x7890, 0x1234, 0x5678, 0x9012},
    {0x3456, 0x7890, 0x1234, 0x5678},
    {0x9012, 0x3456, 0x7890, 0x1234}
};
void main_16m(void) {
    int i, j;
    volatile UInt16 m2[16][4], m3[16][4];
    for(i = 0; i < 16; i++) {
        for(j = 0; j < 4; j++) {
            m2[i][j] = m1_16[i][j];
            m3[i][j] = m2[i][j];
        }
    }
    return;
}
//22 MSP430 Competitive Benchmarking SLAA205C–June 2006–Revised January 2009
//Submit Documentation Feedback
//B.2.6 16-bit switch case.c
//www.ti.com Benchmarking Application Source Code
/*******************************************************************************
*
* Name : 16-bit Switch Case
* Purpose : Benchmark accessing switch statement using 16-bit value.
*
*******************************************************************************/
//typedef unsigned short UInt16;
UInt16 switch_case_16(UInt16 a) {
    UInt16 output;
    switch (a) {
    case 0x0001:
        output = 0x0001;
        break;
    case 0x0002:
        output = 0x0002;
        break;
    case 0x0003:
        output = 0x0003;
        break;
    case 0x0004:
        output = 0x0004;
        break;
    case 0x0005:
        output = 0x0005;
        break;
    case 0x0006:
        output = 0x0006;
        break;
    case 0x0007:
        output = 0x0007;
        break;
    case 0x0008:
        output = 0x0008;
        break;
    case 0x0009:
        output = 0x0009;
        break;
    case 0x000a:
        output = 0x000a;
        break;
    case 0x000b:
        output = 0x000b;
        break;
    case 0x000c:
        output = 0x000c;
        break;
    case 0x000d:
        output = 0x000d;
        break;
    case 0x000e:
        output = 0x000e;
        break;
    case 0x000f:
        output = 0x000f;
//SLAA205C–June 2006–Revised January 2009 MSP430 Competitive Benchmarking 23
//Submit Documentation Feedback
//Benchmarking Application Source Code www.ti.com
        break;
    case 0x0010:
        output = 0x0010;
        break;
    } /* end switch*/
    return (output);
}
void main_16sw(void) {
    volatile UInt16 result;
    result = switch_case_16(0x0010);
    return;
}
//24 MSP430 Competitive Benchmarking SLAA205C–June 2006–Revised January 2009
//Submit Documentation Feedback
//B.2.7 32-bit math.c
//www.ti.com Benchmarking Application Source Code
/*******************************************************************************
*
* Name : 32-bit Math
* Purpose : Benchmark 32-bit math functions.
*
*******************************************************************************/
#include <math.h>
typedef unsigned long UInt32;
UInt32 add32(UInt32 a, UInt32 b) {
    return (a + b);
}
UInt32 mul32(UInt32 a, UInt32 b) {
    return (a * b);
}
UInt32 div32(UInt32 a, UInt32 b) {
    return (a / b);
}
void main_32(void) {
    volatile UInt32 result[4];
    result[0] = 43125;
    result[1] = 14567;
    result[2] = add32(result[0], result[1]);
    result[1] = mul32(result[0], result[2]);
    result[3] = div32(result[1], result[2]);
    return;
}
//SLAA205C–June 2006–Revised January 2009 MSP430 Competitive Benchmarking 25
//Submit Documentation Feedback
//B.2.8 floating-point math.c
//Benchmarking Application Source Code www.ti.com
/*******************************************************************************
*
* Name : Floating-point Math
* Purpose : Benchmark floating-point math functions.
*
*******************************************************************************/
float addf(float a, float b) {
    return (a + b);
}
float mulf(float a, float b) {
    return (a * b);
}
float divf(float a, float b) {
    return (a / b);
}
void main_f(void) {
    volatile float result[4];
    result[0] = 54.567;
    result[1] = 14346.67;
    result[2] = addf(result[0], result[1]);
    result[1] = mulf(result[0], result[2]);
    result[3] = divf(result[1], result[2]);
    return;
}
//26 MSP430 Competitive Benchmarking SLAA205C–June 2006–Revised January 2009
//Submit Documentation Feedback
//B.2.9 matrix multiplication.c
//www.ti.com Benchmarking Application Source Code
/*******************************************************************************
*
* Name : Matrix Multiplication
* Purpose : Benchmark multiplying a 3x4 matrix by a 4x5 matrix.
* Matrix contains 16-bit values.
*
*******************************************************************************/
//typedef unsigned short UInt16;
const UInt16 m1_mmlt[3][4] = {
    {0x01, 0x02, 0x03, 0x04},
    {0x05, 0x06, 0x07, 0x08},
    {0x09, 0x0A, 0x0B, 0x0C}
};
const UInt16 m2_mmlt[4][5] = {
    {0x01, 0x02, 0x03, 0x04, 0x05},
    {0x06, 0x07, 0x08, 0x09, 0x0A},
    {0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
    {0x10, 0x11, 0x12, 0x13, 0x14}
};
void main_mmlt(void) {
    int m, n, p;
    volatile UInt16 m3[3][5];
    for(m = 0; m < 3; m++) {
        for(p = 0; p < 5; p++) {
            m3[m][p] = 0;
            for(n = 0; n < 4; n++) {
                m3[m][p] += m1_mmlt[m][n] * m2_mmlt[n][p];
            }
        }
    }
    return;
}
//SLAA205C–June 2006–Revised January 2009 MSP430 Competitive Benchmarking 27
//Submit Documentation Feedback
//B.2.10 fir filter.c
//Benchmarking Application Source Code www.ti.com
/*******************************************************************************
*
* Name : FIR Filter
* Purpose : Benchmark an FIR filter. The input values for the filter
* is an array of 51 16-bit values. The order of the filter is
* 17.
*
*******************************************************************************/
#ifdef MSP430
#include "msp430x14x.h"
#endif
#include <math.h>
#define FIR_LENGTH 17
const float COEFF[FIR_LENGTH] = {
    -0.000091552734, 0.000305175781, 0.004608154297, 0.003356933594, -0.025939941406,
    -0.044006347656, 0.063079833984, 0.290313720703, 0.416748046875, 0.290313720703,
    0.063079833984, -0.044006347656, -0.025939941406, 0.003356933594, 0.004608154297,
    0.000305175781, -0.000091552734
};
/* The following array simulates input A/D converted values */
const unsigned int INPUT[] = {
    0x0000, 0x0000, 0x0000, 0x0000,0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,0x0000, 0x0000, 0x0000, 0x0000,
    0x0400, 0x0800, 0x0C00, 0x1000, 0x1400, 0x1800, 0x1C00, 0x2000,
    0x2400, 0x2000, 0x1C00, 0x1800, 0x1400, 0x1000, 0x0C00, 0x0800,
    0x0400, 0x0400, 0x0800, 0x0C00, 0x1000, 0x1400, 0x1800, 0x1C00,
    0x2000, 0x2400, 0x2000, 0x1C00, 0x1800, 0x1400, 0x1000, 0x0C00,
    0x0800, 0x0400, 0x0400, 0x0800, 0x0C00, 0x1000, 0x1400, 0x1800,
    0x1C00, 0x2000, 0x2400, 0x2000, 0x1C00, 0x1800, 0x1400, 0x1000,
    0x0C00, 0x0800, 0x0400
};

void main_fir(void) {
    int i, y; /* Loop counters */
    volatile float OUTPUT[36],sum;
    for(y = 0; y < 36; y++) {
        sum=0;
        for(i = 0; i < FIR_LENGTH/2; i++) {
            sum = sum+COEFF[i] * ( INPUT[y + 16 - i] + INPUT[y + i] );
        }
        OUTPUT[y] = sum + (INPUT[y + FIR_LENGTH/2] * COEFF[FIR_LENGTH/2] );
    }
    return;
}

