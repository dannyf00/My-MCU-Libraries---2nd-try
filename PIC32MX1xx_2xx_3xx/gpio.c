//gpio source file
#include "gpio.h"                                               //we use gpio

//void INTEnableSystemMultiVectoredInt(void);

//global defines

//global variables
volatile uint32_t 	SystemCoreClock = F_FRC;	//updated by sysclk_get()
#define _F_CPU 		SystemCoreClock				//updated by sysclk_get()

//switch system clock
void sysclk_set(uint32_t tgt_clk) {
	SYSKEY = 0; // ensure OSCCON is locked
	do {
		SYSKEY = 0xAA996655; 				// Write Key1 to SYSKEY
		SYSKEY = 0x556699AA; 				// Write Key2 to SYSKEY
		//OSCCONbits.CLKLOCK = 0;			//unlock clock
		OSCCON = (OSCCON & ~CLKFRCDIV_256) | (tgt_clk & CLKFRCDIV_256);
		OSCCON = (OSCCON & ~CLKNOSC_FRCDIV) | (tgt_clk & CLKNOSC_FRCDIV);	//111=FRCDIV, 110=FRC/16, 000=FRC
		OSCCON = (OSCCON & ~CLKPLLMULT_24) | (tgt_clk & CLKPLLMULT_24);		//set the multiplier
		OSCCON = (OSCCON & ~CLKPLLDIV_256) | (tgt_clk & CLKPLLDIV_256);		//set the divider
		OSCCONbits.OSWEN = 1;				//initialize a clock switch
	} while (OSCCONbits.OSWEN == 1);		//wait for the switch to complete
	SYSKEY = 0;								//lock syskey
}

//read sysclock back
uint32_t sysclk_get(void) {
	uint32_t tmp;									//read osccon

	switch (OSCCON & CLKCOSC_FRCDIV) {				//read current oscillator bits
		case CLKCOSC_FRCDIV: 						//FRCDIV
			tmp = F_FRC;
			switch (OSCCON & CLKFRCDIV_256) {
				case CLKFRCDIV_256: tmp /=256; break;
				case CLKFRCDIV_64:  tmp /= 64; break;
				case CLKFRCDIV_32:  tmp /= 32; break;
				case CLKFRCDIV_16:  tmp /= 16; break;
				case CLKFRCDIV_8:   tmp /=  8; break;
				case CLKFRCDIV_4:   tmp /=  4; break;
				case CLKFRCDIV_2:   tmp /=  2; break;
				case CLKFRCDIV_1:   tmp /=  1; break;
			}
			break;
		case CLKCOSC_FRC16:							//FRC / 16
			tmp = F_FRC / 16;
			break;
		case CLKCOSC_LPRC:							//LPRC
			tmp = F_LPRC;
			break;
		case CLKCOSC_SOSC:							//SOSC
			tmp = F_SOSC;
			break;
		case CLKCOSC_POSCPLL:						//Posc + PLL
			tmp = F_XTAL;
			//read FPLLIDIV
			switch (DEVCFG2bits.FPLLIDIV) {
				case 0b111: tmp /= 12; break;
				case 0b110: tmp /= 10; break;
				case 0b101: tmp /= 6; break;
				case 0b100: tmp /= 5; break;
				case 0b011: tmp /= 4; break;
				case 0b010: tmp /= 3; break;
				case 0b001: tmp /= 2; break;		//default
				case 0b000: tmp /= 1; break;
			}
			//read the multipliers first
			switch (OSCCON & CLKPLLMULT_24) {
				case CLKPLLMULT_24: tmp *= 24; break;
				case CLKPLLMULT_21: tmp *= 21; break;
				case CLKPLLMULT_20: tmp *= 20; break;
				case CLKPLLMULT_19: tmp *= 19; break;
				case CLKPLLMULT_18: tmp *= 18; break;
				case CLKPLLMULT_17: tmp *= 17; break;
				case CLKPLLMULT_16: tmp *= 16; break;
				case CLKPLLMULT_15: tmp *= 15; break;
			}
			//read the divider
			switch (OSCCON & CLKPLLDIV_256) {
				case CLKPLLDIV_256: tmp /=256; break;
				case CLKPLLDIV_64:  tmp /= 64; break;
				case CLKPLLDIV_32:  tmp /= 32; break;
				case CLKPLLDIV_16:  tmp /= 16; break;
				case CLKPLLDIV_8:   tmp /=  8; break;
				case CLKPLLDIV_4:   tmp /=  4; break;
				case CLKPLLDIV_2:   tmp /=  2; break;
				case CLKPLLDIV_1:   tmp /=  1; break;
			}
			break;
		case CLKCOSC_POSC: 							//Posc
			tmp = F_XTAL;
			break;
		case CLKCOSC_FRCPLL:						//FRCPLL
			tmp = F_FRC;							//FRC input PLL divider set to DIV_2 in config bits
			//read FPLLIDIV
			switch (DEVCFG2bits.FPLLIDIV) {
				case 0b111: tmp /= 12; break;
				case 0b110: tmp /= 10; break;
				case 0b101: tmp /= 6; break;
				case 0b100: tmp /= 5; break;
				case 0b011: tmp /= 4; break;
				case 0b010: tmp /= 3; break;
				case 0b001: tmp /= 2; break;		//default
				case 0b000: tmp /= 1; break;
			}
			//read the multipliers first
			switch (OSCCON & CLKPLLMULT_24) {
				case CLKPLLMULT_24: tmp *= 24; break;
				case CLKPLLMULT_21: tmp *= 21; break;
				case CLKPLLMULT_20: tmp *= 20; break;
				case CLKPLLMULT_19: tmp *= 19; break;
				case CLKPLLMULT_18: tmp *= 18; break;
				case CLKPLLMULT_17: tmp *= 17; break;
				case CLKPLLMULT_16: tmp *= 16; break;
				case CLKPLLMULT_15: tmp *= 15; break;
			}
			//read the divider
			switch (OSCCON & CLKPLLDIV_256) {
				case CLKPLLDIV_256: tmp /= 256; break;
				case CLKPLLDIV_64:  tmp /= 64; break;
				case CLKPLLDIV_32:  tmp /= 32; break;
				case CLKPLLDIV_16:  tmp /= 16; break;
				case CLKPLLDIV_8:   tmp /=  8; break;
				case CLKPLLDIV_4:   tmp /=  4; break;
				case CLKPLLDIV_2:   tmp /=  2; break;
				case CLKPLLDIV_1:   tmp /=  1; break;
			}
			break;
		case CLKCOSC_FRC: 							//internal oscillator
			tmp = F_FRC;
			break;
	}
	_F_CPU = tmp;									//update _F_CPU
	return _F_CPU;
}

