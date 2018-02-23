//usring output compare channels 1..5 as timers
//timer3 as the time base

#include "tmr3oc.h"

//hardware configuration
//end hardware configuration

//global defines
//for compatibility reasons and easy porting
#define _TxON				T3CONbits.TON		//tmr on - T3's ON bit is on T2CON
#define _TxCS				T3CONbits.TCS		//tmr source
#define _TxGE				T3CONbits.TGATE		//timer gate enable
#define _TxCKPS				T3CONbits.TCKPS		//tmr prescaler
#define _Tx32				T2CONbits.T32		//32-bit timer if set - T3's 32-bit/16-bit bit on T2CON
#define _TxIE				IEC0bits.T3IE		//tmr interrupt enable
#define _TxIF				IFS0bits.T3IF		//tmr1 overflow flag
#define _TxIP				IPC3bits.T3IP		//tmr interrupt priority
#define _TxIS				IPC3bits.T3IS		//tmr interrupt sub-priority
#define _PRx				PR3					//period
#define _TMRx				TMR3				//counter
#define _TxIPL				IPL2				//default isr priority levels
#define TxIP_DEFAULT		2					//default interrupt priority - lowest
#define TxIS_DEFAULT		0					//default interrupt subpriority
#define OCxIP_DEFAULT		2					//default interrupt priority - lowest
#define OCxIS_DEFAULT		0					//default interrupt subpriority
#define _TxMD				PMD4bits.T2MD		//'0'-enable power to peripheral
#define _OC1IF				IFS0bits.OC1IF		//interrupt flag
#define _OC2IF				IFS0bits.OC2IF		//interrupt flag
#define _OC3IF				IFS0bits.OC3IF		//interrupt flag
#define _OC4IF				IFS0bits.OC4IF		//interrupt flag
#define _OC5IF				IFS0bits.OC5IF		//interrupt flag
#define _OC1IE				IEC0bits.OC1IE		//interrupt enable bits
#define _OC2IE				IEC0bits.OC2IE		//interrupt enable bits
#define _OC3IE				IEC0bits.OC3IE		//interrupt enable bits
#define _OC4IE				IEC0bits.OC4IE		//interrupt enable bits
#define _OC5IE				IEC0bits.OC5IE		//interrupt enable bits
#define _OC1IP				IPC1bits.OC1IP		//output compare isr priority
#define _OC2IP				IPC2bits.OC2IP		//output compare isr priority
#define _OC3IP				IPC3bits.OC3IP		//output compare isr priority
#define _OC4IP				IPC4bits.OC4IP		//output compare isr priority
#define _OC5IP				IPC5bits.OC5IP		//output compare isr priority
#define _OC1IS				IPC1bits.OC1IS		//output compare isr sub-priority
#define _OC2IS				IPC2bits.OC2IS		//output compare isr sub-priority
#define _OC3IS				IPC3bits.OC3IS		//output compare isr sub-priority
#define _OC4IS				IPC4bits.OC4IS		//output compare isr sub-priority
#define _OC5IS				IPC5bits.OC5IS		//output compare isr sub-priority


//empty handler
static void empty_handler(void) {
	//default tmr handler
}

//global variables
static void (* _isrptr_tov)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* _isrptr_oc1)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* _isrptr_oc2)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* _isrptr_oc3)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* _isrptr_oc4)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* _isrptr_oc5)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static uint16_t _inc_oc1=0xffff;				//increments, 16-bit
static uint16_t _inc_oc2=0xffff;				//increments, 16-bit
static uint16_t _inc_oc3=0xffff;				//increments, 16-bit
static uint16_t _inc_oc4=0xffff;				//increments, 16-bit
static uint16_t _inc_oc5=0xffff;				//increments, 16-bit

//tmr3 isr overflow
void __ISR(_TIMER_3_VECTOR, _TxIPL) _T3Interrupt(void) {
//void __ISR(_TIMER_1_VECTOR, IPL2SOFT) Timer1Handler(void) {
	_TxIF=0;							//clear tmr1 interrupt flag
	_isrptr_tov();						//execute user tmr1 isr
}

//Output Compare 1 ISR:
void __ISR(_OUTPUT_COMPARE_1_VECTOR/*, ipl7*/) _OC1IntHandler (void) {
	//IFS0CLR = 0x0040; // Clear the OC1 interrupt flag
	_OC1IF = 0;
	OC1R += _inc_oc1;					//increment to the next match point
	if (OC1CONbits.OC32==0) OC1R = OC1R & 0xffff;	//keep it 16 bits
	_isrptr_oc1();						//execute user handler
}

//Output Compare 2 ISR:
void __ISR(_OUTPUT_COMPARE_2_VECTOR/*, ipl7*/) _OC2IntHandler (void) {
	//IFS0CLR = 0x0040; // Clear the OC1 interrupt flag
	_OC2IF = 0;
	OC2R += _inc_oc2;					//increment to the next match point
	if (OC2CONbits.OC32==0) OC2R = OC2R & 0xffff;	//keep it 16 bits
	_isrptr_oc2();						//execute user handler
}

