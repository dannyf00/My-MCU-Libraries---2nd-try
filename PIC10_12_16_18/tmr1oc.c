#include "tmr1oc.h"

//hardware configuration
//end hardware configuration

//global defines
//#define TMR1_PS				3				//0->1:1, 1=2:1, 2=4:1, 3=8:1

//XC8 stupidity
//CCPRx register addresses. Confirmed only for PIC16(L)F193x chips
extern volatile unsigned short           CCPR1              @ 0x291;
extern volatile unsigned short           CCPR2              @ 0x298;
extern volatile unsigned short           CCPR3              @ 0x311;
extern volatile unsigned short           CCPR4              @ 0x318;
extern volatile unsigned short           CCPR5              @ 0x31c;


//global variables

//empty handler
static void empty_handler(void) {
	//do nothing here
}

//user isr handlers
void (*tmr1oc1_isrptr)(void) = empty_handler;
void (*tmr1oc2_isrptr)(void) = empty_handler;
void (*tmr1oc3_isrptr)(void) = empty_handler;
void (*tmr1oc4_isrptr)(void) = empty_handler;
void (*tmr1oc5_isrptr)(void) = empty_handler;

//channel pointers
uint16_t tmr1oc1_pr = 0;
uint16_t tmr1oc2_pr = 0;
uint16_t tmr1oc3_pr = 0;
uint16_t tmr1oc4_pr = 0;
uint16_t tmr1oc5_pr = 0;

//global interrupt should be defined like this:
/*
void interrupt isr(void) {
	if (CCP1IF) ccp1_isr();							//run the user isr
	if (CCP2IF) ccp2_isr();							//run the user isr
	if (CCP3IF) ccp3_isr();							//run the user isr
	if (CCP4IF) ccp4_isr();							//run the user isr
	if (CCP5IF) ccp5_isr();							//run the user isr
}
*/

//ccp isr
void ccp1_isr(void) {
	CCP1IF = 0;						//clear the flag
	CCPR1 += tmr1oc1_pr;				//advance the match point
	tmr1oc1_isrptr();				//execute user isr
}

void ccp2_isr(void) {
	CCP2IF = 0;						//clear the flag
	CCPR2 += tmr1oc2_pr;				//advance the match point
	tmr1oc2_isrptr();				//execute user isr
}

//ccp isr
void ccp3_isr(void) {
	CCP3IF = 0;						//clear the flag
	CCPR3 += tmr1oc3_pr;				//advance the match point
	tmr1oc3_isrptr();				//execute user isr
}

void ccp4_isr(void) {
	CCP4IF = 0;						//clear the flag
	CCPR4 += tmr1oc4_pr;				//advance the match point
	tmr1oc4_isrptr();				//execute user isr
}

//ccp isr
void ccp5_isr(void) {
	CCP5IF = 0;						//clear the flag
	CCPR5 += tmr1oc5_pr;				//advance the match point
	tmr1oc5_isrptr();				//execute user isr
}

//initialize tmr1oc modules
void tmr1oc_init(void) {
	//reset the handlers
	tmr1oc1_isrptr = tmr1oc2_isrptr=tmr1oc3_isrptr=tmr1oc4_isrptr=tmr1oc5_isrptr = empty_handler;
	
	//reset timer1 as 16-bit free-running prescaler 1:1
	TMR1CS1 = 0, TMR1CS0 = 1;			//0b01->count system clock
	TMR1GE = 0;
	T1CON = (T1CON &~(0x03 << 4)) | ((TMR1_PS & 0x03) << 4);	//set the prescaler
	nT1SYNC = 1;						//tmr1 asynchronuous
	TMR1 = 0;							//reset the counter
	
	//clear the flags and disable interrupts
	CCP1IF = CCP2IF = CCP3IF = CCP4IF = CCP5IF = 0;	
	CCP1IE = CCP2IE = CCP3IE = CCP4IE = CCP5IE = 0;	

	TMR1ON = 1;							//turn on tmr1
}

