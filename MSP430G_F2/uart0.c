#include "uart0.h"								//uart on eUSCI_A0..3 for MSP432

//EUSCI_A
//#define eUSCIx				UART0
//for compatability
#define UCAxCTL0				UCA0CTL0
#define UCAxCTL1				UCA0CTL1
#define UCAxBR0					UCA0BR0
#define UCAxBR1					UCA0BR1
#define UCAxMCTL				UCA0MCTL
#define UCAxIE					UC0IE			//IE2
#define UCAxIFG					UC0IFG			//IFG2
#define UCAxTXBUF				UCA0TXBUF
#define UCAxRXBUF				UCA0RXBUF
#define UCAxSTAT				UCA0STAT
#define UCAxTXIFG				UCA0TXIFG
#define UCAxRXIFG				UCA0RXIFG
#define UCAxTXIE				UCA0TXIE
#define UCAxRXIE				UCA0RXIE

//reset uart0/eusci_a0
void uart0_init(uint32_t bps) {
	uint16_t brx;								//used for baud rate calculation, corresponds to BRx, BRFx, BRSx in the datasheet
	uint8_t brfx, brsx;
	uint8_t OS16;
	uint32_t intN;
	uint16_t fracN;								//N - INT(N), x 10000

	//configure the pins
#if defined(UART0_TX)
	UART0_TX();
#endif
	
#if defined(UART0_RX)
	UART0_RX();
#endif
	
	// Configure USCI_A0 for UART mode
	UCAxCTL1 = (1<<0);							//EUSCI_A_CTLW0_SWRST;			//UCAxCTLW0 = UCSWRST;                      // Put eUSCI in reset
	//UCAxCTLW0|= EUSCI_A_CTLW0_SSEL__SMCLK;	//UCAxCTLW0 |= UCSSEL__SMCLK;               // CLK = SMCLK
	UCAxCTL0 = 		(0<< 7) |					//0->parity disabled, 1->parity enabled
					(0<< 6) |					//0->odd parity, 1->even parity
					(0<< 5) |					//0->lsb first, 1->msb first
					(0<< 4) |					//0->8-bit data, 1->7-bit data
					(0<< 3) |					//0->1 stop bit, 1->two stop bits
					(0<< 1) |					//0->uart mode, 1->idle line multiprocessor mode, 1->address-bit multiprocessor mode, 3->uart mode with automatic baud rate detection
					(0<< 0) |					//0->asynchronous mode, 1->synchronous mode
					0x00;
	UCAxCTL1 = 		(2<< 6) |					//0->uclk, 1->aclk, 2->smclk, 3->smclk
					(0<< 5) |					//0->errornous characters rejected and ucrxifg is not set, 1->errorneous chararcters received ans set ucrxifg
					(0<< 4) |					//0->received break character do not set ucrxifg, 1->received break characters set ucrxifg
					(0<< 3) |					//0->not dormant. all received characters set ucrxifg, 1->dormant
					(0<< 2) |					//0->next frame transmitted is data, 1->next frame transmitted is an address
					(0<< 1) |					//0->next frame transmitted is not break; 1->next frame transmited is break;
					(1<< 0) |					//0->reset disabled. usci reset released for operation. 1->hold usci in reset
					0x00;
	// Baud Rate calculation
	// 8000000/(16*9600) = 52.083
	// Fractional portion = 0.083
	// User's Guide Table 21-4: UCBRSx = 0x04
	// UCBRFx = int ( (52.083-52)*16) = 1

	//see section 22.3.10 in the datasheet
	//step 1
	intN = F_UART / bps;
	if (intN > 16) {
		//step 3 - high frequency mode, 16 oversampling
		OS16 = 1; brx = intN / 16; brfx = intN - (brx * 16); brsx = 0;
	} else {
		//step 2 - low frequency mode
		OS16 = 0; brx = intN; brfx = 0; brsx = F_UART * 8 / bps - (brx * 8);		//brfx ignored
	}
	//step 4 - optional
	//fracN = (F_UART - intN * bps) * 10000ul / bps;
	//brsx = 0;									//default to 0
	//brx=104; brsx=1; brfx=0; OS16=0;
#if 0
	//look up brsx based on fracN
	         if (fracN < ((   0 +  529) / 2)) brsx = 0x00;
	 	else if (fracN < (( 529 +  715) / 2)) brsx = 0x01;
		else if (fracN < (( 715 +  835) / 2)) brsx = 0x02;
		else if (fracN < (( 835 + 1001) / 2)) brsx = 0x04;
		else if (fracN < ((1001 + 1252) / 2)) brsx = 0x08;
		else if (fracN < ((1252 + 1430) / 2)) brsx = 0x10;
		else if (fracN < ((1430 + 1670) / 2)) brsx = 0x20;
		else if (fracN < ((1670 + 2147) / 2)) brsx = 0x11;
		else if (fracN < ((2147 + 2224) / 2)) brsx = 0x21;
		else if (fracN < ((2224 + 2503) / 2)) brsx = 0x22;
		else if (fracN < ((2503 + 3000) / 2)) brsx = 0x44;
		else if (fracN < ((3000 + 3335) / 2)) brsx = 0x25;
		else if (fracN < ((3335 + 3575) / 2)) brsx = 0x49;
		else if (fracN < ((3575 + 3753) / 2)) brsx = 0x4a;
		else if (fracN < ((3753 + 4003) / 2)) brsx = 0x52;
		else if (fracN < ((4003 + 4286) / 2)) brsx = 0x92;
		else if (fracN < ((4286 + 4378) / 2)) brsx = 0x53;
		else if (fracN < ((4378 + 5002) / 2)) brsx = 0x55;
		else if (fracN < ((5002 + 5715) / 2)) brsx = 0xaa;
		else if (fracN < ((5715 + 6003) / 2)) brsx = 0x6b;
		else if (fracN < ((6003 + 6254) / 2)) brsx = 0xad;
		else if (fracN < ((6254 + 6432) / 2)) brsx = 0xb5;
		else if (fracN < ((6432 + 6667) / 2)) brsx = 0xb6;
		else if (fracN < ((6667 + 7001) / 2)) brsx = 0xd6;
		else if (fracN < ((7001 + 7147) / 2)) brsx = 0xb7;
		else if (fracN < ((7503 + 7861) / 2)) brsx = 0xbb;
		else if (fracN < ((7861 + 8004) / 2)) brsx = 0xdd;
		else if (fracN < ((8004 + 8333) / 2)) brsx = 0xed;
		else if (fracN < ((8333 + 8464) / 2)) brsx = 0xee;
		else if (fracN < ((8464 + 8572) / 2)) brsx = 0xbf;
		else if (fracN < ((8572 + 8751) / 2)) brsx = 0xdf;
		else if (fracN < ((8751 + 9004) / 2)) brsx = 0xef;
		else if (fracN < ((9004 + 9170) / 2)) brsx = 0xfb;
		else if (fracN < ((9170 + 9288) / 2)) brsx = 0xfd;
		else                                  brsx = 0xfe;
#endif

	UCAxBR0=brx;								//LSB
	UCAxBR1=brx>>8;								//MSB
	//UCAxBR0 = 52;                             // 8000000/16/9600
	//UCAxBR1 = 0x00;
	//UCAxMCTLW |= UCOS16 | UCBRF_1;
	UCAxMCTL = 		((brfx & 0x0f) << 4) |		//ucbrsx: 2nd modulation stage select
					((brsx &  0x07) << 1) |		//first modulation stage select
					(OS16<<0) |					//0->oversampling disabled, 1->oversampling enabled
					0x00;
	//the above doesn't work
	//following works
	//UCAxBRW=0x0001;							//works at 3Mhz
	//UCAxMCTLW = 0x00a1;

	//UCAxCTLW1 = 	(3<< 0) |					//0->deglitch = 2ns, 1->deglitch = 50ns, 2->deglitch = 100ns, 3->deglitch = 200ns
	//				0x00;

	//UCAxIE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
	UCAxIFG &=~(UCAxTXIFG | UCAxRXIFG);			//clear all flag
	UCAxIE  &=~(UCAxTXIE  | UCAxRXIE);				//disable all interrupts

	//UCAxCTLW0 &= ~UCSWRST;                    // Initialize eUSCI
	UCAxCTL1&=~(1<<0);							//0->release reset, 1->enable reset
}