//Output Compare 3 ISR:
void __ISR(_OUTPUT_COMPARE_3_VECTOR/*, ipl7*/) _OC3IntHandler (void) {
	//IFS0CLR = 0x0040; // Clear the OC1 interrupt flag
	_OC3IF = 0;
	OC3R += _inc_oc3;					//increment to the next match point
	if (OC3CONbits.OC32==0) OC3R = OC3R & 0xffff;	//keep it 16 bits
	_isrptr_oc3();						//execute user handler
}

//Output Compare 4 ISR:
void __ISR(_OUTPUT_COMPARE_4_VECTOR/*, ipl7*/) _OC4IntHandler (void) {
	//IFS0CLR = 0x0040; // Clear the OC1 interrupt flag
	_OC4IF = 0;
	OC4R += _inc_oc4;					//increment to the next match point
	if (OC4CONbits.OC32==0) OC4R = OC4R & 0xffff;	//keep it 16 bits
	_isrptr_oc4();						//execute user handler
}

//Output Compare 5 ISR:
void __ISR(_OUTPUT_COMPARE_5_VECTOR/*, ipl7*/) _OC5IntHandler (void) {
	//IFS0CLR = 0x0040; // Clear the OC1 interrupt flag
	_OC5IF = 0;
	OC5R += _inc_oc5;					//increment to the next match point
	if (OC5CONbits.OC32==0) OC5R = OC5R & 0xffff;	//keep it 16 bits
	_isrptr_oc5();						//execute user handler
}


//initialize the timer2 (16bit)
void tmr3_init(uint8_t ps) {
	//initialize the variables
	_isrptr_tov = _isrptr_oc1 = _isrptr_oc2 = _isrptr_oc3 = _isrptr_oc4 = _isrptr_oc5 = empty_handler;	//point to default handler
	_inc_oc1 = _inc_oc2 = _inc_oc3 = _inc_oc4 = _inc_oc5 = 0xffff;

	//enable power to the peripheral
	_TxMD = 0;

	//configure the timer
	_TxON = 0;							//turn off rtc1
	_TxCS = 0;							//use internal clock = Fosc
	_TxCKPS=ps & TMR3_PSMASK;			//set prescaler to 1:1
	_Tx32 = 0;							//16-bit mode
	_TxGE = 0;							//rtc1 gate disabled
	_TxIF = _OC1IF = _OC2IF = _OC3IF = _OC4IF = _OC5IF = 0;							//reset the flag
	_TxIE = _OC1IE = _OC2IE = _OC3IE = _OC4IE = _OC5IE = 0;							//rtc1 interrupt off
	_TMRx = 0;							//reset the timer/counter
	_PRx = 0xffff;						//period register
	_TxON = 1;							//turn on rtc1

	//T2CONbits.TON = 1;					//to get the OC working on TMR3
}

//activate the isr handler
void tmr3_act(void (*isr_ptr)(void)) {
	_isrptr_tov=isr_ptr;			//activate the isr handler
	_TxIP = TxIP_DEFAULT;
	_TxIS = TxIS_DEFAULT;
	_TxIF = 0;							//reset the flag
	_TxIE = 1;							//rtc1 interrupt on
}

//configure output compare 1
void tmr31_setpr(uint16_t pr) {
	_inc_oc1 = pr - 1;					//update increment

	//disable the output compare module
	PMD3bits.OC1MD = 0;					//enable power to peripheral
	OC1CONbits.ON = 0;					//stop the output compare module
	OC1CONbits.OCM = 0;
	OC1CONbits.OC32 = _Tx32;			//'0'->16 modes: follow _Tx32
	OC1CONbits.OCTSEL = 1;				//timer base select: '0'->TIMER2, '1'->TIMER3
	OC1CONbits.OCM = 3;					//output compare mode: 3 is the only one that works
	OC1R = _TMRx + _inc_oc1;					//TMR3 + _inc_oc1;				//pr - 1;
	//OC1RS = 0xffff;

	_OC1IF = 0;							//clear the flag
	_OC1IE = 0;							//disable the interrupt

	OC1CONbits.ON = 1;					//turn on the  module
}

//install user handler
void tmr31_act(void (*isr_ptr)(void)) {
	_isrptr_oc1 = isr_ptr;				//install the user handler
	_OC1IF = 0;							//clear the flag
	_OC1IP = OCxIP_DEFAULT;
	_OC1IS = OCxIS_DEFAULT;
	_OC1IE = 1;							//enable the interrupt

}


