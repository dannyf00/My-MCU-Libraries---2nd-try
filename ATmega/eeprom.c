#include <avr/io.h>						//we use gcc-avr
#include <avr/eeprom.h>						//we use avr eeprom
#include "gpio.h"
#include "eeprom.h"						//we use eeprom


//eeprom read, from usb1286 datasheet
unsigned char eeprom_read(unsigned int uiAddress) {
	//char cSREG;
	//cSREG = SREG; 					/* store SREG value */
	/* disable interrupts during timed sequence */
	//di();							//__disable_interrupt();
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE)) continue;
	//;
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	//SREG = cSREG;						//restore sreg
	return EEDR;
}

#pragma GCC optimize ("O3")					//to make sure that the eecr maintains the right timing
//eeprom write, from usb1286 datasheet
void eeprom_write(unsigned int uiAddress, unsigned char ucData) {
	//char cSREG;
	//cSREG = SREG; 					/* store SREG value */
	/* disable interrupts during timed sequence */
	//di();							//__disable_interrupt();
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE)) continue;
	do {
		/* Set up address and Data Registers */
		EEAR = uiAddress;
		EEDR = ucData;
		/* Write logical one to EEMPE */
		EECR |= (1<<EEMPE);
		//per datasheet, the following has to happen within 4 cycles
		//may need to look at the list file to confirm
		//otherwise, increase the optimization levels O2 or higher
		/* Start eeprom write by setting EEPE */
		EECR |= (1<<EEPE);				//need to be within 4 cycles of setting EEMPE
	} while (eeprom_read(uiAddress) ^ ucData);		//make sure that write is successful
	//SREG = cSREG;						//restore sreg
}

