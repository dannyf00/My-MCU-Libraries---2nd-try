#include "uart2.h"			//we use uart1

//pinconfiguration
#define UxTX2RP()			PPS_U2TX_TO_RP(6)			//u1tx pin
#define UxRX2RP()			PPS_U2RX_TO_RP(2)			//rx pin
//end pin configuration

//for U1ART
#define UxMD				_U2MD		//power management bit
#define UxMODE				U2MODEbits	//mode register
#define UxBRG				U2BRG		//baud rate generator
#define UxSTA				U2STAbits	//status register
#define UxTXIE				_U2TXIE		//interrupt enable bit
#define UxTXIF				_U2TXIF		//interrupt flag
#define UxRXIE				_U2RXIE		//interrupt enable bit
#define UxRXIF				_U2RXIF		//interrupt flag
#define UxTXREG				U2TXREG		//transmission data register
#define UxRXREG				U2RXREG		//transmission data register

#define USART_WAIT(flag)		do {} while (flag==0)		//wait for a usart tranmission to end

//initialize usart: high baudrate (brgh=1), 16-bit baudrate (brg16=1)
//baudrate=Fxtal/(4*(spbrg+1))
//spbrg=(Fxtal/4/baudrate)-1
//tx/rx pins to be assumed in gpio mode
//data bits: 	8
//parity: 		none
//stop bits: 	1
//Xon/Xoff:		none
void uart2_init(unsigned long baud_rate)
{
	//enable the pins
#if defined(UxRX2RP)
	UxRX2RP();					//PPS_U1RX_TO_RP(U1RX_RP);
#endif

#if defined(UxTX2RP)
	UxTX2RP();					//PPS_U1TX_TO_RP();
#endif


	//disable md bits
	UxMD = 0;				//power up the module

	//UxMODE register
	//bit 15 UARTEN: UARTx Enable bit(1)
	//1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>
	//0 = UARTx is disabled; all UARTx pins are controlled by PORT latches; UARTx power consumption is	minimal
	UxMODE.UARTEN=1;	//enable the uart module
	//bit 14 Unimplemented: Read as ‘0’
	//bit 13 USIDL: Stop in Idle Mode bit
	//1 = Discontinue module operation when device enters Idle mode
	//0 = Continue module operation in Idle mode
	//bit 12 IREN: IrDA® Encoder and Decoder Enable bit(2)
	//1 = IrDA encoder and decoder enabled
	//0 = IrDA encoder and decoder disabled
	UxMODE.IREN = 0;		//disable irda
	UxMODE.RTSMD = 0;		//1=in simplex mode. 0 = no flow control
	//bit 11 RTSMD: Mode Selection for UxRTS Pin bit
	//1 = UxRTS pin in Simplex mode
	//0 = UxRTS pin in Flow Control mode
	//bit 10 Unimplemented: Read as ‘0’
	//bit 9-8 UEN1:UEN0: UARTx Enable bits(3)
	//11 = UxTX, UxRX and BCLKx pins are enabled and used; UxCTS pin controlled by PORT latches
	//10 = UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
	//01 = UxTX, UxRX and UxRTS pins are enabled and used; UxCTS pin controlled by PORT latches
	//00 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLKx pins controlled by PORT latches
	UxMODE.UEN1=0, UxMODE.UEN0=0;
	//bit 7 WAKE: Wake-up on Start Bit Detect During Sleep Mode Enable bit
	//1 = UARTx will continue to sample the UxRX pin; interrupt generated on falling edge, bit cleared in hardware on following rising edge
	//0 = No wake-up enabled
	UxMODE.WAKE = 0;
	//bit 6 LPBACK: UARTx Loopback Mode Select bit
	//1 = Enable Loopback mode
	//0 = Loopback mode is disabled
	UxMODE.LPBACK = 0;
	//bit 5 ABAUD: Auto-Baud Enable bit
	//1 = Enable baud rate measurement on the next character – requires reception of a Sync field (55h); cleared in hardware upon completion
	//0 = Baud rate measurement disabled or completed
	UxMODE.ABAUD = 0;
	//bit 4 RXINV: Receive Polarity Inversion bit
	//1 = UxRX Idle state is ‘0’
	//0 = UxRX Idle state is ‘1’
	UxMODE.RXINV = 0;
	//bit 3 BRGH: High Baud Rate Enable bit
	//1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
	//0 = BRG generates 16 clocks per bit period (16x baud clock, Standard mode)
	UxMODE.BRGH = 1;
	//bit 2-1 PDSEL1:PDSEL0: Parity and Data Selection bits
	//11 = 9-bit data, no parity
	//10 = 8-bit data, odd parity
	//01 = 8-bit data, even parity
	//00 = 8-bit data, no parity
	UxMODE.PDSEL1=0, UxMODE.PDSEL0=0;
	//bit 0 STSEL: Stop Bit Selection bit
	//1 = Two Stop bits
	//0 = One Stop bit
	UxMODE.STSEL=0;
	//Note 1: If UARTEN = 1, the peripheral inputs and outputs must be configured to an available RPn pin. See
	//Section 10.4 “Peripheral Pin Select” for more information.
	//2: This feature is only available for the 16x BRG mode (BRGH = 0).
	//3: Bit availability depends on pin availability.


	//BAUDCON
	UxBRG = F_UART / 4 / baud_rate - 1;				//set lower byte of brg

	//disable interrupts
#if defined(UxTX2RP)
	UxTXIF = 0;						//clera the flag
	UxTXIE = 0;						//disable the interrupt

	//set up status register
	//bit 15,13 UTXISEL1:UTXISEL0: Transmission Interrupt Mode Selection bits
	//11 = Reserved; do not use
	//10 = Interrupt when a character is transferred to the Transmit Shift Register (TSR) and as a result, the transmit buffer becomes empty
	//01 = Interrupt when the last character is shifted out of the Transmit Shift Register; all transmit operations are completed
	//00 = Interrupt when a character is transferred to the Transmit Shift Register (this implies there is at least one character open in the transmit buffer)
	UxSTA.UTXISEL1=0, UxSTA.UTXISEL0=0;
#endif
	//bit 14 UTXINV: IrDA® Encoder Transmit Polarity Inversion bit
	//If IREN = 0:
	//1 = UxTX Idle ‘0’
	//0 = UxTX Idle ‘1’
	//If IREN = 1:
	//1 = UxTX Idle ‘1’
	//0 = UxTX Idle ‘0’
	UxSTA.UTXINV=0;
	//bit 12 Unimplemented: Read as ‘0’
	//bit 11 UTXBRK: Transmit Break bit
	//1 = Send Sync Break on next transmission – Start bit, followed by twelve ‘0’ bits, followed by Stop bit;	cleared by hardware upon completion
	//0 = Sync Break transmission disabled or completed
	UxSTA.UTXBRK=0;
	//bit 10 UTXEN: Transmit Enable bit(1)
	//1 = Transmit enabled, UxTX pin controlled by UARTx
	//0 = Transmit disabled, any pending transmission is aborted and buffer is reset. UxTX pin controlled by the PORT register.
	UxSTA.UTXEN=1;
	//bit 9 UTXBF: Transmit Buffer Full Status bit (read-only)
	//1 = Transmit buffer is full
	//0 = Transmit buffer is not full, at least one more character can be written
	//bit 8 TRMT: Transmit Shift Register Empty bit (read-only)
	//1 = Transmit Shift Register is empty and transmit buffer is empty (the last transmission has completed)
	//0 = Transmit Shift Register is not empty, a transmission is in progress or queued
#if defined(UxRX2RP)
	UxRXIF = 0;						//clear the flag
	UxRXIE = 0;						//disable the interrupt

	//bit 7-6 URXISEL1:URXISEL0: Receive Interrupt Mode Selection bits
	//11 = Interrupt is set on RSR transfer, making the receive buffer full (i.e., has 4 data characters)
	//10 = Interrupt is set on RSR transfer, making the receive buffer 3/4 full (i.e., has 3 data characters)
	//0x = Interrupt is set when any character is received and transferred from the RSR to the receive buffer. Receive buffer has one or more characters.
	UxSTA.URXISEL1 = 0, UxSTA.URXISEL0 = 0;
#endif
	//bit 5 ADDEN: Address Character Detect bit (bit 8 of received data = 1)
	//1 = Address Detect mode enabled. If 9-bit mode is not selected, this does not take effect.
	//0 = Address Detect mode disabled
	//bit 4 RIDLE: Receiver Idle bit (read-only)
	//1 = Receiver is Idle
	//0 = Receiver is active
	//bit 3 PERR: Parity Error Status bit (read-only)
	//1 = Parity error has been detected for the current character (character at the top of the receive FIFO)
	//0 = Parity error has not been detected
	//bit 2 FERR: Framing Error Status bit (read-only)
	//1 = Framing error has been detected for the current character (character at the top of the receive FIFO)
	//0 = Framing error has not been detected
	//bit 1 OERR: Receive Buffer Overrun Error Status bit (clear/read-only)
	//1 = Receive buffer has overflowed
	//0 = Receive buffer has not overflowed (clearing a previously set OERR bit (1  0 transition) will reset the receiver buffer and the RSR to the empty state)
	//bit 0 URXDA: Receive Buffer Data Available bit (read-only)
	//1 = Receive buffer has data; at least one more character can be read
	//0 = Receive buffer is empty
	//REGISTER 17-2: UxSTA: UARTx STATUS AND CONTROL REGISTER (CONTINUED)
	//Note 1: If UARTEN = 1, the peripheral inputs and outputs must be configured to an available RPn pin. See
	//Section 10.4 “Peripheral Pin Select” for more information.

}

void uart2_putch(char ch) {
	while (UxSTA.UTXBF) continue;	//wait if the tx buffer is full

	//Write data
	UxTXREG=ch;				//load up the tx register

	//while(!TRMT);			//wait for the transmission to finish
							//don't use txif as this is not back-to-back transmission
	//USART_WAIT(UxSTA.TRMT);
}

void uart2_puts(char *str) {
	while(*str) {
		uart2_putch(*str++);	//send the ch and advance the pointer
	}
}

/*

Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux

*/

void uart2_putline(char *ln) {
	//USARTWriteString(ln);
	uart2_puts(ln);
	//USARTWriteString("\r\n");
	uart2_puts((char *)"\r\n");
}

unsigned char uart2_getch(void) {
	//while(!RCIF); RCIF=0;		//Wait for a byte
	//USART_WAIT(UxSTA.TRMT);		//wait for the prior transmission to end

	return UxRXREG;		//return it
}

//test if data rx is available
uint16_t uart2_available(void) {
	return UxSTA.URXDA;
}

//test if uart tx is busy
uint16_t uart2_busy(void) {
	return UxSTA.UTXBF;
}
