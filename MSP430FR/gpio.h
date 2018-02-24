#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>									//standard types
#include <stdbool.h>								//we use tivaware
#include <msp430.h>									//we use iar msp430
//#include <io430.h>
#include <intrinsics.h>								//we use nop

//port manipulation macros for PIC.

//port macros
#define IO_SET(port, pins)			port->DATA |= (pins)
#define IO_CLR(port, pins)			port->DATA &=~(pins)
#define IO_FLP(port, pins)			port->DATA ^= (pins)
#define IO_GET(port, pins)			((port->IN)&(pins))

#define IO_IN(port, pins)			IO_INFL(port, pins)
#define IO_OUT(port, pins)			IO_OUTPP(port, pins)
#define IO_INFL(port, pins)			do {port->DIR &=~(pins);                     port->REN&=~(pins); IO_AF0(port, pins);} while (0)	//floating input
#define IO_INPU(port, pins)			do {port->DIR &=~(pins); port->OUT|= (pins); port->REN|= (pins); IO_AF0(port, pins);} while (0)	//input with pull-up
#define IO_INPD(port, pins)			do {port->DIR &=~(pins); port->OUT&=~(pins); port->REN|= (pins); IO_AF0(port, pins);} while (0)	//input with pull-down
#define IO_OUTPP(port, pins)		do {port->DIR |= (pins);                                                            } while (0)	//output, push-pull
#define IO_AF0(port, pins)			do {port->SEL1&=~(pins); port->SEL0&=~(pins);} while (0)	//0b00->GPIO
#define IO_AF1(port, pins)			do {port->SEL1&=~(pins); port->SEL0|= (pins);} while (0)	//0b01->primary alternate function
#define IO_AF2(port, pins)			do {port->SEL1|= (pins); port->SEL0&=~(pins);} while (0)	//0b10->secondary alternate function
#define IO_AF3(port, pins)			do {port->SEL1|= (pins); port->SEL0|= (pins);} while (0)	//0b11->tertiary alternate function

#define NOP()				__no_operation()			//asm("nop")					//nop()
#define NOP2()				{NOP(); NOP();}
#define NOP4()				{NOP2(); NOP2();}
#define NOP8()				{NOP4(); NOP4();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP24()				{NOP16(); NOP8();}
#define NOP32()				{NOP16(); NOP16();}
#define NOP40()				{NOP32(); NOP8();}
#define NOP64()				{NOP32(); NOP32();}

//define leds
//led101 = red led on PORTA0
//led102 = Green and PORTB.14

#define sleep()				asm("sleep")				//put the mcu into sleep

#define F_CPU				(F_SMCLK)					//cpu runs at 2Mhz -> Fxtal = 1Mhz
#define F_ACLK				32768						//ACLK = 32768Hz
#define F_MCLK				1000000ul					//master clock MCLK = 1Mhz
#define F_SMCLK				1000000ul					//sub-main clock = 1Mhz

//void (*mcu_reset)(void) = 0x0000; 				//jump to 0x0000 -> software reset

#ifndef ei
#define ei()				__enable_interrupt()
#endif

#ifndef di
#define di()				__disable_interrupt()
#endif

//device/family id
//#define DEVID				(*(const unsigned int *) 0xff0000)
//#define DEVREV			(*(const unsigned int *) 0xff0002)

//clock management
//clock management
#define DCO_RSEL2x		(1<<6)		//double the frequency
#define DCO_FSEL0		(0<<1)		//1Mhz/1Mhz
#define DCO_FSEL1		(1<<1)		//2.67/5.33Mhz
#define DCO_FSEL2		(2<<1)		//3.5/7.0Mhz
#define DCO_FSEL3		(3<<1)		//4.0/8.0Mhz
#define DCO_FSEL4		(4<<1)		//5.33/16.0Mhz
#define DCO_FSEL5		(5<<1)		//7.0/21.0Mhz
#define DCO_FSEL6		(6<<1)		//8.0/24.0Mhz
#define DCO_FSEL7		(7<<1)		//reserved

