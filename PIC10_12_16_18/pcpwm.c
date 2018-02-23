#include "pcpwm.h"							//14-bit power control pwm functions for 18f2331/2431/4331/4431/

//hardware configuration
//end hardware configuration

//global defines

//global variables
static uint16_t _pcpwm_pr=0x3fff;				//pwm perid, 14 bit

void pcpwm_init(void) {
	_pcpwm_pr = 0x3fff;						//reset pwm period
	
	//set up the time base
	//set up ptcon0
	PTOPS3=0, PTOPS2=0, PTOPS1=0, PTOPS0=0;	//time base output postscaler = 1:1.
	PTCKPS1=1, PTCKPS0=1;					//clock prescaler. 0b00=1:1, 0b01=4:1, 0b10=16:1, 0b11=64:1
	PTMOD1=0, PTMOD0=0;						//pwm time base mode. 0b00=free running; 0b01=single shot; 0b10=continueous up/down; 0b11=continuous up/down with interrupt
	
	//set up ptcon1
	PTEN = 0;								//time base disabled. 0=disable, 1=enable
	PTDIR = 0;								//0=count up, 1=count down.
	
	//set up pwmcon0
	
	//set pwm enable mode
	//bit 6-4 PWMEN2:PWMEN0: PWM Module Enable bits(1)
	//111 =All odd PWM I/O pins enabled for PWM output(2).
	//110 =PWM1, PWM3 pins enabled for PWM output.
	//101 =All PWM I/O pins enabled for PWM output(2) .
	//100 =PWM0, PWM1, PWM2, PWM3, PWM4 and PWM5 pins enabled for PWM output.
	//011 =PWM0, PWM1, PWM2 and PWM3 I/O pins enabled for PWM output.
	//010 =PWM0 and PWM1 pins enabled for PWM output.
	//001 =PWM1 pin is enabled for PWM output.
	//000 =PWM module disabled. All PWM I/O pins are general purpose I/O.
	PWMEN2=0, PWMEN1=1, PWMEN0=1;			//pwm0/1/2/3 pins enabled
	
	//set pwm output pairs
	//bit 3-0 PMOD3:PMOD0: PWM Output Pair Mode bits
	//For PMOD0:
	//1 = PWM I/O pin pair (PWM0, PWM1) is in the Independent mode.
	//0 = PWM I/O pin pair (PWM0, PWM1) is in the Complementary mode.
	PMOD0 = 0;
	//For PMOD1:
	//1 = PWM I/O pin pair (PWM2, PWM3) is in the Independent mode.
	//0 = PWM I/O pin pair (PWM2, PWM3) is in the Complementary mode.
	PMOD1 = 0;
	//For PMOD2:
	//1 = PWM I/O pin pair (PWM4, PWM5) is in the Independent mode.
	//0 = PWM I/O pin pair (PWM4, PWM5) is in the Complementary mode.
	PMOD2 = 0;
	//For PMOD3(3):
	//1 = PWM I/O pin pair (PWM6, PWM7) is in the Independent mode.
	//0 = PWM I/O pin pair (PWM6, PWM7) is in the Complementary mode. 
	PMOD3 = 0;
	
	//set up pwmcon1
	//bit 7-4 SEVOPS3:SEVOPS0: PWM Special Event Trigger Output Postscale Select bits
	//0000 =1:1 Postscale
	//0001 =1:2 Postscale
	//.
	//.
	//.
	//1111 =1:16 Postscale
	SEVOPS3 = 0, SEVOPS2 = 0, SEVOPS1 = 0, SEVOPS0 = 0;	//postscaler = 1:1
	
	//bit 3 SEVTDIR: Special Event Trigger Time Base Direction bit
	//1 = A special event trigger will occur when the PWM time base is counting downwards.
	//0 = A special event trigger will occur when the PWM time base is counting upwards.
	SEVTDIR = 0;
	//bit 2 Unimplemented: Read as `0'.
	//bit 1 UDIS: PWM Update Disable bit
	//1 = Updates from duty cycle and period buffer registers are disabled.
	//0 = Updates from duty cycle and period buffer registers are enabled.
	UDIS = 0;											//updates enabled
	//bit 0 OSYNC: PWM Output Override Synchronization bit
	//1 = Output overrides via the OVDCON register are synchronized to the PWM time base.
	//0 = Output overrides via the OVDCON register are asynchronous.
	OSYNC = 0;											//output overrides asynchronous
	
	//set up dead time control register
	//bit 7-6 DTPS1:DTPS0: Dead Time Unit A Prescale Select bits
	//11 = Clock source for Dead Time Unit is FOSC/16.
	//10 = Clock source for Dead Time Unit is FOSC/8.
	//01 = Clock source for Dead Time Unit is FOSC/4.
	//00 = Clock source for Dead Time Unit is FOSC/2.
	DTPS1 = 0, DTPS0 = 0;
	//bit 5-0 DT5:DT0: Unsigned 6-bit dead time value bits for Dead Time Unit
	DT5 = 0, DT4 = 0, DT3 = 0, DT2 = 0, DT1 = 0, DT0 = 0;
	
	//set up fault configuration register
	//bit 7 BRFEN: Breakpoint Fault Enable bit
	//1 = Enable fault condition on a breakpoint (i.e., only when HDMIN = 1)
	//0 = Disable fault condition
	//bit 6 FLTBS: Fault B Status bit(1)
	//1 = FLTB is asserted;
	//if FLTBMOD = 0, cleared by the user
	//if FLTBMOD = 1, cleared automatically at beginning of the new period when FLTB is
	//deasserted
	//0 = No Fault
	//bit 5 FLTBMOD: Fault B Mode bit(1)
	//1 = Cycle-by-cycle mode: Pins are inactive for the remainder of the current PWM period, or until
	//FLTB is deasserted. FLTBS is cleared automatically when FLTB is inactive (no fault present).
	//0 = Inactive mode: Pins are deactivated (catastrophic failure) until FLTB is deasserted and
	//FLTBS is cleared by the user only.
	//bit 4 FLTBEN: Fault B Enable bit(1)
	//1 = Enable Fault B
	//0 = Disable Fault B
	//bit 3 FLTCON: Fault Configuration bit
	//1 = FLTA , FLTB or both deactivates all PWM outputs
	//0 = FLTA or FLTB deactivates PWM[5:0]
	//bit 2 FLTAS: Fault A Status bit
	//1 = FLTA is asserted;
	//If FLTAMOD = 0, cleared by the user
	//If FLTAMOD = 1, cleared automatically at beginning of the new period when FLTA is
	//deasserted.
	//0 = No Fault
	//bit 1 FLTAMOD: Fault A Mode bit
	//1 = Cycle-by-cycle mode: Pins are inactive for the remainder of the current PWM period, or until
	//FLTA is deasserted. FLTAS is cleared automatically.
	//0 = Inactive mode: Pins are deactivated (catastrophic failure) until FLTA is deasserted and
	//FLTAS is cleared by the user only.
	//bit 0 FLTAEN: Fault A Enable bit
	//1 = Enable Fault A
	//0 = Disable Fault A
	FLTCONFIG = 0x00;								//default value
	
	//clear interrupt
	PTIF = 0;										//clear the flag
	PTIE = 0;										//no interrupt
	
	//reset the timer
	PTMRH = 0;
	PTMRL = 0;
	
	//turn on the time base
	PTEN = 1;
	
}

