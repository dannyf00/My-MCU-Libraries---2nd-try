#include "tibenchmark.h"

//benchmark a function for a set number of times
void benchmark(void (*func)(void), uint32_t cnt) {
	while (cnt--) func();
}

/*******************************************************************************
*
* Name : 8-bit Math
* Purpose : Benchmark 8-bit math functions.
*
*******************************************************************************/
typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned long UInt32;

UInt8 u8_add(UInt8 a, UInt8 b) {
    return (a + b);
}
UInt8 u8_mul(UInt8 a, UInt8 b) {
    return (a * b);
}
UInt8 u8_div(UInt8 a, UInt8 b) {
    return (a / b);
}
void main_8bitmath(void) {
    volatile UInt8 result[4];
    result[0] = 12;
    result[1] = 3;
    result[2] = u8_add(result[0], result[1]);
    result[1] = u8_mul(result[0], result[2]);
    result[3] = u8_div(result[1], result[2]);
    return;
}

/*******************************************************************************
*
* Name : 8-bit 2-dim Matrix
* Purpose : Benchmark copying 8-bit values.
*
*******************************************************************************/
//typedef unsigned char UInt8;
const UInt8 tmp0_m1[16][4] = {
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
volatile UInt8 tmp0_m2[16][4], tmp0_m3[16][4];
void main_8bit2dmatrix(void) {
    int i, j;
    //volatile UInt8 m2[16][4], m3[16][4];
    for(i = 0; i < 16; i++)	{
        for(j=0; j < 4; j++) {
            tmp0_m2[i][j] = tmp0_m1[i][j];
            tmp0_m3[i][j] = tmp0_m2[i][j];
        }
    }
    return;
}

/*******************************************************************************
*
* Name : 8-bit Switch Case
* Purpose : Benchmark accessing switch statement using 8-bit value.
*
*******************************************************************************/
//typedef unsigned char UInt8;
UInt8 u8_switch_case(UInt8 a) {
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
        break;
    case 0x10:
        output = 0x10;
        break;
    } /* end switch*/
    return (output);
}

void main_8bitswitchcase(void) {
    volatile UInt8 result;
    result = u8_switch_case(0x10);
    return;
}

/*******************************************************************************
*
* Name : 16-bit Math
* Purpose : Benchmark 16-bit math functions.
*
*******************************************************************************/
//typedef unsigned short UInt16;
UInt16 u16_add(UInt16 a, UInt16 b) {
    return (a + b);
}
UInt16 u16_mul(UInt16 a, UInt16 b) {
    return (a * b);
}
UInt16 u16_div(UInt16 a, UInt16 b) {
    return (a / b);
}
void main_16bitmath(void) {
    volatile UInt16 result[4];
    result[0] = 231;
    result[1] = 12;
    result[2] = u16_add(result[0], result[1]);
    result[1] = u16_mul(result[0], result[2]);
    result[3] = u16_div(result[1], result[2]);
    return;
}

/*******************************************************************************
*
* Name : 16-bit 2-dim Matrix
* Purpose : Benchmark copying 16-bit values.
*
*******************************************************************************/
//typedef unsigned short UInt16;
const UInt16 tmp1_m1[16][4] = {
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
	volatile UInt16 tmp1_m2[16][4], tmp1_m3[16][4];
void main_16bit2dmatrix(void) {
    int i, j;
    //volatile UInt16 m2[16][4], m3[16][4];
    for(i = 0; i < 16; i++) {
        for(j = 0; j < 4; j++) {
            tmp1_m2[i][j] = tmp1_m1[i][j];
            tmp1_m3[i][j] = tmp1_m2[i][j];
        }
    }
    return;
}

/*******************************************************************************
*
* Name : 16-bit Switch Case
* Purpose : Benchmark accessing switch statement using 16-bit value.
*
*******************************************************************************/
//typedef unsigned short UInt16;
UInt16 u16_switch_case(UInt16 a) {
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
        //SLAA205C每June 2006每Revised January 2009 MSP430 Competitive Benchmarking 23
        //Submit Documentation Feedback
        //Benchmarking Application Source Code www.ti.com
        break;
    case 0x0010:
        output = 0x0010;
        break;
    } /* end switch*/
    return (output);
}
void main_16bitswitchcase(void) {
    volatile UInt16 result;
    result = u16_switch_case(0x0010);
    return;
}