//set oc1/ccp1
void tmr1oc_setpr1(uint16_t pr) {
	CCP1CON = 	(0<<6) |				//do not care for output compare mode
				(0<<4) |				//do not care for output compare mode
				(0b1010) |				//0b1010->generate software interrupts
				0x00;
	tmr1oc1_pr = pr - 1;				//save period
	CCPR1 = TMR1 + tmr1oc1_pr;			//set the next match point
	//CCP1IF = 0;							//clera the flag
	//CCP1IE = 0;							//'0'->disable the interrupt
}

//install user handler
void tmr1oc_act1(void (*isrptr)(void)) {
	tmr1oc1_isrptr = isrptr;			//install user handler
	CCP1IF = 0;							//clear the flag
	CCP1IE = 1;							//enable the interrupt
	PEIE = 1;							//'1'->enable interrupt
}
		
//set oc2/ccp2
void tmr1oc_setpr2(uint16_t pr) {
	CCP2CON = 	(0<<6) |				//do not care for output compare mode
				(0<<4) |				//do not care for output compare mode
				(0b1010) |				//0b1010->generate software interrupts
				0x00;
	tmr1oc2_pr = pr - 1;				//save period
	CCPR2 = TMR1 + tmr1oc2_pr;			//set the next match point
	//CCP2IF = 0;							//clera the flag
	//CCP2IE = 0;							//'0'->disable the interrupt
}

//install user handler
void tmr1oc_act2(void (*isrptr)(void)) {
	tmr1oc2_isrptr = isrptr;			//install user handler
	CCP2IF = 0;							//clear the flag
	CCP2IE = 1;							//enable the interrupt
	PEIE = 1;							//'1'->enable interrupt
}
//set oc3/ccp3
void tmr1oc_setpr3(uint16_t pr) {
	CCP3CON = 	(0<<6) |				//do not care for output compare mode
				(0<<4) |				//do not care for output compare mode
				(0b1010) |				//0b1010->generate software interrupts
				0x00;
	tmr1oc3_pr = pr - 1;				//save period
	CCPR3 = TMR1 + tmr1oc3_pr;			//set the next match point
	//CCP3IF = 0;							//clera the flag
	//CCP3IE = 0;							//'0'->disable the interrupt
}

//install user handler
void tmr1oc_act3(void (*isrptr)(void)) {
	tmr1oc3_isrptr = isrptr;			//install user handler
	CCP3IF = 0;							//clear the flag
	CCP3IE = 1;							//enable the interrupt
	PEIE = 1;							//'1'->enable interrupt
}
//set oc2/ccp4
void tmr1oc_setpr4(uint16_t pr) {
	CCP4CON = 	(0<<6) |				//do not care for output compare mode
				(0<<4) |				//do not care for output compare mode
				(0b1010) |				//0b1010->generate software interrupts
				0x00;
	tmr1oc4_pr = pr - 1;				//save period
	CCPR4 = TMR1 + tmr1oc4_pr;			//set the next match point
	//CCP4IF = 0;							//clera the flag
	//CCP4IE = 0;							//'0'->disable the interrupt
}

//install user handler
void tmr1oc_act4(void (*isrptr)(void)) {
	tmr1oc4_isrptr = isrptr;			//install user handler
	CCP4IF = 0;							//clear the flag
	CCP4IE = 1;							//enable the interrupt
	PEIE = 1;							//'1'->enable interrupt
}
//set oc5/ccp5
void tmr1oc_setpr5(uint16_t pr) {
	CCP5CON = 	(0<<6) |				//do not care for output compare mode
				(0<<4) |				//do not care for output compare mode
				(0b1010) |				//0b1010->generate software interrupts
				0x00;
	tmr1oc5_pr = pr - 1;				//save period
	CCPR5 = TMR1 + tmr1oc5_pr;			//set the next match point
	//CCP5IF = 0;							//clera the flag
	//CCP5IE = 0;							//'0'->disable the interrupt
}

//install user handler
void tmr1oc_act5(void (*isrptr)(void)) {
	tmr1oc5_isrptr = isrptr;			//install user handler
	CCP5IF = 0;							//clear the flag
	CCP5IE = 1;							//enable the interrupt
	PEIE = 1;							//'1'->enable interrupt
}
