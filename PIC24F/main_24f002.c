#include <p24fxxxx.h>					//we use pic24f
#include "gpio.h"

#ifdef __24FJ64GA102_H
//config fues settings for 24fj64ga102
///config fues settings
_CONFIG1(	JTAGEN_OFF &				//Disable JTAG port 
		GCP_OFF &						//Disable code protect 
		GWRP_OFF &						//Disable write protect 
		ICS_PGx2 &						//EMUC/EMUD share PGC2/PGD2 
		//BKBUG_ON &					//Enable background debugger 
		//COE_OFF &						//Device resets into operational mode 
		FWDTEN_OFF &					//Disable watchdog timer (WDT) 
		WINDIS_OFF &					//Use standard WDT (if it is enabled) 
		FWPSA_PR128 &					//Use WDT prescaler ratio of 1:128 
		WDTPS_PS32768					//Use WDT postscaler ratio of 1:32,768 
		)
  
_CONFIG2(	IESO_OFF &					//Disabled
		SOSCSEL_SOSC &					//Default Secondary Oscillator
		WUTSEL_LEG &					//Legacy Wake-up timer selected
		FNOSC_PRI &						//FNOSC_PRO = Primary oscillator (XT, HS, EC). FNOSC_FRC -> 8Mhz internal rc (default to 2Mhz)
		FCKSM_CSDCMD &					//Clock switching and clock monitor disabled 
		OSCIOFNC_OFF &					//OSCO or Fosc/2
		IOL1WAY_OFF &					//Unlimited Writes To RP Registers
		I2C1SEL_PRI &					//Use Primary I2C1 pins
		POSCMOD_XT						//High speed seeting for external oscillator 
		)
  
_CONFIG3(	WPFP_WPFP63 &				//Highest Page (same as page 42)
		SOSCSEL_IO &					//SOSC pins have digital I/O functions (RA4, RB4)
		WUTSEL_LEG &					//Default regulator start-up time used
		WPDIS_WPDIS &					//Segmented code protection disabled
		WPCFG_WPCFGDIS &				//Last page and Flash Configuration words are unprotected
		WPEND_WPENDMEM					//Write Protect from WPFP to the last page of memory
		)
  
_CONFIG4(	DSWDTPS_DSWDTPSF &			//1:2,147,483,648 (25.7 days)
		DSWDTOSC_LPRC &					//DSWDT uses Low Power RC Oscillator (LPRC)
		//DSWDTOSC_SOSC &				//DSWDT uses Secondary Oscillator (SOSC)
		RTCOSC_LPRC &					//RTCC uses Low Power RC Oscillator (LPRC)
		//RTCOSC_SOSC &					//RTCC uses Secondary Oscillator (SOSC)
		DSBOREN_OFF &					//BOR disabled in Deep Sleep
		DSWDTEN_OFF 					//DSWDT disabled
		)
         
#else
//config fues settings for everything else - need customization
_CONFIG1(	JTAGEN_OFF &				//Disable JTAG port 
		GCP_OFF &						//Disable code protect 
		GWRP_OFF &						//Disable write protect 
		ICS_PGx2 &						//EMUC/EMUD share PGC2/PGD2 
		//BKBUG_ON &					//Enable background debugger 
		//COE_OFF &						//Device resets into operational mode 
		FWDTEN_OFF &					//Disable watchdog timer (WDT) 
		WINDIS_OFF &					//Use standard WDT (if it is enabled) 
		FWPSA_PR128 &					//Use WDT prescaler ratio of 1:128 
		WDTPS_PS32768					//Use WDT postscaler ratio of 1:32,768 
		)
  
_CONFIG2(	IESO_OFF &					//Disabled
		SOSCSEL_SOSC &					//Default Secondary Oscillator
		WUTSEL_LEG &					//Legacy Wake-up timer selected
		FNOSC_PRI &						//FNOSC_PRO = Primary oscillator (XT, HS, EC). FNOSC_FRC -> 8Mhz internal rc (default to 2Mhz)
		FCKSM_CSDCMD &					//Clock switching and clock monitor disabled 
		OSCIOFNC_OFF &					//OSCO or Fosc/2
		IOL1WAY_OFF &					//Unlimited Writes To RP Registers
		I2C1SEL_PRI &					//Use Primary I2C1 pins
		POSCMOD_XT						//High speed seeting for external oscillator 
		)
#endif

//default configuration setting
//_CONFIG2( IESO_OFF & FNOSC_PRI & FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_XT)
//_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & ICS_PGx2 & FWDTEN_OFF & WINDIS_OFF);

//_CONFIG1(JTAGEN_OFF & GCP_OFF & FWDTEN_OFF); 	//JTAG OFF, CODE PROTECTION OFF, WATCH DOG TIMER OFF
//_CONFIG2(IESO_OFF & FNOSC_PRI & FCKSM_CSDCMD & POSCMOD_XT); 	//TWO-STAGE START OFF, PRIMARY OSCILLATOR (HS/XT/EC), CLOCK FAILURE SWITCH DISABLED, PRIMARY OSCILLATOR IS XT

//hardware configuration
//end hardware configuration

void mcu_init(void) {
}
	
//main code section
int main(void)
{         
	mcu_init();						//reset the mcu


	ei();
	while(1) {
		//flp();
	}           
}

