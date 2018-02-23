#ifndef _GPIO_H
#define _GPIO_H

#include "lpc210x.h"								//we use lpc210x
#include <stdint.h>									//we use stndard int types
//port macros
#define IO_OUT(port, pins)			port |= (pins)
#define IO_IN(port, pins)			port &=~(pins)

#define IO_SET(port, pins)			port |= (pins)
#define IO_CLR(port, pins)			port &=~(pins)
#define IO_FLP(port, pins)			port ^= (pins)
#define IO_GET(port, pins)			((port) & (pins))

//#define FIO_SET(port, pins)			port->FIOSET = (pins)
//#define FIO_CLR(port, pins)			port->FIOCLR = (pins)
//#define FIO_SET(port, pins)			port->MASKED_ACCESS[(pins) & 0b11111111111] = ((pins) & 0b11111111111)
//#define FIO_CLR(port, pins)			port->MASKED_ACCESS[(pins) & 0b11111111111] = 0
//#define FIO_FLP(port, pins)			IO_FLP(port, pins)
//#define FIO_GET(port, pins)			((port->FIOPIN) & (pins))

//gpio macros
#define GIO_SET(gpio, pins)			gpio->SET = (pins)
#define GIO_CLR(gpio, pins)			gpio->CLR = (pins)
#define GIO_FLP(gpio, pins)			gpio->PIN^= (pins)
#define GIO_GET(gpio, pins)			((gpio->PIN) & (pins))
#define GIO_OUT(gpio, pins)			gpio->DIR|= (pins)
#define GIO_IN(gpio, pins)			gpio->DIR&=~(pins)


//specific to STM32VLDiscovery
//led definitions
#define LED_GPIO		GPIO
#define LED_PORT		IOPIN
#define LED_DDR			IODIR
#define LED				(1<<7)						//GPIO_Pin_9			//green led on pc9

//#define GPIO0			LPC_GPIO0
//#define GPIO1			LPC_GPIO1
//#define GPIO2			LPC_GPIO2

//reset the mcu
void mcu_init(void);


//nop
#define NOP()	__nop()
#define NOP2()	{NOP(); NOP();}
#define NOP4()	{NOP2(); NOP2();}
#define NOP8()	{NOP4(); NOP4();}
#define NOP16()	{NOP8(); NOP8();}
#define NOP24()	{NOP16(); NOP8();}
#define NOP32()	{NOP16(); NOP16();}
#define NOP40()	{NOP32(); NOP8();}

//f_cpu speed
//#define SystemCoreClock		(SystemFrequency)					//SystemFrequency used in the library files
#define F_CPU					(24000000ul)						//cpu runs at 2Mhz -> Fxtal = 2Mhz

//void (*mcu_reset)(void) = 0x0000; 				//jump to 0x0000 -> software reset

#ifndef ei
#define ei()													//not used - for compatability reasons
#endif

#ifndef di
#define di()													//not used - for compatability reasons
#endif

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
#define x1k(val)			(x1000(val))						//multiply val by 1000
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

//port struct
typedef struct {
	uint32_t PIN;
	uint32_t SET;
	uint32_t DIR;
	uint32_t CLR;
} GPIO_Type;

#define GPIO				((volatile  GPIO_Type *) & IOPIN)

//timer0/1 struct
typedef struct {
	uint32_t IR;			//interrupt register. write '1' to clear
	uint32_t TCR;			//timer control register
	uint32_t TC;			//timer counter;
	uint32_t PR;			//prescale register
	uint32_t PC;			//prescale counter;
	uint32_t MCR;			//match control register
	uint32_t MR0;			//match register 0..3
	uint32_t MR1;
	uint32_t MR2;
	uint32_t MR3;
	uint32_t CCTLR;			//=CCR: capture control register
	uint32_t CR0;			//capture register 0..3
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t EMR;			//external match register. EMR@0x403c
	uint8_t reserved[0x4070 - (0x403c+4)];
	uint32_t CTCR;			//count control register, CTCR @ 0x4070
} CTIMER_Type;

#define CT0					((volatile CTIMER_Type *) & T0IR)
#define CT1					((volatile CTIMER_Type *) & T1IR)

//pwm struct
typedef struct {
	uint32_t IR;			//interrupt register
	uint32_t TCR;			//timer control register
	uint32_t TC;			//timer counter
	uint32_t PR;			//prescaler register
	uint32_t PC;			//prescaler counter
	uint32_t MCR;			//match control register
	uint32_t MR0;			//match register 0..6
	uint32_t MR1;
	uint32_t MR2;
	uint32_t MR3;		  	//@4024
	uint8_t RESERVED0[0x4040 - (0x4024 + 4)];
	uint32_t MR4;			//@4040
	uint32_t MR5;
	uint32_t MR6;
	uint32_t PCR;			//pwm control register @404c
	//uint8_t RESERVED1[0x4050 - 0x404c - 4];
	uint32_t LER;			//latch enable register @4050
} LPC_PWM_TypeDef;

#define PWM0				((volatile LPC_PWM_TypeDef *) &PWMIR)


#endif