//configure output compare 2
void tmr32_setpr(uint16_t pr) {
	_inc_oc2 = pr - 1;					//update increment

	//disable the output compare module
	PMD3bits.OC2MD = 0;					//enable power to peripheral
	OC2CONbits.ON = 0;					//stop the output compare module
	OC2CONbits.OCM = 0;
	OC2CONbits.OC32 = _Tx32;			//'0'->16 modes: follow _Tx32
	OC2CONbits.OCTSEL = 1;				//timer base select: '0'->TIMER2, '1'->TIMER3
	OC2CONbits.OCM = 3;					//output compare mode: 3 is the only one that works
	OC2R = _TMRx + _inc_oc2;					//TMR3 + _inc_oc1;				//pr - 1;
	//OC2RS = 0xffff;

	_OC2IF = 0;							//clear the flag
	_OC2IE = 0;							//disable the interrupt

	OC2CONbits.ON = 1;					//turn on the  module
}

//install user handler
void tmr32_act(void (*isr_ptr)(void)) {
	_isrptr_oc2 = isr_ptr;				//install the user handler
	_OC2IF = 0;							//clear the flag
	_OC2IP = OCxIP_DEFAULT;
	_OC2IS = OCxIS_DEFAULT;
	_OC2IE = 1;							//enable the interrupt

}


//configure output compare 3
void tmr33_setpr(uint16_t pr) {
	_inc_oc3 = pr - 1;					//update increment

	//disable the output compare module
	PMD3bits.OC3MD = 0;					//enable power to peripheral
	OC3CONbits.ON = 0;					//stop the output compare module
	OC3CONbits.OCM = 0;
	OC3CONbits.OC32 = _Tx32;			//'0'->16 modes: follow _Tx32
	OC3CONbits.OCTSEL = 1;				//timer base select: '0'->TIMER2, '1'->TIMER3
	OC3CONbits.OCM = 3;					//output compare mode: 3 is the only one that works
	OC3R = _TMRx + _inc_oc3;					//TMR3 + _inc_oc1;				//pr - 1;
	//OC3RS = 0xffff;

	_OC3IF = 0;							//clear the flag
	_OC3IE = 0;							//disable the interrupt

	OC3CONbits.ON = 1;					//turn on the  module
}

//install user handler
void tmr33_act(void (*isr_ptr)(void)) {
	_isrptr_oc3 = isr_ptr;				//install the user handler
	_OC3IF = 0;							//clear the flag
	_OC3IP = OCxIP_DEFAULT;
	_OC3IS = OCxIS_DEFAULT;
	_OC3IE = 1;							//enable the interrupt

}


//configure output compare 4
void tmr34_setpr(uint16_t pr) {
	_inc_oc4 = pr - 1;					//update increment

	//disable the output compare module
	PMD3bits.OC4MD = 0;					//enable power to peripheral
	OC4CONbits.ON = 0;					//stop the output compare module
	OC4CONbits.OCM = 0;
	OC4CONbits.OC32 = _Tx32;			//'0'->16 modes: follow _Tx32
	OC4CONbits.OCTSEL = 1;				//timer base select: '0'->TIMER2, '1'->TIMER3
	OC4CONbits.OCM = 3;					//output compare mode: 3 is the only one that works
	OC4R = _TMRx + _inc_oc4;					//TMR3 + _inc_oc1;				//pr - 1;
	//OC4RS = 0xffff;

	_OC4IF = 0;							//clear the flag
	_OC4IE = 0;							//disable the interrupt

	OC4CONbits.ON = 1;					//turn on the  module
}

//install user handler
void tmr34_act(void (*isr_ptr)(void)) {
	_isrptr_oc4 = isr_ptr;				//install the user handler
	_OC4IF = 0;							//clear the flag
	_OC4IP = OCxIP_DEFAULT;
	_OC4IS = OCxIS_DEFAULT;
	_OC4IE = 1;							//enable the interrupt

}


//configure output compare 5
void tmr35_setpr(uint16_t pr) {
	_inc_oc5 = pr - 1;					//update increment

	//disable the output compare module
	PMD3bits.OC5MD = 0;					//enable power to peripheral
	OC5CONbits.ON = 0;					//stop the output compare module
	OC5CONbits.OCM = 0;
	OC5CONbits.OC32 = _Tx32;			//'0'->16 modes: follow _Tx32
	OC5CONbits.OCTSEL = 1;				//timer base select: '0'->TIMER2, '1'->TIMER3
	OC5CONbits.OCM = 3;					//output compare mode: 3 is the only one that works
	OC5R = _TMRx + _inc_oc5;					//TMR3 + _inc_oc1;				//pr - 1;
	//OC5RS = 0xffff;

	_OC5IF = 0;							//clear the flag
	_OC5IE = 0;							//disable the interrupt

	OC5CONbits.ON = 1;					//turn on the  module
}

//install user handler
void tmr35_act(void (*isr_ptr)(void)) {
	_isrptr_oc5 = isr_ptr;				//install the user handler
	_OC5IF = 0;							//clear the flag
	_OC5IP = OCxIP_DEFAULT;
	_OC5IS = OCxIS_DEFAULT;
	_OC5IE = 1;							//enable the interrupt

}