extern uint32_t SystemCoreClock;	//default clock
#define SystemCoreClock2DCO_1Mhz()	SystemCoreClock2DCO(DCO_FSEL0)
#define SystemCoreClock2DCO_2M7hz()	SystemCoreClock2DCO(DCO_FSEL1)
#define SystemCoreClock2DCO_5M3hz()	SystemCoreClock2DCO(DCO_FSEL1 | DCO_RSEL2x)
#define SystemCoreClock2DCO_3M5hz()	SystemCoreClock2DCO(DCO_FSEL2)
#define SystemCoreClock2DCO_7Mhz()	SystemCoreClock2DCO(DCO_FSEL2 | DCO_RSEL2x)
#define SystemCoreClock2DCO_4Mhz()	SystemCoreClock2DCO(DCO_FSEL3)
#define SystemCoreClock2DCO_8Mhz()	SystemCoreClock2DCO(DCO_FSEL3 | DCO_RSEL2x)
//#define SystemCoreClock2DCO_5M3hz()	SystemCoreClock2DCO(DCO_FSEL4)
#define SystemCoreClock2DCO_16hz()	SystemCoreClock2DCO(DCO_FSEL4 | DCO_RSEL2x)
//#define SystemCoreClock2DCO_7Mhz()	SystemCoreClock2DCO(DCO_FSEL5)
#define SystemCoreClock2DCO_21Mhz()	SystemCoreClock2DCO(DCO_FSEL5 | DCO_RSEL2x)
//#define SystemCoreClock2DCO_8Mhz()	SystemCoreClock2DCO(DCO_FSEL6)
#define SystemCoreClock2DCO_24Mhz()	SystemCoreClock2DCO(DCO_FSEL7 | DCO_RSEL2x)

void mcu_init(void);									//reset the mcu


//simple multiples
#define x1(val)				(val)								//multiply val by 1
#define x2(val)				(((val) << 1))						//multiply val by 2
#define x3(val)				(x2(val) + (val))					//multiply val by 3
#define x4(val)				(((val) << 2))						//multiply val by 4
#define x5(val)				(x4(val) + (val))					//multiply val by 5
#define x6(val)				(x4(val) + x2(val))					//multiply val by 6
#define x7(val)				(x6(val) + (val))					//multiply val by 7
#define x8(val)				((val) << 3)						//multiply val by 8
#define x9(val)				(x8(val) + (val))					//multiply val by 9

//multiples of 10s
#define x10(val)			(x8(val) + x2(val))					//multiply val by 10
#define x100(val)			(x10(x10(val)))						//multiply val by 100
#define x1000(val)			(x100(x10(val)))					//multiply val by 1000
#define x1k(val)			x1000(val)							//multiply val by 1000
#define x10k(val)			(x100(x100(val)))					//multiply val by 10000

#define x20(val)			(x2(x10(val)))
#define x30(val)			(x3(x10(val)))
#define x40(val)			(x4(x10(val)))
#define x50(val)			(x5(x10(val)))
#define x60(val)			(x6(x10(val)))
#define x70(val)			(x7(x10(val)))
#define x80(val)			(x8(x10(val)))
#define x90(val)			(x9(x10(val)))

//multiples of 100s
#define x200(val)			(x2(x100(val)))
#define x300(val)			(x3(x100(val)))
#define x400(val)			(x4(x100(val)))
#define x500(val)			(x5(x100(val)))
#define x600(val)			(x6(x100(val)))
#define x700(val)			(x7(x100(val)))
#define x800(val)			(x8(x100(val)))
#define x900(val)			(x9(x100(val)))

//custom definitions
#define x34(val)			(x30(val) + x4(val))				//multiply val by 34
#define x97(val)			(x90(val) + x7(val))				//multiply val by 97x

//gpio definitions
//16-bit gpio, with interrupt
typedef struct {
	uint16_t IN;					//input register
	uint16_t DATA;					//OUT;					//output register
	uint16_t DIR;					//direction register
	uint16_t REN;					//resistor enable register
	uint8_t  RESERVED0[0x0a-0x08];	//08..09
	uint16_t SEL0;
	uint16_t SEL1;					//select 0/1
	uint8_t  RESERVED1[0x16-0x0e];	//0x0e..0x15
	uint16_t SELC;					//Complement select
	uint16_t IES;					//interrupt edge select
	uint16_t IE;					//interrupt enable
	uint16_t IFG;					//interrupt flag
} GPIOINT_TypeDef;

