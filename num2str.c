#include "num2str.h"				//we use fast routines to convert string

//global defines
#define X1(x)			((x))
#define X2(x)			((x) << 1)
#define X4(x)			((x) << 2)
#define X8(x)			((x) << 3)
#define X10(x)			(X8(x) + X2(x))
#define X16(x)			((x) << 4)
#define X128(x)			((x) << 7)
#define X256(x)			((x) << 8)
#define X512(x)			X2(X256(x))

//alternate X10 implementation
uint16_t X10_(uint16_t dat) {
	uint16_t tmp;
#if 0
	dat = dat + dat;	//dat = 2*dat
	tmp = dat + dat;	//tmp = 4*dat
	tmp = tmp + tmp;	//tmp = 8*dat
	tmp = tmp + dat;	//tmp = 10*dat
#else
	tmp = dat + dat;	//tmp = 2*dat
	tmp = tmp + tmp;	//tmp = 4*dat
	tmp = tmp + dat;	//tmp = 5*dat
	tmp = tmp + tmp;	//tmp = 10*dat
#endif	
	return tmp;
}

	
//convert a 10-bit digit to decimal string
//str = dat * 1000 / 2^10(=1024)
void num10_str(uint8_t *str, uint16_t dat) {
	//uint16_t tmp;
	dat = X10(dat); str[0]= (dat >> 10) + '0'; dat = dat & 0x03ff;
	dat = X10(dat); str[1]= (dat >> 10) + '0'; dat = dat & 0x03ff;
	dat = X10(dat); str[2]= (dat >> 10) + '0'; dat = dat & 0x03ff;
	dat = X10(dat); str[3]= (dat >> 10) + '0'; dat = dat & 0x03ff;
	dat = X10(dat); str[4]= (dat >> 10) + '0'; dat = dat & 0x03ff;
	dat = X10(dat); str[5]= (dat >> 10) + '0'; dat = dat & 0x03ff;
	dat = X10(dat); str[6]= (dat >> 10) + '0'; dat = dat & 0x03ff;
	dat = X10(dat); str[7]= (dat >> 10) + '0'; dat = dat & 0x03ff;
}

//convert a 12-bit digit to decimal string
//str = dat * 1000 / 2^12(=4096)
void num12_str(uint8_t *str, uint16_t dat) {
	//uint16_t tmp;
	dat = X10(dat); str[0]= (dat >> 12) + '0'; dat = dat & 0x0fff;
	dat = X10(dat); str[1]= (dat >> 12) + '0'; dat = dat & 0x0fff;
	dat = X10(dat); str[2]= (dat >> 12) + '0'; dat = dat & 0x0fff;
	dat = X10(dat); str[3]= (dat >> 12) + '0'; dat = dat & 0x0fff;
	dat = X10(dat); str[4]= (dat >> 12) + '0'; dat = dat & 0x0fff;
	dat = X10(dat); str[5]= (dat >> 12) + '0'; dat = dat & 0x0fff;
	dat = X10(dat); str[6]= (dat >> 12) + '0'; dat = dat & 0x0fff;
	dat = X10(dat); str[7]= (dat >> 12) + '0'; dat = dat & 0x0fff;
}

//convert a 14-bit digit to decimal string
//str = dat * 1000 / 2^14(=16384)
void num14_str(uint8_t *str, uint16_t dat) {
	//uint16_t tmp;
	dat = X10(dat); str[0]= (dat >> 14) + '0'; dat = dat & 0x3fff;
	dat = X10(dat); str[1]= (dat >> 14) + '0'; dat = dat & 0x3fff;
	dat = X10(dat); str[2]= (dat >> 14) + '0'; dat = dat & 0x3fff;
	dat = X10(dat); str[3]= (dat >> 14) + '0'; dat = dat & 0x3fff;
	dat = X10(dat); str[4]= (dat >> 14) + '0'; dat = dat & 0x3fff;
	dat = X10(dat); str[5]= (dat >> 14) + '0'; dat = dat & 0x3fff;
	dat = X10(dat); str[6]= (dat >> 14) + '0'; dat = dat & 0x3fff;
	dat = X10(dat); str[7]= (dat >> 14) + '0'; dat = dat & 0x3fff;
}

//convert a 16-bit digit to decimal string
//str = dat * 1000 / 2^16(=65536)
void num16_str(uint8_t *str, uint32_t dat) {
	//uint16_t tmp;
	dat = X10(dat); str[0]= (dat >> 16) + '0'; dat = dat & 0xffff;
	dat = X10(dat); str[1]= (dat >> 16) + '0'; dat = dat & 0xffff;
	dat = X10(dat); str[2]= (dat >> 16) + '0'; dat = dat & 0xffff;
	dat = X10(dat); str[3]= (dat >> 16) + '0'; dat = dat & 0xffff;
	dat = X10(dat); str[4]= (dat >> 16) + '0'; dat = dat & 0xffff;
	dat = X10(dat); str[5]= (dat >> 16) + '0'; dat = dat & 0xffff;
	dat = X10(dat); str[6]= (dat >> 16) + '0'; dat = dat & 0xffff;
	dat = X10(dat); str[7]= (dat >> 16) + '0'; dat = dat & 0xffff;
}

