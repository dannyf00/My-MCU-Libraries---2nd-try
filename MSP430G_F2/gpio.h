#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>									//standard types
#include <stdbool.h>								//we use tivaware
#include <msp430.h>									//we use iar msp430
//#include <io430.h>
#include <intrinsics.h>								//we use nop

//port manipulation macros for PIC.

#define IO_SET(port, bits)	port |= (bits)			//set bits on port
#define IO_CLR(port, bits)	port &=~(bits)			//clear bits on port
#define IO_FLP(port, bits)	port ^= (bits)			//flip bits on port
#define IO_GET(port, bits)	((port) & (bits))		//return bits on port
#define IO_OUT(ddr, bits)	ddr |= (bits)			//set bits as output
#define IO_IN(ddr, bits)	ddr &=~(bits)			//set bits as input

//gpio definitions
#define GIO_SET(port, bits)	IO_SET(port->POUT, bits)		//port->LAT |= (bits)			//set bits on port
#define GIO_CLR(port, bits)	IO_CLR(port->POUT, bits)		//port->LAT &=~(bits)			//clear bits on port
#define GIO_FLP(port, bits)	IO_FLP(port->POUT, bits)		//port->LAT ^= (bits)			//flip bits on port
#define GIO_GET(port, bits)	IO_GET(port->PIN, bits)	//((port->PORT) & (bits))		//return bits on port
#define GIO_OUT(port, bits)	IO_OUT(port->DDR, bits)	//ddr->TRIS &=~(bits)			//set bits as output
#define GIO_IN(port, bits)	IO_IN(port->DDR, bits)		//ddr->TRIS |= (bits)			//set bits as input


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
//led101 = red
#define LED1_GPIO			GPIOA
#define LED1_PORT			P1OUT
#define LED1_DDR			P1DIR
#define LED1				(1<<0)						//red led

//GPIOA.1/Green and GPIOB.14/Red
#define LED2_GPIO			GPIOB
#define LED2_PORT			P4OUT
#define LED2_DDR			P4DIR
#define LED2				(1<<6)						//green led

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
typedef struct {
//for MSP430Fxxxx mcus
	uint16_t PIN;			//input register, @ offset 0x00
	uint16_t POUT;			//output register
	uint16_t DDR;			//direction register
	uint16_t REN;			//resistor enable. '0'->disable pull-up/down, '1'->enable pull-up/down
	uint16_t RESERVED0;
	uint16_t SEL0;			//SEL0
	uint16_t SEL1;			//sel1
	
//for MSP430Gxxxx mcus
	//uint8_t PIN;			//input register, @ offset 0x00
	//uint8_t PORT;			//output register
	//uint8_t DDR;			//direction register
	//uint8_t SEL;			//pin select
	//uint8_t SEL2;			//pin select 2
} GPIO_TypeDef;						//gpio type definitions

#define GPIOA				((volatile GPIO_TypeDef *) &PAIN)
#define GPIOB				((volatile GPIO_TypeDef *) &PBIN)
#define GPIOC				((volatile GPIO_TypeDef *) &PCIN)
#define GPIOD				((volatile GPIO_TypeDef *) &PDIN)
#define GPIOE				((volatile GPIO_TypeDef *) &PEIN)
#define GPIOF				((volatile GPIO_TypeDef *) &PFIN)
#define GPIOJ				((volatile GPIO_TypeDef *) &PJIN)

#endif //gpio_h_
