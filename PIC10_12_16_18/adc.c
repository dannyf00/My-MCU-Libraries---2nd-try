//#include <pic.h>						//we use picc
//#include "gpio.h"
#include "adc.h"						//we use adc

#if defined(ADC_v1)						//12f675
void adc_init(void) {
	//set the clock frequency
	//ADCS2=1, ADCS1=0, ADCS0=1;		//adcs2..0=0b110 -> adc clock 1:64
	ADCS2=0, ADCS1=1, ADCS0=1;			//adcs2..0=0bx11 -> used dedicated ADC RC oscillator
	CHS1=0, CHS0=0;						//chs1..0=0b00->AN0 selected
	ADFM = 1;							//adc results right justified
	VCFG = 0;							//use Vdd
	ADIF = 0;							//cleara adif
	ADIE = 0;							//0=disable adie, 1=enable adie
	ADON=1;								//turn on the adc
}

unsigned short adc_read(unsigned char ch) {
	//unsigned char sANSEL=ANSEL, sANSELH=ANSELH, sADCON0=ADCON0;		//shadow variables to save anselh/l
	//configure ADCON0's CHS3..0 bits and ANSEL
	switch (ch & ADC_MASK) {
		case ADC_0: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_0; ANS3=0, ANS2=0, ANS1=0, ANS0=1;break;
		case ADC_1: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_1; ANS3=0, ANS2=0, ANS1=1, ANS0=0;break;
		case ADC_2: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_2; ANS3=0, ANS2=1, ANS1=0, ANS0=0;break;
		case ADC_3: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_3; ANS3=1, ANS2=0, ANS1=0, ANS0=0;break;
		default: while (1) continue;	//error trap
	}
	adc_delay();						//for Tacq
	//ANSEL |= ch; 						//analog select the channel
	//IO_IN(TRISA, ch); 				//turn the port to be digital input
	GODONE=1;							//turn on the adc
	while (GODONE) continue;			//wait for adc to finish
	//restore old values to ansel/h
	//ANSEL = sANSEL, ANSELH = sANSELH, ADCON0 = sADCON0;
	return (ADRESH << 8) | ADRESL;
}

#elif defined(ADC_v2)					//16f684
//functions for 16f684
void adc_init(void) {
	//set the clock frequency
	//ADCS2=1, ADCS1=1, ADCS0=1;			//adcs2..0=0b110 -> adc clock 1:64
	ADCS2=0, ADCS1=1, ADCS0=1;			//adcs2..0=0bx11 -> used dedicated ADC RC oscillator
	CHS1=0, CHS0=0;						//chs1..0=0b00->AN0 selected
	ADFM = 1;							//adc results right justified
	VCFG = 0;							//0=use Vdd, 1=use Vref
	ADIF = 0;							//cleara adif
	ADIE = 0;							//0=disable adie, 1=enable adie
	ADON=1;								//turn on the adc
}

unsigned short adc_read(unsigned char ch) {
	//unsigned char sANSEL=ANSEL, sANSELH=ANSELH, sADCON0=ADCON0;		//shadow variables to save anselh/l
	//configure ADCON0's CHS3..0 bits and ANSEL
	switch (ch & ADC_MASK) {
		case ADC_0: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_0; ANSEL = 0x01;break;
		case ADC_1: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_1; ANSEL = 0x02;break;
		case ADC_2: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_2; ANSEL = 0x04;break;
		case ADC_3: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_3; ANSEL = 0x08;break;
		case ADC_4: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_4; ANSEL = 0x10;break;
		case ADC_5: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_5; ANSEL = 0x20;break;
		case ADC_6: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_6; ANSEL = 0x40;break;
		case ADC_7: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_7; ANSEL = 0x80;break;
		default: while (1) continue;	//error trap
	}
	adc_delay();						//for Tacq
	//ANSEL |= ch; 						//analog select the channel
	//IO_IN(TRISA, ch); 				//turn the port to be digital input
	GODONE=1;							//turn on the adc
	while (GODONE) continue;			//wait for adc to finish
	//restore old values to ansel/h
	//ANSEL = sANSEL, ANSELH = sANSELH, ADCON0 = sADCON0;
	return (ADRESH << 8) | ADRESL;
}