//16-bit gpio, without interrupt
//IES/IE/IFG included for compatability
//not all ports have them
typedef struct {
	uint16_t IN;					//input register
	uint16_t DATA;					//OUT;					//output register
	uint16_t DIR;					//direction register
	uint16_t REN;					//resistor enable register
	uint8_t  RESERVED0[0x0a-0x08];	//08..09
	uint16_t SEL0;
	uint16_t SEL1;					//select 0/1
	uint8_t  RESERVED1[0x16-0x0e];	//0x0e..0x15
	uint16_t SELC;					//Complement select
	uint16_t IES;					//interrupt edge select
	uint16_t IE;					//interrupt enable
	uint16_t IFG;					//interrupt flag
} PORT_TypeDef;

//PORTA..J = PA..J
#define PORTA						((PORT_TypeDef *)&PAIN)
#define PORTB						((PORT_TypeDef *)&PBIN)
#define PORTC						((PORT_TypeDef *)&PCIN)
#define PORTD						((PORT_TypeDef *)&PDIN)
#define PORTE						((PORT_TypeDef *)&PEIN)
#define PORTF						((PORT_TypeDef *)&PFIN)
#define PORTJ						((PORT_TypeDef *)&PJIN)

//8-bit port, PORT1, PORT2, PORT3, ..., - notice the offset
typedef struct {
	//uint8_t RESERVED;
	uint8_t IN;						//input register
	uint8_t RESERVED0;
	uint8_t DATA;					//OUT;					//output register
	uint8_t RESERVED1;
	uint8_t DIR;					//direction register
	uint8_t RESERVED2;
	uint8_t REN;					//resistor enable register
	uint8_t RESERVED3;
	uint8_t RESERVED4[0x0a-0x08];	//08..09
	uint8_t SEL0; 
	uint8_t RESERVED5;
	uint8_t SEL1;					//select 0/1
	uint8_t RESERVED6;
	uint8_t RESERVED7[0x16-0x0e];	//0x0e..0x15
	uint8_t SELC;					//Complement select
	uint8_t RESERVED8;
	uint8_t IES;					//interrupt edge select
	uint8_t RESERVED9;
	uint8_t IE;						//interrupt enable
	uint8_t RESERVED10;
	uint8_t IFG;					//interrupt flag
	uint8_t RESERVED11;
} PORT8_TypeDef;
	
//PORTA..J = PA..J
#define PORT1						((PORT8_TypeDef *)((uint8_t *) &PAIN + 0))
#define PORT2						((PORT8_TypeDef *)((uint8_t *) &PAIN + 1))
#define PORT3						((PORT8_TypeDef *)((uint8_t *) &PBIN + 0))
#define PORT4						((PORT8_TypeDef *)((uint8_t *) &PBIN + 1))
#define PORT5						((PORT8_TypeDef *)((uint8_t *) &PCIN + 0))
#define PORT6						((PORT8_TypeDef *)((uint8_t *) &PCIN + 1))
#define PORT7						((PORT8_TypeDef *)((uint8_t *) &PDIN + 0))
#define PORT8						((PORT8_TypeDef *)((uint8_t *) &PDIN + 1))
#define PORT9						((PORT8_TypeDef *)((uint8_t *) &PEIN + 0))
#define PORT10						((PORT8_TypeDef *)((uint8_t *) &PEIN + 1))
#define PORT11						((PORT8_TypeDef *)((uint8_t *) &PJIN + 0))

//for compatability
#define PA							PORTA
#define PB							PORTB
#define PC							PORTC
#define PD							PORTD
#define PE							PORTE
#define PF							PORTF
#define PJ							PORTJ

#define P1							PORT1
#define P2							PORT2
#define P3							PORT3
#define P4							PORT4
#define P5							PORT5
#define P6							PORT6
#define P7							PORT7
#define P8							PORT8
#define P9							PORT9
#define P10							PORT10
#define P11							PORT11

