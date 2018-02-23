#include "ledbar.h"						//convert data into led bars (trailing 1s)

//hardware configuration
//end hardware configuration

//global defines
#define BAR(dig)			((1ul<<(dig))-1)	//return full digits for "dig", bar style
#define DOT(dig)			((dig)?(1ul<<((dig)-1)):0)	//return full digits for "dig", dot style

//global variables

//bar style routines
//log-linear for 8-bit data into 8-bit led
//log-linear
uint8_t dat8_bar8(uint8_t w) {
	if (w<1) return BAR(0);
	if (w<3) return BAR(1);
	if (w<6) return BAR(2);
	if (w<12) return BAR(3);
	if (w<23) return BAR(4);
	if (w<46) return BAR(5);
	if (w<91) return BAR(6);
	if (w<182) return BAR(7);
	return 0xff;
}	

//convert 8-digit dat to 16-led digits
//log-linear
uint16_t dat8_bar16(uint8_t w) {
	if (w<1) return BAR(0);
	if (w<2) return BAR(1);
	if (w<3) return BAR(2);
	if (w<4) return BAR(3);
	if (w<5) return BAR(4);
	if (w<7) return BAR(5);
	if (w<10) return BAR(6);
	if (w<14) return BAR(7);
	if (w<20) return BAR(8);
	if (w<27) return BAR(9);
	if (w<39) return BAR(10);
	if (w<54) return BAR(11);
	if (w<77) return BAR(12);
	if (w<108) return BAR(13);
	if (w<153) return BAR(14);
	if (w<216) return BAR(15);
	return 0xffff;							//16;
}

//log-linear for 10-bit data into 8-bit led
//log-linear
uint8_t dat10_bar8(uint16_t w) {
	if (w<1) return BAR(0);
	if (w<4) return BAR(1);
	if (w<9) return BAR(2);
	if (w<21) return BAR(3);
	if (w<50) return BAR(4);
	if (w<118) return BAR(5);
	if (w<280) return BAR(6);
	if (w<664) return BAR(7);
	return 0xff;
}	

//convert 10-digit dat to 12-led digits
//log-linear
uint16_t dat10_bar12(uint16_t w) {
	if (w<1) return BAR(0);
	if (w<2) return BAR(1);
	if (w<3) return BAR(2);
	if (w<6) return BAR(3);
	if (w<10) return BAR(4);
	if (w<18) return BAR(5);
	if (w<32) return BAR(6);
	if (w<57) return BAR(7);
	if (w<102) return BAR(8);
	if (w<181) return BAR(9);
	if (w<323) return BAR(10);
	if (w<575) return BAR(11);
	return 0x0fff;							//16;
}

//convert 10-digit dat to 16-led digits
//log-linear
uint16_t dat10_bar16(uint16_t w) {
	if (w<1) return BAR(0);
	if (w<2) return BAR(1);
	if (w<3) return BAR(2);
	if (w<5) return BAR(3);
	if (w<8) return BAR(4);
	if (w<11) return BAR(5);
	if (w<17) return BAR(6);
	if (w<26) return BAR(7);
	if (w<40) return BAR(8);
	if (w<62) return BAR(9);
	if (w<95) return BAR(10);
	if (w<146) return BAR(11);
	if (w<225) return BAR(12);
	if (w<347) return BAR(13);
	if (w<535) return BAR(14);
	if (w<825) return BAR(15);
	return 0xffff;							//16;
}

//convert 10-digit dat to 20-led digits
//log-linear
uint32_t dat10_bar20(uint16_t w) {
	if (w<1) return BAR(0);
	if (w<1) return BAR(1);
	if (w<2) return BAR(2);
	if (w<3) return BAR(3);
	if (w<4) return BAR(4);
	if (w<6) return BAR(5);
	if (w<8) return BAR(6);
	if (w<11) return BAR(7);
	if (w<16) return BAR(8);
	if (w<23) return BAR(9);
	if (w<32) return BAR(10);
	if (w<45) return BAR(11);
	if (w<64) return BAR(12);
	if (w<91) return BAR(13);
	if (w<128) return BAR(14);
	if (w<181) return BAR(15);
	if (w<256) return BAR(16);
	if (w<362) return BAR(17);
	if (w<512) return BAR(18);
	if (w<724) return BAR(19);
	return 0xffffful;							//16;
}