#elif defined(ADC_v3)					//adc for 16f886
//functions for 16F886
void adc_init(void) {
	//set the clock frequency
	ADCS1=0, ADCS0=1;					//adc clock 1:8
	//ADCS1=1, ADCS0=1;					//adc clock: dedicated rc oscillator
	CHS3=0, CHS2=0, CHS1=0, CHS0=0;		//chs3..0=0b0000->AN0 selected
	ADFM = 1;							//adc results right justified
	VCFG1=0;							//use GND as ground
	VCFG0=0;							//use Vdd
	ADIF = 0;							//clear the adc flag
	ADIE = 0;							//0=disable adc interrupt; 1=enable adc interrupt
	//PEIE = 0;							//0=disable peie; 1=enable peie
	ADON=1;								//turn on the adc
}

unsigned short adc_read(unsigned char ch) {
	//unsigned char sANSEL=ANSEL, sANSELH=ANSELH, sADCON0=ADCON0;		//shadow variables to save anselh/l
	//configure ADCON0's CHS3..0 bits and ANSEL
	switch (ch & ADC_MASK) {
		case ADC_0:  ADCON0=(ADCON0 & ~ADC_MASK) | ADC_0;  ANSEL=1<<0; ANSELH=0<<0; break;
		case ADC_1:  ADCON0=(ADCON0 & ~ADC_MASK) | ADC_1;  ANSEL=1<<1; ANSELH=0<<0; break;
		case ADC_2:  ADCON0=(ADCON0 & ~ADC_MASK) | ADC_2;  ANSEL=1<<2; ANSELH=0<<0; break;
		case ADC_3:  ADCON0=(ADCON0 & ~ADC_MASK) | ADC_3;  ANSEL=1<<3; ANSELH=0<<0; break;
		case ADC_4:  ADCON0=(ADCON0 & ~ADC_MASK) | ADC_4;  ANSEL=1<<4; ANSELH=0<<0; break;
		case ADC_5:  ADCON0=(ADCON0 & ~ADC_MASK) | ADC_5;  ANSEL=1<<5; ANSELH=0<<0; break;
		case ADC_6:  ADCON0=(ADCON0 & ~ADC_MASK) | ADC_6;  ANSEL=1<<6; ANSELH=0<<0; break;
		case ADC_7:  ADCON0=(ADCON0 & ~ADC_MASK) | ADC_7;  ANSEL=0<<7; ANSELH=0<<0; break;
		case ADC_8:  ADCON0=(ADCON0 & ~ADC_MASK) | ADC_8;  ANSEL=0<<0; ANSELH=1<<0; break;
		case ADC_9:  ADCON0=(ADCON0 & ~ADC_MASK) | ADC_9;  ANSEL=0<<0; ANSELH=1<<1; break;
		case ADC_10: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_10; ANSEL=0<<0; ANSELH=1<<2; break;
		case ADC_11: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_11; ANSEL=0<<0; ANSELH=1<<3; break;
		case ADC_12: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_12; ANSEL=0<<0; ANSELH=1<<4; break;
		case ADC_13: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_13; ANSEL=0<<0; ANSELH=1<<5; break;
		case ADC_VREF: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_VREF; ANSEL=0<<0; ANSELH=0<<0; break;
		case ADC_FREF: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_FREF; ANSEL=0<<0; ANSELH=0<<0; break;
		default: while (1) continue;	//error trap
	}
	adc_delay();						//for Tacq
	//ANSEL |= ch; 						//analog select the channel
	//IO_IN(TRISA, ch); 				//turn the port to be digital input
	GODONE=1;							//turn on the adc
	while (GODONE) continue;			//wait for adc to finish
	//restore old values to ansel/h
	//ANSEL = sANSEL, ANSELH = sANSELH, ADCON0 = sADCON0;
	return (ADRESH << 8) | ADRESL;
}

