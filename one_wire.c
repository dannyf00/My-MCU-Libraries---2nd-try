//code shamelessly stolen from Maxim-ic's application 126
//#include <lpc210x.h>					//we use lpc
#include <regx51.h>						//we use keil c51
#include "gpio.h"
#include "delay.h"
#include "one_wire.h"					//we use one_wire

//max delay of 255us
//#define tickDelay(x)	DelayUs(x)

//-----------------------------------------------------------------------------
// Generate a 1-Wire reset, return 1 if no presence detect was found,
// return 0 otherwise.
// (NOTE: Does not handle alarm presence from DS2404/DS1994)
//
unsigned char ow_init(unsigned int ow_pin) {
	char result;

	delay_1u();							//delay 0u
	OW_LOW(ow_pin); 					// Drives DQ low
	delay_480u();						//delay 480us
	OW_HIGH(ow_pin); 					// Releases the bus
	delay_60u();						//delay 60 - 240us
	if (OW_PORT & ow_pin) result = 1;	//return 1 if OW_Pin is high = slave not present
	else result = 0;					//return 0 if OW_Pin is low - pulled down by the slave = slave present
	delay_420u(); 						// Complete the reset sequence recovery
//	OW_High();							//output high impedance
	return result;
}

//----------------------------------------------------------------------------
// Send a 1-Wire write bit. Provide 10us recovery time.
//
void ow_writebit (unsigned int ow_pin, unsigned char tbit) {
	if (tbit) {
		// Write '1' bit
		OW_LOW(ow_pin); 				// Drives DQ lOW_
		delay_1u();						// delay > 1us
		OW_HIGH(ow_pin); 				// Releases the bus
		delay_60u(); 					// Complete the time slot and 10us recovery
	}
	else {
		// Write '0' bit
		OW_LOW(ow_pin); 				// Drives DQ lOW_
		delay_60u();					// delay 60 - 120us
		OW_HIGH(ow_pin); 				// Releases the bus
		delay_1u();					// 10us recovery
	}
}

//-----------------------------------------------------------------------------
// Read a bit from the 1-Wire bus and return it. Provide 10us recovery time.
//
unsigned char ow_readbit(unsigned int ow_pin)
{
        unsigned char result;

        OW_LOW(ow_pin); 				// Drives DQ lOW_
        delay_1u();						// delay > 1us
        OW_HIGH(ow_pin); 				// Releases the bus
        delay_15u();						// needs to be done in 15us.
        if (OW_PORT & ow_pin) result = 1;	//if return 1 if OW_PIN reads high
        else result = 0;							//return 0 if OW_PIN reads lOW_
        delay_30u(); 					// Complete the time slot and 10us recovery
		delay_15u();
//        delay_55u(); delay_55u();
        return result;
}

//-----------------------------------------------------------------------------
// Write 1-Wire data byte
//
void ow_write(unsigned int ow_pin, unsigned char data_t)
{
        unsigned char loop;

        // Loop to write each bit in the byte, LS-bit first
        for (loop = 0; loop < 8; loop++) {
//				OW_STROBE(1<<1);
                ow_writebit(ow_pin, data_t & 0x01);
//				OW_STROBE(1<<1);

                // shift the data byte for the next bit
                data_t >>= 1;
        }
}


//-----------------------------------------------------------------------------
// Read 1-Wire data byte and return it
//
unsigned char ow_read(unsigned int ow_pin)
{
        unsigned char loop; 
        unsigned char result=0;

        for (loop = 0; loop < 8; loop++) {
                // shift the result to get it ready for the next bit
                result >>= 1;

                // if result is one, then set MS bit
                if (ow_readbit(ow_pin))
                        result |= 0x80;
        }
        return result;
}

//-----------------------------------------------------------------------------
// Write a 1-Wire data byte and return the sampled result.
//
unsigned char ow_touchbyte(unsigned int ow_pin, unsigned char data_t)
{
        unsigned char loop;
        unsigned char result=0;

        for (loop = 0; loop < 8; loop++) {
                // shift the result to get it ready for the next bit
                result >>= 1;

                // If sending a '1' then read a bit else write a '0'
                if (data_t & 0x01) {
                        if (ow_readbit(ow_pin))
                                result |= 0x80;
                }
                else
                        ow_writebit(ow_pin, 0);

                // shift the data byte for the next bit
                data_t >>= 1;
        }
        return result;
}

//-----------------------------------------------------------------------------
// Write a block 1-Wire data bytes and return the sampled result in the same
// buffer.
//
void ow_writeblock(unsigned int ow_pin, unsigned char *data_t, unsigned short data_len)
{
        unsigned short loop;

        for (loop = 0; loop < data_len; loop++) {
                data_t[loop] = ow_touchbyte(ow_pin, data_t[loop]);
        }
}