//send a char
void uart0_put(char ch) {
	//while ((IFG2 & UCAxTXIFG) == 0) continue;	//UCAxIFG &=~UCTXIFG;			//0->TXBUF is not empty, 1->TXBUF is empty - most aggressive
	//there appears to be a bug in the hardware for UCTXCPTIFG
	//while ((UCAxIFG & UCTXCPTIFG) == 0) continue; //UCAxIFG &=~UCTXCPTIFG;	//wait for all bits to be shifted out and txbuf is empty
	while ((UCAxSTAT & UCBUSY) == 1) continue;	//wait for transmission / receiving to be inactive: 1->busy, 0->not busy - most conservative
	delay(200);									//software bug: UCBUSY not asserted in simulation
	UCAxTXBUF = ch;								//load up the char
}

//send a string
void uart0_puts(char *str) {
	while (*str) uart0_put(*str++);	
}

//receive a char and clear the flag
char uart0_get(void) {
	//UCAxIFG &=~(1ul<<0);						//clear the flag - done automatically by a read of RXBUF
	//non-block -> does not test if data is available
	return UCAxRXBUF;
}

//test if uart tx is busy
char uart0_busy(void) {
	//return (IFG2 & UCAxTXIFG) == 0;			//UCTXIFG = 1 if TXBUF is empty - most aggressive
	//return (UCAxIFG & UCTXCPTIFG) == 0;		//UCTXCPTIFG = 1 if all bits have been shifted out - there is a bug in hardware - do not use
	return (UCAxSTAT & UCBUSY) == 1;			//1->busy transmitting / receiving, 0->not active - most conservative
}

//test if uart rx is available
char uart0_available(void) {
	return UCAxIFG & UCAxRXIFG;
	//if (IFG2 & UCAxRXIFG) return 1;				//UCRXIFG  is automatically reset by a read of RXBUF
	//else return 0;
	//return (UCAxIFG & (1ul<<0));
}