//switch reference clock
//tgt_clk: use REFOSC_ and REFODIV() macros
//pllotrim: use REFOTRIM() macros
void refclk_set(uint32_t tgt_clk,uint32_t pllotrim) {
	REFOCON = tgt_clk & ~(1<<15);					//set refocon, don't turn on the oscillator yet

	REFOTRIM = REFOTRIM(pllotrim);	//set the trim
	REFOCON |= tgt_clk & (1<<15);					//turn on the oscillator
}

//get reference clock


//reset the mcu

void mcu_init(void) {

	/* Set the system and peripheral bus speeds and enable the program cache*/

	//SYSTEMConfigPerformance( F_CPU );

	//mOSCSetPBDIV( OSC_PB_DIV_2 );

	//clock defaults to FRC
	//set PBDIV to 1:1
	//unlock sequency
	//SYSKEY = 0x0; 									// ensure OSCCON is locked
	//SYSKEY = 0xAA996655; 							// Write Key1 to SYSKEY
	//SYSKEY = 0x556699AA; 							// Write Key2 to SYSKEY
	// OSCCON is now unlocked
	// make the desired change
	//OSCCON = (OSCCON &~0x00180000ul) | (0x00 & 0x00180000ul);	//or to set through config bits
	//lock sequency
	//SYSKEY = 0x00;									//write any value to lock


	//turn off all peripherals
#if defined(PMD1)
	PMD1=0xffff;
#endif
#if defined(PMD2)
	PMD2=0xffff;
#endif
#if defined(PMD3)
	PMD3=0xffff;
#endif
#if defined(PMD4)
	PMD4=0xffff;
#endif
#if defined(PMD5)
	PMD5=0xffff;
#endif
#if defined(PMD6)
	PMD6=0xffff;
#endif

	//all pins digital
//#if defined(ANSELA)
    ANSELA = 0x0000;
//#endif
//#if defined(ANSELB)
    ANSELB = 0x0000;
//#endif
//#if defined(ANSELC)
    //ANSELC = 0x0000;
//#endif

//#if defined(AD1PCFG)
    //AD1PCFG = 0xffff;
//#endif

	//disable interrupts
	//__builtin_disable_interrupts();			//disable interrupts
	//INTDisableInterrupts();
	//enable multivector mode
	//INTCONbits.MVEC = 1;					//1=enable multiple vector
	//__builtin_enable_interrupts();			//enable interrupts
	//INTEnableInterrupts();
	//INTEnableSystemMultiVectoredInt();
	INTCONbits.MVEC = 1;					//1=enable multi-vectored interrupts, 0=disable

	SystemCoreClockUpdate();				//update SystemCoreClock

	//enable global interrupts
	ei();							//testing

}