//convert 16-bit data to 16-led digits
//log-linear
uint16_t dat16_bar16(uint16_t w) {
	if (w<1) return BAR(0);
	if (w<3) return BAR(1);
	if (w<6) return BAR(2);
	if (w<12) return BAR(3);
	if (w<23) return BAR(4);
	if (w<46) return BAR(5);
	if (w<91) return BAR(6);
	if (w<182) return BAR(7);
	if (w<363) return BAR(8);
	if (w<725) return BAR(9);
	if (w<1449) return BAR(10);
	if (w<2897) return BAR(11);
	if (w<5793) return BAR(12);
	if (w<11586) return BAR(13);
	if (w<23171) return BAR(14);
	if (w<47341) return BAR(15);
	return 0xffff;							//16;
}

//dot style routines
//log-linear for 8-bit data into 8-bit led
//log-linear
uint8_t dat8_dot8(uint8_t w) {
	if (w<1) return DOT(0);
	if (w<3) return DOT(1);
	if (w<6) return DOT(2);
	if (w<12) return DOT(3);
	if (w<23) return DOT(4);
	if (w<46) return DOT(5);
	if (w<91) return DOT(6);
	if (w<182) return DOT(7);
	return DOT(8);
}	

//convert 8-digit dat to 16-led digits
//log-linear
uint16_t dat8_dot16(uint8_t w) {
	if (w<1) return DOT(0);
	if (w<2) return DOT(1);
	if (w<3) return DOT(2);
	if (w<4) return DOT(3);
	if (w<5) return DOT(4);
	if (w<7) return DOT(5);
	if (w<10) return DOT(6);
	if (w<14) return DOT(7);
	if (w<20) return DOT(8);
	if (w<27) return DOT(9);
	if (w<39) return DOT(10);
	if (w<54) return DOT(11);
	if (w<77) return DOT(12);
	if (w<108) return DOT(13);
	if (w<153) return DOT(14);
	if (w<216) return DOT(15);
	return DOT(16);							//16;
}

//log-linear for 10-bit data into 8-bit led
//log-linear
uint8_t dat10_dot8(uint16_t w) {
	if (w<1) return DOT(0);
	if (w<4) return DOT(1);
	if (w<9) return DOT(2);
	if (w<21) return DOT(3);
	if (w<50) return DOT(4);
	if (w<118) return DOT(5);
	if (w<280) return DOT(6);
	if (w<664) return DOT(7);
	return DOT(8);
}	

//convert 10-digit dat to 12-led digits
//log-linear
uint16_t dat10_dot12(uint16_t w) {
	if (w<1) return DOT(0);
	if (w<2) return DOT(1);
	if (w<3) return DOT(2);
	if (w<6) return DOT(3);
	if (w<10) return DOT(4);
	if (w<18) return DOT(5);
	if (w<32) return DOT(6);
	if (w<57) return DOT(7);
	if (w<102) return DOT(8);
	if (w<181) return DOT(9);
	if (w<323) return DOT(10);
	if (w<575) return DOT(11);
	return DOT(12);							//16;
}

//convert 10-digit dat to 16-led digits
//log-linear
uint16_t dat10_dot16(uint16_t w) {
	if (w<1) return DOT(0);
	if (w<2) return DOT(1);
	if (w<3) return DOT(2);
	if (w<5) return DOT(3);
	if (w<8) return DOT(4);
	if (w<11) return DOT(5);
	if (w<17) return DOT(6);
	if (w<26) return DOT(7);
	if (w<40) return DOT(8);
	if (w<62) return DOT(9);
	if (w<95) return DOT(10);
	if (w<146) return DOT(11);
	if (w<225) return DOT(12);
	if (w<347) return DOT(13);
	if (w<535) return DOT(14);
	if (w<825) return DOT(15);
	return DOT(16);							//16;
}

//convert 16-bit data to 16-led digits
//log-linear
uint16_t dat16_dot16(uint16_t w) {
	if (w<1) return DOT(0);
	if (w<3) return DOT(1);
	if (w<6) return DOT(2);
	if (w<12) return DOT(3);
	if (w<23) return DOT(4);
	if (w<46) return DOT(5);
	if (w<91) return DOT(6);
	if (w<182) return DOT(7);
	if (w<363) return DOT(8);
	if (w<725) return DOT(9);
	if (w<1449) return DOT(10);
	if (w<2897) return DOT(11);
	if (w<5793) return DOT(12);
	if (w<11586) return DOT(13);
	if (w<23171) return DOT(14);
	if (w<47341) return DOT(15);
	return DOT(16);							//16;
}