//timer_a structure
typedef struct {
	uint16_t CTL;					//control register
	union {
		uint16_t CCTL[7];			//as an array, 
		struct {					//or individual registers
			uint16_t CCTL0;					//capture/compare control0
			uint16_t CCTL1;					//capture/compare control0
			uint16_t CCTL2;					//capture/compare control0
			uint16_t CCTL3;					//capture/compare control0
			uint16_t CCTL4;					//capture/compare control0
			uint16_t CCTL5;					//capture/compare control0
			uint16_t CCTL6;					//capture/compare control0
		};
	};
	uint16_t R;						//counter
	union {
		uint16_t CCR[7];			//as an array,
		struct {					//or individual registres
			uint16_t CCR0;					//capture/compare 0
			uint16_t CCR1;					//capture/compare 1
			uint16_t CCR2;					//capture/compare 2
			uint16_t CCR3;					//capture/compare 3
			uint16_t CCR4;					//capture/compare 4
			uint16_t CCR5;					//capture/compare 5
			uint16_t CCR6;					//capture/compare 6
		};
	};
	uint16_t EX0;					//expansion 0
	uint8_t  RESERVED0[0x2e-0x22];	//0x22..0x2d
	uint16_t IV;					//interrupt vector
} TIMERA_TypeDef;

//timera definitions
#define TIMERA0						((TIMERA_TypeDef *)&TA0CTL)
#define TIMERA1						((TIMERA_TypeDef *)&TA1CTL)
#define TIMERA2						((TIMERA_TypeDef *)&TA2CTL)
#define TIMERA3						((TIMERA_TypeDef *)&TA3CTL)

//timer_b structure
typedef struct {
	uint16_t CTL;					//control register
	union {
		uint16_t CCTL[7];			//as an array, 
		struct {					//or individual registers
			uint16_t CCTL0;					//capture/compare control0
			uint16_t CCTL1;					//capture/compare control0
			uint16_t CCTL2;					//capture/compare control0
			uint16_t CCTL3;					//capture/compare control0
			uint16_t CCTL4;					//capture/compare control0
			uint16_t CCTL5;					//capture/compare control0
			uint16_t CCTL6;					//capture/compare control0
		};
	};
	uint16_t R;						//counter
	union {
		uint16_t CCR[7];			//as an array,
		struct {					//or individual registres
			uint16_t CCR0;					//capture/compare 0
			uint16_t CCR1;					//capture/compare 1
			uint16_t CCR2;					//capture/compare 2
			uint16_t CCR3;					//capture/compare 3
			uint16_t CCR4;					//capture/compare 4
			uint16_t CCR5;					//capture/compare 5
			uint16_t CCR6;					//capture/compare 6
		};
	};
	uint16_t EX0;					//expansion 0
	uint8_t  RESERVED0[0x2e-0x22];	//0x22..0x2d
	uint16_t IV;					//interrupt vector
} TIMERB_TypeDef;

//timerb definitions
#define TIMERB0						((TIMERB_TypeDef *)&TB0CTL)
#define TIMERB1						((TIMERB_TypeDef *)&TB1CTL)
#define TIMERB2						((TIMERB_TypeDef *)&TB2CTL)
#define TIMERB3						((TIMERB_TypeDef *)&TB3CTL)

//uart0 struct
//eUSCI_A
typedef struct {
	uint16_t CTLW0;					//control word0
	uint16_t CTLW1;					//control word1
	uint8_t  RESERVED0[0x05-0x04+1];			//0x04..0x05
	uint16_t BRW;					//board rate
	uint16_t MCTLW;					//modulation control word
	uint16_t STATW;					//status
	uint16_t RXBUF;					//receive buffer
	uint16_t TXBUF;					//transmit buffer
	uint16_t ABCTL;					//auto baud rate control
	uint16_t IRCTL;					//IrDA control
	uint8_t  RESERVED1[0x19-0x14+1];	//from 0x14..0x19
	uint16_t IE;					//interrupt enable
	uint16_t IFG;					//interrupt flag
	uint16_t IV;					//interrupt vector
} UART_TypeDef;

#define UART0						((UART_TypeDef *)&UCA0CTLW0)
#define UART1						((UART_TypeDef *)&UCA1CTLW0)
#define UART2						((UART_TypeDef *)&UCA2CTLW0)
#define UART3						((UART_TypeDef *)&UCA3CTLW0)

#endif