/*******************************************************************************
*
* Name : 32-bit Math
* Purpose : Benchmark 32-bit math functions.
*
*******************************************************************************/
#include <math.h>
//typedef unsigned long UInt32;
UInt32 u32_add(UInt32 a, UInt32 b) {
    return (a + b);
}
UInt32 u32_mul(UInt32 a, UInt32 b) {
    return (a * b);
}
UInt32 u32_div(UInt32 a, UInt32 b) {
    return (a / b);
}
void main_32bitmath(void) {
    volatile UInt32 result[4];
    result[0] = 43125;
    result[1] = 14567;
    result[2] = u32_add(result[0], result[1]);
    result[1] = u32_mul(result[0], result[2]);
    result[3] = u32_div(result[1], result[2]);
    return;
}

/*******************************************************************************
*
* Name : Floating-point Math
* Purpose : Benchmark floating-point math functions.
*
*******************************************************************************/
float fp_add(float a, float b) {
    return (a + b);
}
float fp_mul(float a, float b) {
    return (a * b);
}
float fp_div(float a, float b) {
    return (a / b);
}
void main_fpmath(void) {
    volatile float result[4];
    result[0] = 54.567;
    result[1] = 14346.67;
    result[2] = fp_add(result[0], result[1]);
    result[1] = fp_mul(result[0], result[2]);
    result[3] = fp_div(result[1], result[2]);
    return;
}

