#ifndef QMATH_H_INCLUDED
#define QMATH_H_INCLUDED

//my own Qmath routines, for C30/XC16		//macros __C30__ or __XC16__
#include <libq.h>							//needs to link in libq for the executables
typedef _Q15 Q16_t;
typedef _Q16 Q32_t;

//macros to map my Qmath routines to C30/XC16 Qmath routines
//Q16_t format now
#define ADD_Q16(a, b)		_Q15add(a, b)	//returns a+b
#define SUB_Q16(a, b)		_Q15sub(a, b)	//returns a-b
#define MUL_Q16(a, b)		_Q15mul(a, b)	//returns a*b
#define DIV_Q16(a, b)		_Q15div(a, b)	//returns a/b
#define ABS_Q16(a)			_Q15abs(a)		//returns |a|
#define SIN_Q16(a)			_Q15sin(a)		//returns sin(a)
#define COS_Q16(a)			_Q15cos(a)		//returns cos(a)
#define TAN_Q16(a)			_Q15tan(a)		//returns tan(a)
#define ASIN_Q16(a)			_Q15asin(a)		//returns arc sin(a)
#define ACOS_Q16(a)			_Q15acos(a)		//returns arc cos(a)
#define ATAN_Q16(a)			_Q15atan(a)		//returns arc tang(a)
#define EXP_Q16(a)			_Q15exp(a)		//returns e^a
#define LOG_Q16(a)			_Q15log(a)		//returns log(a)
#define LOG10_Q16(a)		_Q15log10(a)	//returns log10(a)
#define NEG_Q16(a)			_Q15neg(a)		//negate (a)
#define SFT_Q16(a, sft)		_Q15shl(a, sft)	//shift left if sft is positive and shift right if sft is negative
#define SQRT_Q16(a)			_Q15sqrt(a)		//returns sqrt(a)
#define FtoQ16(f)			_Q15ftoi(f)		//converts float to Q16. a between -1 to 0.99996
#define Q16toF(q)			_itofQ15(q)		//convert Q16 to float

//Q32_t format now
#define ADD_Q32(a, b)		_Q16add(a, b)	//returns a+b
#define SUB_Q32(a, b)		_Q16sub(a, b)	//returns a-b
#define MUL_Q32(a, b)		_Q16mul(a, b)	//returns a*b
#define DIV_Q32(a, b)		_Q16div(a, b)	//returns a/b
#define ABS_Q32(a)			_Q16abs(a)		//returns |a|
#define SIN_Q32(a)			_Q16sin(a)		//returns sin(a)
#define COS_Q32(a)			_Q16cos(a)		//returns cos(a)
#define TAN_Q32(a)			_Q16tan(a)		//returns tan(a)
#define ASIN_Q32(a)			_Q16asin(a)		//returns arc sin(a)
#define ACOS_Q32(a)			_Q16acos(a)		//returns arc cos(a)
#define ATAN_Q32(a)			_Q16atan(a)		//returns arc tang(a)
#define EXP_Q32(a)			_Q16exp(a)		//returns e^a
#define LOG_Q32(a)			_Q16log(a)		//returns log(a)
#define LOG10_Q32(a)		_Q16log10(a)	//returns log10(a)
#define NEG_Q32(a)			_Q16neg(a)		//negate (a)
#define SFT_Q32(a, sft)		_Q16shl(a, sft)	//shift left if sft is positive and shift right if sft is negative
#define SQRT_Q32(a)			_Q16sqrt(a)
#define FtoQ32(f)			_Q16ftoi(f)		//converts float to Q32. a between -32768 to 32767
#define Q32toF(q)			_itofQ16(q)		//convert Q32 to float

#endif /* QMATH_H_INCLUDED */