//set pwm period - 14bit period recast to 12bits
void pcpwm_setpr(uint16_t prescaler, uint16_t period) {
	//set prescaler
	PTCKPS1=(prescaler & 0x02)?1:0;
	PTCKPS0=(prescaler & 0x01)?1:0;					//clock prescaler. 0b00=1:1, 0b01=4:1, 0b10=16:1, 0b11=64:1

	//set pwm period buffer
	_pcpwm_pr = period & 0x3fff;						//14bit pwm
	PTPERH = (_pcpwm_pr - 1) >> 10;
	PTPERL = (_pcpwm_pr - 1) >> 2;
	
}

//get pwm period - 14bit period
//uint16_t pcpwm_getpr(void) {
//	return _pcpwm_pr;
//}


//set pwm period for ch 0 - 14bit dc
void pcpwm_setdc0(uint16_t dc) {
	//For PMOD0:
	//1 = PWM I/O pin pair (PWM0, PWM1) is in the Independent mode.
	//0 = PWM I/O pin pair (PWM0, PWM1) is in the Complementary mode.
	PMOD0 = 0;

	PDC0H = (dc - 1) >> 8;
	PDC0L = (dc - 1);
}

//set pwm period for ch 1 - 14bit dc
void pcpwm_setdc1(uint16_t dc) {
	//For PMOD1:
	//1 = PWM I/O pin pair (PWM2, PWM3) is in the Independent mode.
	//0 = PWM I/O pin pair (PWM2, PWM3) is in the Complementary mode.
	PMOD1 = 0;

	PDC1H = (dc - 1) >> 8;
	PDC1L = (dc - 1);
}

//set pwm period for ch 2 - 14bit dc
void pcpwm_setdc2(uint16_t dc) {
	//For PMOD2:
	//1 = PWM I/O pin pair (PWM4, PWM5) is in the Independent mode.
	//0 = PWM I/O pin pair (PWM4, PWM5) is in the Complementary mode.
	PMOD2 = 0;
	
	PDC2H = (dc - 1) >> 8;
	PDC2L = (dc - 1);
}

//set pwm period for ch 3 - 14bit dc
void pcpwm_setdc3(uint16_t dc) {
	//For PMOD3(3):
	//1 = PWM I/O pin pair (PWM6, PWM7) is in the Independent mode.
	//0 = PWM I/O pin pair (PWM6, PWM7) is in the Complementary mode. 
	PMOD3 = 0;

	PDC3H = (dc - 1) >> 8;
	PDC3L = (dc - 1);
}