#elif   defined(ADC_v4)					//adc for 16f193x
//functions for 16F886
void adc_init(void) {
	//set the clock frequency
	ADCS2=0, ADCS1=0, ADCS0=1;			//adc clock. 0b000=2:1, 100=4:1, 001=8:1, 101=16:1, 010=32:1, 110=64:1, 011/111=dedicated rc oscillator
	//ADCS1=1, ADCS0=1;					//adc clock: dedicated rc oscillator
	//CHS3=0, CHS2=0, CHS1=0, CHS0=0;		//chs3..0=0b0000->AN0 selected
	ADFM = 1;							//adc results right justified
	ADNREF = 0;							//VCFG1=0;							//use GND as ground
	ADPREF1=0, ADPREF0=0;				//VCFG0=0;							//use Vdd
	//ADPREF1=0, ADPREF0=1;				//reserved
	//ADPREF1=1, ADPREF0=0;				//Use +Vref pin
	//ADPREF1=1, ADPREF0=1;				//Use internal Reference (FVR=1.024/2.048/4.096v)
	ADIF = 0;							//clear the adc flag
	ADIE = 0;							//0=disable adc interrupt; 1=enable adc interrupt
	//PEIE = 0;							//0=disable peie; 1=enable peie
	ADON=1;								//turn on the adc
}

unsigned short adc_read(unsigned char ch) {
	//unsigned char sANSEL=ANSEL, sANSELH=ANSELH, sADCON0=ADCON0;		//shadow variables to save anselh/l
	//configure ADCON0's CHS3..0 bits and ANSEL
	switch (ch & ADC_MASK) {
		case ADC_0: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_0; ANSELA=1<<0; break;
		case ADC_1: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_1; ANSELA=1<<1; break;
		case ADC_2: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_2; ANSELA=1<<2; break;
		case ADC_3: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_3; ANSELA=1<<3; break;
		case ADC_4: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_4; ANSELA=1<<4; break;
//AN5/6/7 only available for 16F1934/1937/1939)
#if		defined(_16F1934) || defined(_16F1937) || defined(_16F1939) || \
		defined(_16LF1934) || defined(_16LF1937) || defined(_16LF1939)
		case ADC_5: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_5; ANSELE=1<<0; break;
		case ADC_6: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_6; ANSELE=1<<1; break;
		case ADC_7: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_7; ANSELE=1<<2; break;
#endif
		case ADC_8: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_8; ANSELB=1<<2; break;
		case ADC_9: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_9; ANSELB=1<<3; break;
		case ADC_10: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_10; ANSELB=1<<1; break;
		case ADC_11: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_11; ANSELB=1<<4; break;
		case ADC_12: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_12; ANSELB=1<<0; break;
		case ADC_13: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_13; ANSELB=1<<5; break;
		case ADC_TEMP: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_TEMP; break;
		case ADC_DAC: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_DAC; break;
		case ADC_FVR: ADCON0=(ADCON0 & ~ADC_MASK) | ADC_FVR; break;
		default: while (1) continue;	//error trap
	}
	adc_delay();						//for Tacq
	//ANSEL |= ch; 						//analog select the channel
	//IO_IN(TRISA, ch); 				//turn the port to be digital input
	GODONE=1;							//turn on the adc
	while (GODONE) continue;			//wait for adc to finish
	//restore old values to ansel/h
	//ANSEL = sANSEL, ANSELH = sANSELH, ADCON0 = sADCON0;
	return (ADRESH << 8) | ADRESL;
}

#else
//no functions defined for the select chip
  #warning adc.c - no adc functions defined on select chip
#endif
