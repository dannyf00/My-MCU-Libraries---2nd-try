#include "pwmtb0.h"							//we use tmrb0

//hardware configuration
//end hardware configuration

//global defines
//for easy portability
#define TBx					TIMERB0			//use TIMERB0
/*
#define TAxCTL				TB0CTL			//timera control
#define TAxR				TB0R			//timer / counter
#define TAxIV				TB0IV			//interrupt flag
#define TAxEX0				TB0EX0			//expansion register

#define TAxCCTL0			TB0CCTL0		//timer0 compare control
#define TAxCCTL1			TB0CCTL1		//timer1 cmpare control
#define TAxCCTL2			TB0CCTL2		//timer2 compare control
#define TAxCCTL3			TB0CCTL3		//timer0 compare control
#define TAxCCTL4			TB0CCTL4		//timer1 cmpare control
#define TAxCCTL5			TB0CCTL5		//timer2 compare control
#define TAxCCTL6			TB0CCTL6		//timer0 compare control
#define TAxCCR0				TB0CCR0			//timer0 compare register
#define TAxCCR1				TB0CCR1			//timer1 compare register
#define TAxCCR2				TB0CCR2			//timer2 compare register
#define TAxCCR3				TB0CCR3			//timer0 compare register
#define TAxCCR4				TB0CCR4			//timer1 compare register
#define TAxCCR5				TB0CCR5			//timer2 compare register
#define TAxCCR6				TB0CCR6			//timer0 compare register
*/
//global variables

//initialize timer_a, ccr0
//continous mode
//up (default) or up/down mode
void pwmtb0_init(uint16_t ps, uint16_t pr) {
	//clear the timer control register
	TBx->CTL |= TBCLR;							//TxCTL_bit.TACLR;						//set to reset timer a

	//stop timer
	TBx->CTL &=~MC_0;							//TxCTL_bit.TAMC = 0x00;				//timer mode - 0x00: halted, 0x01: up mode, 0x02: continuous mode (to 0xffff), 0x03: up/down
	//TxCTL |= TASSEL_2;						//TxCTL_bit.TASSEL = 0x02;				//timer source - 0x00: TACLK, 0x01: ACLK, 0x02: SMCLK, 0x03: INCLK
	//TxCTL |= (ps & ID_3);						//TxCTL_bit.TAID = ps & 0x03;			//input divider - 0x00: /1, 0x01: /2, 0x02: /4, 0x03: /8
	//TxCTL &=~TAIE;							//TxCTL_bit.TAIE = 0;					//timer a interrupt enable: 0: interrupt disabled; 1: interrupt enabled;
	//TxCTL &=~TAIFG;							//TxCTL_bit.TAIFG = 0;					//interrupt flag: 0= no interrupt pending; 1=interrupt pending
	//TxCTL |= OUTMOD0;							//set output mode to zero
	TBx->CCR0 = pr - 1;							//set the period
#if defined(TB0EX0_)
	TBx->EX0 = (ps & TMRB_EX8x);	//set expansion divider
#endif
	TBx->CTL = 	TASSEL_2 |						//0=TACLK, 1=ACLK, 2=SMCLK, and 3=INCLK
				(ps & TMRB_PS8x) |				//prescaler
				MC_1 |							//0=stop, 1=up to ccr0, 2=continous mode, 3=up and down
				0x00;							//TCIE disabled
	//timer is running now
	
#if defined(PWM_TB0CH1)
	//TB0CH1 output to be activated
	//set up TBx->CCTLx register
	TBx->CCTL1 = 	CM_0 |					//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_7 |					//3:reset on match/set on roll-over
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
	TBx->CCR1 = 0;							//duty cycle starts at 0
	PWM_TB0CH1();							//activate the pin
#endif

#if defined(PWM_TB0CH2)
	//TB0CH2 output to be activated
	//set up TBx->CCTLx register
	TBx->CCTL2 = 	CM_0 |					//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_7 |					//3:reset on match/set on roll-over
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
	TBx->CCR2 = 0;							//duty cycle starts at 0
	PWM_TB0CH2();							//activate the pin
#endif

#if defined(PWM_TB0CH3)
	//TB0CH3 output to be activated
	//set up TBx->CCTLx register
	TBx->CCTL3 = 	CM_0 |					//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_7 |					//3:reset on match/set on roll-over
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
	TBx->CCR3 = 0;							//duty cycle starts at 0
	PWM_TB0CH3();							//activate the pin
#endif

#if defined(PWM_TB0CH4)
	//TB0CH4 output to be activated
	//set up TBx->CCTLx register
	TBx->CCTL4 = 	CM_0 |					//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_7 |					//3:reset on match/set on roll-over
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
	TBx->CCR4 = 0;							//duty cycle starts at 0
	PWM_TB0CH4();							//activate the pin
#endif

#if defined(PWM_TB0CH5)
	//TB0CH5 output to be activated
	//set up TBx->CCTLx register
	TBx->CCTL5 = 	CM_0 |					//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_7 |					//3:reset on match/set on roll-over
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
	TBx->CCR5 = 0;							//duty cycle starts at 0
	PWM_TB0CH5();							//activate the pin
#endif

#if defined(PWM_TB0CH5)
	//TB0CH5 output to be activated
	//set up TBx->CCTLx register
	TBx->CCTL5 = 	CM_0 |					//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_7 |					//3:reset on match/set on roll-over
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
	TBx->CCR5 = 0;							//duty cycle starts at 0
	PWM_TB0CH5();							//activate the pin
#endif

}
