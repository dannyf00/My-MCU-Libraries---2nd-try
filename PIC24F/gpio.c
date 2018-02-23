//gpio for PIC24
//primarily to read DEVID and DEVREV

#include "gpio.h"						//not really used

uint32_t SystemCoreClock=8000000ul;		//systemcoreclock = Peripheral clock
uint32_t F_CPU=8000000ul;			//CPU clock
uint32_t F_REFO=8000000ul;		//refclock output

//read devid @ 0xff0000
unsigned int DEVID(void) {
	TBLPAG = 0x00ff;
	return __builtin_tblrdl(0x0000);	//for DEVID @ 0xff0000
}

//read devrev @ 0xff0002
unsigned int DEVREV(void) {
	TBLPAG = 0x00ff;
	return __builtin_tblrdl(0x0002);	//for DEVID @ 0xff0000
}

//read device id / rev
//devid at low 16 bits and rev high 16-bits, to be compatible with pic32
unsigned long DEVIDREV(void) {
	unsigned long tmp;
	tmp=DEVREV();						//read the rev
	tmp=(tmp << 16) | DEVID();			//read id
	return tmp;
}

//set FRC
//clk:
//0x0000->0x0700: div
//0x8000->PLLx (4x)
uint32_t SystemCoreClock2FRC(uint32_t clk) {
	uint32_t tmp;

	tmp = clk & 0x0700;					//tmp = CLKDIV

}
//update systemcoreclock / Pheripheral clock
uint32_t SystemCoreClockUpdate(void) {
	uint32_t tmp = F_FRC;				//default to FRC

	//pick clock source
	switch (OSCCON & 0x7000) {			//get the COSC2..0 bits
		case 7<<12: tmp = F_FRC; 			//FRCDIV used
					switch (CLKDIV & 0x0700) {	//look to CLKDIV:RCDIV2..0 bits
						case 7<<8: tmp /=128; break;
						case 6<<8: tmp /= 64; break;
						case 5<<8: tmp /= 32; break;
						case 4<<8: tmp /= 16; break;
						case 3<<8: tmp /=  8; break;
						case 2<<8: tmp /=  4; break;
						case 1<<8: tmp /=  2; break;
						case 0<<8: tmp /=  1; break;
					}
					break;
		case 5<<12: tmp = F_LPRC; break;	//LPRC
		case 4<<12: tmp = F_SOSC; break;	//SOSC
		case 3<<12: tmp = F_XTAL * 4; break;		//XTALxPLL used
		case 2<<12: tmp = F_XTAL; break;	//XTAL
		case 1<<12: tmp = F_FRC * 4;			//FRXcPLL used
					switch (CLKDIV & 0x0700) {	//look to CLKDIV:RCDIV2..0 bits
						case 7<<8: tmp /=128; break;
						case 6<<8: tmp /= 64; break;
						case 5<<8: tmp /= 32; break;
						case 4<<8: tmp /= 16; break;
						case 3<<8: tmp /=  8; break;
						case 2<<8: tmp /=  4; break;
						case 1<<8: tmp /=  2; break;
						case 0<<8: tmp /=  1; break;
					}
					break;
		case 0<<12: tmp = F_FRC; break;		//frc used
	}
	SystemCoreClock = tmp;					//update systemcoreclock
	//update F_CPU
	if (CLKDIV & (1<<11)) {					//doze2..0 used
		switch (CLKDIV & 0x7000) {
			case 7<<8: tmp /=128; break;
			case 6<<8: tmp /= 64; break;
			case 5<<8: tmp /= 32; break;
			case 4<<8: tmp /= 16; break;
			case 3<<8: tmp /=  8; break;
			case 2<<8: tmp /=  4; break;
			case 1<<8: tmp /=  2; break;
			case 0<<8: tmp /=  1; break;
		}
	}
	F_CPU = tmp;							//update cpu clock
	//calculate F_REFO
	if (REFOCON & (1<<12)) tmp = F_XTAL;	//1->primary oscillator is used as input to refo
	else tmp = SystemCoreClock;				//use systemcoreclock as input
	switch (REFOCON & 0x0f00) {
		case 0x0f: tmp /= 32768; break;
		case 0x0e: tmp /= 16384; break;
		case 0x0d: tmp /=  8192; break;
		case 0x0c: tmp /=  4096; break;
		case 0x0b: tmp /=  2048; break;
		case 0x0a: tmp /=  1024; break;
		case 0x09: tmp /=   512; break;
		case 0x08: tmp /=   256; break;
		case 0x07: tmp /=   128; break;
		case 0x06: tmp /=    64; break;
		case 0x05: tmp /=    32; break;
		case 0x04: tmp /=    16; break;
		case 0x03: tmp /=     8; break;
		case 0x02: tmp /=     4; break;
		case 0x01: tmp /=     2; break;
		case 0x00: tmp /=     1; break;
	}
	F_REFO = tmp;								//update refo output clock
	return SystemCoreClock;
}

//reset the mcu
void mcu_init(void) {
	//turn off all peripherals
	PMD1=0xffff;
	PMD2=0xffff;
	PMD3=0xffff;
#if defined(PMD4)
	PMD4=0xffff;
#endif

	//all pins digital
#if defined(AD1PCFG)
	AD1PCFG = 0xffff;					//all pins digital
#endif
	//or AD1PCFGH
#if defined(AD1PCFGH)
	AD1PCFGH = 0xffff;					//all pins digital
#endif
	//or AD1PCFGL
#if defined(AD1PCFGL)
	AD1PCFGL = 0xffff;					//all pins digital
#endif
}