/*******************************************************************************
*
* Name : Matrix Multiplication
* Purpose : Benchmark multiplying a 3x4 matrix by a 4x5 matrix.
* Matrix contains 16-bit values.
*
*******************************************************************************/
//typedef unsigned short UInt16;
const UInt16 tmp2_m1[3][4] = {
    {0x01, 0x02, 0x03, 0x04},
    {0x05, 0x06, 0x07, 0x08},
    {0x09, 0x0A, 0x0B, 0x0C}
};
const UInt16 tmp2_m2[4][5] = {
    {0x01, 0x02, 0x03, 0x04, 0x05},
    {0x06, 0x07, 0x08, 0x09, 0x0A},
    {0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
    {0x10, 0x11, 0x12, 0x13, 0x14}
};
volatile UInt16 tmp2_m3[3][5];
void main_matrixmul(void) {
    int m, n, p;
    //volatile UInt16 tmp2_m3[3][5];
    for(m = 0; m < 3; m++) {
        for(p = 0; p < 5; p++) {
            tmp2_m3[m][p] = 0;
            for(n = 0; n < 4; n++) {
                tmp2_m3[m][p] += tmp2_m1[m][n] * tmp2_m2[n][p];
            }
        }
    }
    return;
}

/*******************************************************************************
*
* Name : FIR Filter
* Purpose : Benchmark an FIR filter. The input values for the filter
* is an array of 51 16-bit values. The order of the filter is
* 17.
*
*******************************************************************************/
#if defined(BENCHMARK_FIR)
//#ifdef MSP430
//#include "msp430x14x.h"
//#endif
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
volatile float OUTPUT[36],sum;
void main_fir(void) {
    int i, y; /* Loop counters */
    //volatile float OUTPUT[36],sum;
    for(y = 0; y < 36; y++) {
        sum=0;
        for(i = 0; i < FIR_LENGTH/2; i++) {
            sum = sum+COEFF[i] * ( INPUT[y + 16 - i] + INPUT[y + i] );
        }
        OUTPUT[y] = sum + (INPUT[y + FIR_LENGTH/2] * COEFF[FIR_LENGTH/2] );
    }
    return;
}
#endif

/*******************************************************************************
*
* Name : Dhrystone
* Purpose : Benchmark the Dhrystone code. This benchmark is used to gauge
* the performance of the microcontroller in handling pointers,
* structures and strings.
*
*******************************************************************************/
#if defined(BENCHMARK_DHRY)
#include <stdio.h>
#include <string.h>
#define LOOPS DHRY_LOOPS /* Use this for slow or 16 bit machines */
#define structassign(d, s) d = s
typedef enum {Ident1, Ident2, Ident3, Ident4, Ident5} Enumeration;
typedef int OneToThirty;
typedef int OneToFifty;
typedef unsigned char CapitalLetter;
typedef unsigned char String30[31];
typedef int Array1Dim[51];
typedef int Array2Dim[10][10];
struct Record {
    struct Record *PtrComp;
    Enumeration Discr;
    Enumeration EnumComp;
    OneToFifty IntComp;
    String30 StringComp;
};
typedef struct Record RecordType;
typedef RecordType * RecordPtr;
typedef int boolean;
#ifndef NULL
  #define NULL 0
#endif
#define TRUE 1
#define FALSE 0
#define REG register
int IntGlob;
boolean BoolGlob;
unsigned char Char1Glob;
unsigned char Char2Glob;
Array1Dim Array1Glob;
Array2Dim Array2Glob;
RecordPtr PtrGlb;
RecordPtr PtrGlbNext;
RecordType rec1, rec2;
Enumeration Func1(CapitalLetter CharPar1, CapitalLetter CharPar2) {
    REG CapitalLetter CharLoc1;
    REG CapitalLetter CharLoc2;
    CharLoc1 = CharPar1;
    CharLoc2 = CharLoc1;
    if (CharLoc2 != CharPar2)
        return (Ident1);
    else
        return (Ident2);
    //SLAA205C每June 2006每Revised January 2009 MSP430 Competitive Benchmarking 29
    //Submit Documentation Feedback
    //Benchmarking Application Source Code www.ti.com
}
boolean Func2(String30 StrParI1, String30 StrParI2) {
    REG OneToThirty IntLoc;
    REG CapitalLetter CharLoc;
    IntLoc = 1;
    while (IntLoc <= 1)
        if (Func1(StrParI1[IntLoc], StrParI2[IntLoc+1]) == Ident1) {
            CharLoc = 'A';
            ++IntLoc;
        }
    if (CharLoc >= 'W' && CharLoc <= 'Z')
        IntLoc = 7;
    if (CharLoc == 'X')
        return(TRUE);
    else {
        if (strcmp(StrParI1, StrParI2) > 0) {
            IntLoc += 7;
            return (TRUE);
        } else
            return (FALSE);
    }
}
boolean Func3(Enumeration EnumParIn) {
    REG Enumeration EnumLoc;
    EnumLoc = EnumParIn;
    if (EnumLoc == Ident3) return (TRUE);
    return (FALSE);
}
void Proc7(OneToFifty IntParI1, OneToFifty IntParI2, OneToFifty *IntParOut) {
    REG OneToFifty IntLoc;
    IntLoc = IntParI1 + 2;
    *IntParOut = IntParI2 + IntLoc;
}
void Proc4(void) {
    REG boolean BoolLoc;
    BoolLoc = Char1Glob == 'A';
    BoolLoc |= BoolGlob;
    Char2Glob = 'B';
}
void Proc5(void) {
    Char1Glob = 'A';
    BoolGlob = FALSE;
}
void Proc6(Enumeration EnumParIn, Enumeration *EnumParOut) {
//30 MSP430 Competitive Benchmarking SLAA205C每June 2006每Revised January 2009
//Submit Documentation Feedback
//www.ti.com Benchmarking Application Source Code {
    *EnumParOut = EnumParIn;
    if (! Func3(EnumParIn) )
        *EnumParOut = Ident4;
    switch (EnumParIn) {
    case Ident1:
        *EnumParOut = Ident1;
        break;
    case Ident2:
        if (IntGlob > 100) *EnumParOut = Ident1;
        else *EnumParOut = Ident4;
        break;
    case Ident3:
        *EnumParOut = Ident2;
        break;
    case Ident4:
        break;
    case Ident5:
        *EnumParOut = Ident3;
    }
}
void Proc3(RecordPtr *PtrParOut) {
    if (PtrGlb != NULL)
        *PtrParOut = PtrGlb->PtrComp;
    else
        IntGlob = 100;
    Proc7(10, IntGlob, &PtrGlb->IntComp);
}
void Proc1(RecordPtr PtrParIn) {
#define NextRecord (*(PtrParIn->PtrComp))
    structassign(NextRecord, *PtrGlb);
    PtrParIn->IntComp = 5;
    NextRecord.IntComp = PtrParIn->IntComp;
    NextRecord.PtrComp = PtrParIn->PtrComp;
    Proc3(&NextRecord.PtrComp);
    if (NextRecord.Discr == Ident1) {
        NextRecord.IntComp = 6;
        Proc6(PtrParIn->EnumComp, &NextRecord.EnumComp);
        NextRecord.PtrComp = PtrGlb->PtrComp;
        Proc7(NextRecord.IntComp, 10, &NextRecord.IntComp);
    } else
        structassign(*PtrParIn, NextRecord);
#undef NextRecord
}
void Proc2(OneToFifty *IntParIO) {
    REG OneToFifty IntLoc;
    REG Enumeration EnumLoc;
    IntLoc = *IntParIO + 10;
    for(;;) {
        if (Char1Glob == 'A') {
            --IntLoc;
            *IntParIO = IntLoc - IntGlob;
            EnumLoc = Ident1;
        }
        if (EnumLoc == Ident1)
            //SLAA205C每June 2006每Revised January 2009 MSP430 Competitive Benchmarking 31
            //Submit Documentation Feedback
            //Benchmarking Application Source Code www.ti.com
            break;
    }
}
void Proc8 (Array1Dim Array1Par, Array2Dim Array2Par, OneToFifty IntParI1, OneToFifty
            IntParI2) {
    REG OneToFifty IntLoc;
    REG OneToFifty IntIndex;
    IntLoc = IntParI1 + 5;
    Array1Par[IntLoc] = IntParI2;
    Array1Par[IntLoc+1] = Array1Par[IntLoc];
    Array1Par[IntLoc+30] = IntLoc;
    for (IntIndex = IntLoc; IntIndex <= (IntLoc+1); ++IntIndex)
        Array2Par[IntLoc][IntIndex] = IntLoc;
    ++Array2Par[IntLoc][IntLoc-1];
    Array2Par[IntLoc+20][IntLoc] = Array1Par[IntLoc];
    IntGlob = 5;
}
void Proc0 (void) {
    OneToFifty IntLoc1;
    REG OneToFifty IntLoc2;
    OneToFifty IntLoc3;
    REG unsigned char CharLoc;
    REG unsigned char CharIndex;
    Enumeration EnumLoc;
    String30 String1Loc;
    String30 String2Loc;
    //extern unsigned char *malloc();			//no support for malloc()
    long time(long *);
    long starttime;
    long benchtime;
    long nulltime;
    register unsigned int i;
    for (i = 0; i < LOOPS; ++i);
    PtrGlbNext = &rec1; /* (RecordPtr) malloc(sizeof(RecordType)); */
    PtrGlb = &rec2; /* (RecordPtr) malloc(sizeof(RecordType)); */
    PtrGlb->PtrComp = PtrGlbNext;
    PtrGlb->Discr = Ident1;
    PtrGlb->EnumComp = Ident3;
    PtrGlb->IntComp = 40;
    strcpy(PtrGlb->StringComp, "DHRYSTONE PROGRAM, SOME STRING");
    strcpy(String1Loc, "DHRYSTONE PROGRAM, 1'ST STRING"); /*GOOF*/
    Array2Glob[8][7] = 10; /* Was missing in published program */
    for (i = 0; i < LOOPS; ++i) {
        Proc5();
        Proc4();
        IntLoc1 = 2;
        IntLoc2 = 3;
        strcpy(String2Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
        EnumLoc = Ident2;
        BoolGlob = ! Func2(String1Loc, String2Loc);
        while (IntLoc1 < IntLoc2) {
            //32 MSP430 Competitive Benchmarking SLAA205C每June 2006每Revised January 2009
            //Submit Documentation Feedback
            //www.ti.com Benchmarking Application Source Code
            IntLoc3 = 5 * IntLoc1 - IntLoc2;
            Proc7(IntLoc1, IntLoc2, &IntLoc3);
            ++IntLoc1;
        }
        Proc8(Array1Glob, Array2Glob, IntLoc1, IntLoc3);
        Proc1(PtrGlb);
        for (CharIndex = 'A'; CharIndex <= Char2Glob; ++CharIndex)
            if (EnumLoc == Func1(CharIndex, 'C'))
                Proc6(Ident1, &EnumLoc);
        IntLoc3 = IntLoc2 * IntLoc1;
        IntLoc2 = IntLoc3 / IntLoc1;
        IntLoc2 = 7 * (IntLoc3 - IntLoc2) - IntLoc1;
        Proc2(&IntLoc1);
    }
}
void main_dhry(void) {
    Proc0();
}
#endif

/*******************************************************************************
*
* Name : Whetstone
* Purpose : Benchmark the Whetstone code. The code focuses on scientific
* functions such as sine, cosine, exponents and logarithm on
* fixed and floating point numbers.
*
*******************************************************************************/
#if defined(BENCHMARK_WHET)
#include <math.h>
#include <stdio.h>
void PA(float E[5]);
void P0(void);
void P3(float *X, float *Y, float *Z);
float T,T1,T2,E1[5];
int J,K,L;
float X1,X2,X3,X4;
long ptime,time0;
void main_whet (void) {
    int LOOP,I,II,JJ,N1,N2,N3,N4,N5,N6,N7,N8,N9,N10,N11;
    float X,Y,Z;
    T = .499975;
    T1 = 0.50025;
    T2 = 2.0;
    LOOP = 1;
    II = 1;
    for (JJ=1; JJ<=II; JJ++) {
        N1 = 0;
        N2 = 2 * LOOP;
        N3 = 2 * LOOP;
        N4 = 2 * LOOP;
        N5 = 0;
        N6 = 2 * LOOP;
        N7 = 2 * LOOP;
        N8 = 2 * LOOP;
        N9 = 2 * LOOP;
        N10 = 0;
        N11 = 2 * LOOP;
        /* Module 1: Simple identifiers */
        X1 = 1.0;
        X2 = -1.0;
        X3 = -1.0;
        X4 = -1.0;
        if (N1!=0) {
            for(I=1; I<=N1; I++) {
                X1 = (X1 + X2 + X3 - X4)*T;
                X2 = (X1 + X2 - X3 + X4)*T;
                X3 = (X1 - X2 + X3 + X4)*T;
                X4 = (-X1 + X2 + X3 + X4)*T;
            };
        };
        //34 MSP430 Competitive Benchmarking SLAA205C每June 2006每Revised January 2009
        //Submit Documentation Feedback
        //www.ti.com Benchmarking Application Source Code
        /* Module 2: Array elements */
        E1[1] = 1.0;
        E1[2] = -1.0;
        E1[3] = -1.0;
        E1[4] = -1.0;
        if (N2!=0) {
            for (I=1; I<=N2; I++) {
                E1[1] = (E1[1] + E1[2] + E1[3] - E1[4])*T;
                E1[2] = (E1[1] + E1[2] - E1[3] + E1[4])*T;
                E1[3] = (E1[1] - E1[2] + E1[3] + E1[4])*T;
                E1[4] = (-E1[1] + E1[2] + E1[3] + E1[4])*T;
            }
        }
        /* Module 3: Array as parameter */
        if (N3!=0) {
            for (I=1; I<=N3; I++) {
                PA(E1);
            }
        }
        /* Module 4: Conditional jumps */
        J = 1;
        if (N4!=0) {
            for (I=1; I<=N4; I++) {
#if 0
                if (J==1) goto L51;
                J = 3;
                goto L52;
L51:
                J = 2;
L52:
                if (J > 2) goto L53;
                J = 1;
                goto L54;
L53:
                J = 0;
L54:
                if (J < 1) goto L55;
                J = 0;
                goto L60;
L55:
                J = 1;
L60:
#else
                if (J == 1)
                    J = 2;
                else
                    J = 3;

                if (J > 2)
                    J = 0;
                else
                    J = 1;

                if (J < 1)
                    J = 1;
                else
                    J = 0;
#endif
            }
        }
        /* Module 5: Integer arithmetic */
        J = 1;
        K = 2;
        L = 3;
        if (N6!=0) {
            for (I=1; I<=N6; I++) {
                J = J * (K-J) * (L-K);
                K = L * K - (L-J) * K;
                L = (L - K) * (K + J);
                E1[L-1] = J + K + L;
                //SLAA205C每June 2006每Revised January 2009 MSP430 Competitive Benchmarking 35
                //Submit Documentation Feedback
                //Benchmarking Application Source Code www.ti.com
                E1[K-1] = J * K * L;
            }
        }
        /* Module 6: Trigonometric functions */
        X = 0.5;
        Y = 0.5;
        if (N7!=0) {
            for (I=1; I<=N7; I++) {
                X=T*atan(T2*sin(X)*cos(X)/(cos(X+Y)+cos(X-Y)-1.0));
                Y=T*atan(T2*sin(Y)*cos(Y)/(cos(X+Y)+cos(X-Y)-1.0));
            }
        }
        /* Module 7: Procedure calls */
        X = 1.0;
        Y = 1.0;
        Z = 1.0;
        if (N8!=0) {
            for (I=1; I<=N8; I++) {
                P3(&X,&Y,&Z);
            }
        }
        /* Module 8: Array references */
        J = 1;
        K = 2;
        L = 3;
        E1[1] = 1.0;
        E1[2] = 2.0;
        E1[3] = 3.0;
        if (N9!=0) {
            for (I=1; I<=N9; I++) {
                P0();
            }
        }
        /* Module 9: Integer arithmetic */
        J = 2;
        K = 3;
        if (N10!=0) {
            for (I=1; I<=N10; I++) {
                J = J + K;
                K = J + K;
                J = K - J;
                K = K - J - J;
            }
        }
        /* Module 10: Standard functions */
        X = 0.75;
        if (N11!=0)
            //36 MSP430 Competitive Benchmarking SLAA205C每June 2006每Revised January 2009
            //Submit Documentation Feedback
            //www.ti.com Benchmarking Application Source Code
		{
            for (I=1; I<=N11; I++) {
                X = sqrt(exp(log(X)/T1));
            }
        }
    }
}
void PA(E) float E[5];
{
    int J1;
    J1 = 0;
L10:
    E[1] = (E[1] + E[2] + E[3] - E[4]) * T;
    E[2] = (E[1] + E[2] - E[3] + E[4]) * T;
    E[3] = (E[1] - E[2] + E[3] + E[4]) * T;
    E[4] = (-E[1] + E[2] + E[3] + E[4]) / T2;
    J1 = J1 + 1;
    if ((J1 - 6) < 0) goto L10;
    return;
}
void P0(void) {
    E1[J] = E1[K];
    E1[K] = E1[L];
    E1[L] = E1[J];
    return;
}
void P3(X,Y,Z) float *X,*Y,*Z;
{
    float Y1;
    X1 = *X;
    Y1 = *Y;
    X1 = T * (X1 + Y1);
    Y1 = T * (X1 + Y1);
    *Z = (X1 + Y1) / T2;
    return;
}
#endif