//convert a 18-bit digit to decimal string
//str = dat * 1000 / 2^18(=262144)
void num18_str(uint8_t *str, uint32_t dat) {
	//uint16_t tmp;
	dat = X10(dat); str[0]= (dat >> 18) + '0'; dat = dat & 0x03fffful;
	dat = X10(dat); str[1]= (dat >> 18) + '0'; dat = dat & 0x03fffful;
	dat = X10(dat); str[2]= (dat >> 18) + '0'; dat = dat & 0x03fffful;
	dat = X10(dat); str[3]= (dat >> 18) + '0'; dat = dat & 0x03fffful;
	dat = X10(dat); str[4]= (dat >> 18) + '0'; dat = dat & 0x03fffful;
	dat = X10(dat); str[5]= (dat >> 18) + '0'; dat = dat & 0x03fffful;
	dat = X10(dat); str[6]= (dat >> 18) + '0'; dat = dat & 0x03fffful;
	dat = X10(dat); str[7]= (dat >> 18) + '0'; dat = dat & 0x03fffful;
}

//convert a 20-bit digit to decimal string
//str = dat * 1000 / 2^20(=1,048,576)
void num20_str(uint8_t *str, uint32_t dat) {
	//uint16_t tmp;
	dat = X10(dat); str[0]= (dat >> 20) + '0'; dat = dat & 0x0ffffful;
	dat = X10(dat); str[1]= (dat >> 20) + '0'; dat = dat & 0x0ffffful;
	dat = X10(dat); str[2]= (dat >> 20) + '0'; dat = dat & 0x0ffffful;
	dat = X10(dat); str[3]= (dat >> 20) + '0'; dat = dat & 0x0ffffful;
	dat = X10(dat); str[4]= (dat >> 20) + '0'; dat = dat & 0x0ffffful;
	dat = X10(dat); str[5]= (dat >> 20) + '0'; dat = dat & 0x0ffffful;
	dat = X10(dat); str[6]= (dat >> 20) + '0'; dat = dat & 0x0ffffful;
	dat = X10(dat); str[7]= (dat >> 20) + '0'; dat = dat & 0x0ffffful;
}

//convert a 22-bit digit to decimal string
//str = dat * 1000 / 2^22(=4,194,304)
void num22_str(uint8_t *str, uint32_t dat) {
	//uint16_t tmp;
	dat = X10(dat); str[0]= (dat >> 22) + '0'; dat = dat & 0x3ffffful;
	dat = X10(dat); str[1]= (dat >> 22) + '0'; dat = dat & 0x3ffffful;
	dat = X10(dat); str[2]= (dat >> 22) + '0'; dat = dat & 0x3ffffful;
	dat = X10(dat); str[3]= (dat >> 22) + '0'; dat = dat & 0x3ffffful;
	dat = X10(dat); str[4]= (dat >> 22) + '0'; dat = dat & 0x3ffffful;
	dat = X10(dat); str[5]= (dat >> 22) + '0'; dat = dat & 0x3ffffful;
	dat = X10(dat); str[6]= (dat >> 22) + '0'; dat = dat & 0x3ffffful;
	dat = X10(dat); str[7]= (dat >> 22) + '0'; dat = dat & 0x3ffffful;
}

//convert a 24-bit digit to decimal string
//str = dat * 1000 / 2^24(=16,777,216)
void num24_str(uint8_t *str, uint32_t dat) {
	//uint16_t tmp;
	dat = X10(dat); str[0]= (dat >> 24) + '0'; dat = dat & 0xfffffful;
	dat = X10(dat); str[1]= (dat >> 24) + '0'; dat = dat & 0xfffffful;
	dat = X10(dat); str[2]= (dat >> 24) + '0'; dat = dat & 0xfffffful;
	dat = X10(dat); str[3]= (dat >> 24) + '0'; dat = dat & 0xfffffful;
	dat = X10(dat); str[4]= (dat >> 24) + '0'; dat = dat & 0xfffffful;
	dat = X10(dat); str[5]= (dat >> 24) + '0'; dat = dat & 0xfffffful;
	dat = X10(dat); str[6]= (dat >> 24) + '0'; dat = dat & 0xfffffful;
	dat = X10(dat); str[7]= (dat >> 24) + '0'; dat = dat & 0xfffffful;
}

