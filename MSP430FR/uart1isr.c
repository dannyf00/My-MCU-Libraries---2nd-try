#include "uart1isr.h"								//uart on eUSCI_A0..3 for MSP432

//EUSCI_A
#define eUSCIx				UART1

//global variables
static char *_UxTX_ptr;
static unsigned char _UxTX_BUSY=0;		//0=ux transmission done, 1=ux transmission in process

//uart0-isr: only TX is implemented
#pragma vector=USCI_A1_VECTOR
__interrupt void _ISRUSCI_A1 (void) {
	//TX interrupt
	//clear the flag
	if (*_UxTX_ptr) {					//0 indicates the end of the string
		//_UxTX_ptr;					//increment to the next char
		eUSCIx->TXBUF = *_UxTX_ptr++;	//load up a char to be transmitted
	} else {
		//UxSTA.UTXEN = 0;				//turn off the transmission
		eUSCIx->IE &=~UCTXIE;			//UxTXIE = 0;						//0->disable the interrupt
		_UxTX_BUSY = 0;					//transmission done
	}
}



//reset uart1/eusci_a1
void uart1_init(uint32_t bps) {
	uint16_t brx;								//used for baud rate calculation, corresponds to BRx, BRFx, BRSx in the datasheet
	uint8_t brfx, brsx;
	uint8_t OS16;
	uint32_t intN;
	uint32_t fracN;								//N - INT(N), x 10000

	//configure the pins
#if defined(UART1_TX)
	UART1_TX();
#endif
	
#if defined(UART1_RX)
	UART1_RX();
#endif
	
	// Configure USCI_A0 for UART mode
	eUSCIx->CTLW0 = (1<<0);						//EUSCI_A_CTLW0_SWRST;			//UCA0CTLW0 = UCSWRST;                      // Put eUSCI in reset
	//eUSCIx->CTLW0|= EUSCI_A_CTLW0_SSEL__SMCLK;	//UCA0CTLW0 |= UCSSEL__SMCLK;               // CLK = SMCLK
	eUSCIx->CTLW0 = 	(0<<15) |					//0->parity disabled, 1->parity enabled
					(0<<14) |					//0->odd parity, 1->even parity
					(0<<13) |					//0->lsb first, 1->msb first
					(0<<12) |					//0->8-bit data, 1->7-bit data
					(0<<11) |					//0->1 stop bit, 1->two stop bits
					(0<< 9) |					//0->uart mode, 1->idle line multiprocessor mode, 1->address-bit multiprocessor mode, 3->uart mode with automatic baud rate detection
					(0<< 8) |					//0->asynchronous mode, 1->synchronous mode
					(2<< 6) |					//0->uclk, 1->aclk, 2->smclk, 3->smclk
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
		//step 3
		OS16 = 1; brx = intN / 16; brfx = intN - (brx * 16);
	} else {
		//step 2
		OS16 = 0; brx = intN; brfx = 0;
	}
	//step 4
	fracN = (F_UART - intN * bps) * 10000ul / bps;
	brsx = 0;									//default to 0
#if 1
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

	eUSCIx->BRW=brx;
	//UCA0BR0 = 52;                             // 8000000/16/9600
	//UCA0BR1 = 0x00;
	//UCA0MCTLW |= UCOS16 | UCBRF_1;
	eUSCIx->MCTLW = 	((brsx & 0xff) << 8) |		//ucbrsx: 2nd modulation stage select
					((brfx &  0x0f) << 4) |		//first modulation stage select
					(OS16<<0) |					//0->oversampling disabled, 1->oversampling enabled
					0x00;
	//the above doesn't work
	//following works
	//eUSCIx->BRW=0x0001;						//works at 3Mhz
	//eUSCIx->MCTLW = 0x00a1;

	eUSCIx->CTLW1 = 	(3<< 0) |					//0->deglitch = 2ns, 1->deglitch = 50ns, 2->deglitch = 100ns, 3->deglitch = 200ns
					0x00;

	//UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
	eUSCIx->IFG = 0x00;							//clear all flag
	eUSCIx->IE  = 0x00;							//disable all interrupts

	//UCA0CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
	eUSCIx->CTLW0&=~(1<<0);						//0->release reset, 1->enable reset
}

//send a char
void uart1_put(char ch) {
	while ((eUSCIx->IFG & UCTXIFG) == 0) continue;//eUSCIx->IFG &=~UCTXIFG;			//0->TXBUF is not empty, 1->TXBUF is empty - most aggressive
	//there appears to be a bug in the hardware for UCTXCPTIFG
	//while ((eUSCIx->IFG & UCTXCPTIFG) == 0) continue; //eUSCIx->IFG &=~UCTXCPTIFG;	//wait for all bits to be shifted out and txbuf is empty
	//while ((eUSCIx->STATW & UCBUSY) == 1) continue;	//wait for transmission / receiving to be inactive - most conservative
	eUSCIx->TXBUF = ch;							//load up the char
}

//send a string
void uart1_puts(char *str) {
	//while (*str) uart0_put(*str++);
	if (*str) {							//if the string isn't empty to begin with
		_UxTX_BUSY  = 1;					//transmission in progress
		_UxTX_ptr=str;						//point to the string to be transmitted
		eUSCIx->IFG &=~UCTXIFG;				//UxTXIF = 0;							//clear the flag
		//UxSTA.UTXEN=1;					//enable transmission - always enabled
		eUSCIx->IE |= UCTXIE;				//UxTXIE = 1;							//enable the interrupt
		eUSCIx->TXBUF = *_UxTX_ptr++;				//load up the 1st char. advance to the next char
	}
	
}

//receive a char and clear the flag
char uart1_get(void) {
	//eUSCIx->IFG &=~(1ul<<0);					//clear the flag - done automatically by a read of RXBUF
	//non-block -> does not test if data is available
	return eUSCIx->RXBUF;
}

//test if uart tx is busy
char uart1_busy(void) {
	return _UxTX_BUSY;
	//return (eUSCIx->IFG & UCTXIFG) == 0;			//UCTXIFG = 1 if TXBUF is empty - most aggressive
	//return (eUSCIx->IFG & UCTXCPTIFG) == 0;	//UCTXCPTIFG = 1 if all bits have been shifted out - there is a bug in hardware - do not use
	//return (eUSCIx->STATW & UCBUSY) == 1;		//1->busy transmitting / receiving, 0->not active - most conservative
}

//test if uart rx is available
char uart1_available(void) {
	if (eUSCIx->IFG & UCRXIFG) return 1;			//UCRXIFG  is automatically reset by a read of RXBUF
	else return 0;
	//return (eUSCIx->IFG & (1ul<<0));
}

