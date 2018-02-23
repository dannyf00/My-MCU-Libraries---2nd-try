#include "gpio.h"

//reset the mcu
void mcu_init(void) {
//12F675
#if 	defined(_12F629)	|| defined(_12F675)
	CMCON = 0x07;						//turn off analog comparator
	ANSEL = 0x00;						//all pins gpio

//16F627/16F628/16F648
#elif	defined(_16F627A) || defined(_16F628A) || defined(_16F648A) || defined(_16F627 ) || defined(_16F628 ) || defined(_16F648 )

	//ADCON1 = 0x0f;					//all pins digital - no adc module
	CMCON = 0x07;						//analog comparators off
	//IRCF2 = 1, IRCF1 = 0, IRCF0 = 1;	//0b111->16Mhz, 0b101->4Mhz, ircf2..0=0b011 -> 1Mhz

//16f630 / 676
#elif	defined(_16F630) || defined(_16F676)

	ANSEL = 0x00;						//all pins digital
	CMCON = 0x07;						//analog comparator off
	
//16F631/677/685/687/689/690
//16F882/883/884/886/887
#elif	defined(_16F631) || defined(_16F677) || defined(_16F685) || defined(_16F687) || defined(_16F689) || defined(_16F690) || \
		defined(_16F882)	|| defined(_16F883)	|| defined(_16F884)	|| defined(_16F886)	|| defined(_16F887)

	ANSEL = ANSELH = 0;					//all ports digital
	C1ON = 0;							//CM1CON0 = 0x00;						//turn off comparator 1
	C2ON = 0;							//CM2CON0 = 0x00;						//turn off comparator 2
	IRCF2 = 1, IRCF1 = 1, IRCF0 = 0;	//0b110 = 4Mhz.
	
//16F684
#elif 	defined(_16F684)
	ANSEL = 0x00;						//porta are digital io
	//ANSELH = 0x00;					//all portB is digital io
	CM2=CM1=CM0=1;						//CMCON0 = 0x07;						//analog comparators off

	IRCF2 = 1, IRCF1 = 0, IRCF0 = 1;	//0b111->16Mhz, 0b101->4Mhz, ircf2..0=0b011 -> 1Mhz

//16f1826/1827
#elif	defined(_16F1826) || defined(_16F1827) || \
		defined(_16LF1826) || defined(_16LF1827)
		
		IRCF3 = 1, IRCF2 = 1, IRCF1 = 0, IRCF0 = 1;	//0b1111 = 16Mhz, 0b1110 = 8Mhz, 0b1101 = 4Mhz, 0b1100 = 2Mhz, 0b1011 = 1Mhz
		ANSELA = ANSELB = 0x00;			//all pins digital
		C1ON = 0;						//turn off comparator 1
		C2ON = 0;						//turn off comparator 2

//16F1936/1937/1938/1939
#elif 	defined(_16F1933) || defined(_16F1934) || defined(_16F1936) || defined(_16F1937) || defined(_16F1938) || defined(_16F1939) || \
		defined(_16LF1933) || defined(_16LF1934) || defined(_16LF1936) || defined(_16LF1937) || defined(_16LF1938) || defined(_16LF1939)

	ANSELA = 0x00;						//all pins gpio
	ANSELB = 0x00;
	CM1CON0 = 0x00;						//turn off analog comparators
	CM2CON0 = 0x00;
	APFCON = 0x00;                      //choose default functions

	IRCF3=1, IRCF2=1, IRCF1=1, IRCF0=1;	//0b1111->16Mhz, 0b1110->8Mhz, 0b1101->4Mhz

//18F1xK22
#elif	defined (_18F13K22) || defined (_18F14K22) || defined (_18LF13K22) || defined (_18LF14K22)
	ANSEL = ANSELH = 0;					//all pings gpio
	C1ON = C2ON = 0;					//disable analog comparators
	IRCF2 = 1, IRCF1 = 0, IRCF0 = 1;	//0b111->16Mhz, 0b101->4Mhz, ircf2..0=0b011 -> 1Mhz

//18FxxK20
#elif	defined(_18F23K20) || defined(_18F24K20) || defined(_18F25K20) || defined(_18F26K20) || \
       	defined(_18F43K20) || defined(_18F44K20) || defined(_18F45K20) || defined(_18F46K20)
	ANSEL = 0x00;						//all pins digital
	ANSELH= 0x00;
	CM1CON0 = 0x00;						//analog comparators off
	CM2CON0 = 0x00;

	IRCF2 = 1, IRCF1 = 1, IRCF0 = 1;	//0b111->16Mhz, 0b101->4Mhz, ircf2..0=0b011 -> 1Mhz

//18FxxK22
#elif   defined (_18F23K22) || defined (_18F24K22) || defined (_18F25K22) || defined (_18F26K22) || \
        defined (_18F43K22) || defined (_18F44K22) || defined (_18F45K22) || defined (_18F46K22) || \
        defined (_18LF23K22) || defined (_18LF24K22) || defined (_18LF25K22) || defined (_18LF26K22) || \
        defined (_18LF43K22) || defined (_18LF44K22) || defined (_18LF45K22) || defined (_18LF46K22)

	ANSELA = ANSELB = ANSELC = 0x00;	//all pins digital
#if	defined(_18F43K22) || defined(_18F44K22) || defined(_18F45K22) || defined(_18F46K22)
	ANSELD = ANSELE = 0x00;				//for 18F4xK22 devices only
#endif
	CM1CON0 = 0x00;						//analog comparators off
	CM2CON0 = 0x00;

	IRCF2 = 1, IRCF1 = 0, IRCF0 = 1;	//0b111->16Mhz, 0b101->4Mhz, ircf2..0=0b011 -> 1Mhz

//18F4520

#elif defined(_18F2420) || defined(_18F2520) || defined(_18F4420) || defined(_18F4520) 

	PCFG3=1, PCFG2=1, PCFG1=1, PCFG1=1; //all pins digital
	CM2=1, CM1=1, CM0=1; //analog comparators off
	IRCF2 = 1, IRCF1 = 1, IRCF0 = 0; //0b111->8Mhz, 0b110->4Mhz, 0b101->2Mhz,... 

//18F6627
#elif	defined(_18F6627) || defined(_18F6722) || defined(_18F8627) || defined(_18F8722) || \
		defined(_18F6527) || defined(_18F6622) || defined(_18F8527) || defined(_18F8622) || \
		defined(_18F6628) || defined(_18F6723) || defined(_18F8628) || defined(_18F8723) || \
		defined(_18F2585) || defined(_18F4585) || defined(_18F2680) || defined(_18F4680)

	ADCON1 = 0x0f;						//all pins digital
	CMCON = 0x07;						//analog comparators off
	IRCF2 = 1, IRCF1 = 0, IRCF0 = 1;	//0b111->16Mhz, 0b101->4Mhz, ircf2..0=0b011 -> 1Mhz

#elif   defined (_18F2331) || defined (_18F2431) || defined (_18F4331) || defined (_18F4431)
	ANSEL0 = 0x00;						//analog functions off
	ANSEL1 = 0x00;
	IRCF2 = 1, IRCF1 = 1, IRCF0 = 0;	//0b111->8Mhz, 0b110->4Mhz, 0b101->2Mhz
	
//18f2550/4550
#elif	defined(_18F2455) || defined(_18F2550) || defined(_18F4455) || defined(_18F4550) || \
		defined(_18F2458) || defined(_18F2553) || defined(_18F4458) || defined(_18F4553)

	ADCON1 = 0x0f;						//all pins digital
	CMCON  = 0x07;						//all analog comparators off
	//IRCF2 = 1, IRCF1 = 1, IRCF0 = 0;	//0b111->8Mhz, 0b110->4Mhz, 0b101->2Mhz, ...

#else
//missing header files
#warning no device header file defined in gpio.c!

#endif
}
