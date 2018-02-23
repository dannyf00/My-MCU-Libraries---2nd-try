#ifndef _GPIO_H_
#define _GPIO_H_

//gpio header file for lpc21xx
#if defined(__GNUC__)
	#include <stdint.h>							//uint8_t ... types
	#include <avr/io.h>							//we use avr
	#include <avr/interrupt.h>
#elif defined(__ICCAVR__)
//#if defined(__EWAVR__)						//alternatively
	#include <ioavr.h>							//we use iar avr
	#include <stdint.h>							//have to use dlib (General Options->Library Configuration->Normal DLIB
	#include <intrinsics.h>						//we use _nop_(). IAR AVR only
#else
	#warning "no general header files included"	//need to put something here if not covered by gcc/iar avr
#endif

//port definitions
#define IO_SET(port, bits)	port |= (bits)		//set bits on port
#define IO_CLR(port, bits)	port &=~(bits)		//clear bits on port
#define IO_FLP(port, bits)	port ^= (bits)		//flip bits on port
#define IO_GET(port, bits)	((port) & (bits))	//return bits on port
#define IO_IN(ddr, bits)	ddr &=~(bits)		//set bits as input
#define IO_OUT(ddr, bits)	ddr |= (bits)		//ddr |= (bits)		//set bits as output

//gpio definitions
#define GIO_SET(port, bits)	IO_SET(port->PORT,bits)		//set bits on port
#define GIO_CLR(port, bits)	IO_CLR(port->PORT,bits)		//clear bits on port
#define GIO_FLP(port, bits)	IO_FLP(port->PORT,bits)		//flip bits on port
#define GIO_GET(port, bits)	IO_GET(port->PIN, bits)		//return bits on port
#define GIO_IN(port, bits)	IO_IN(port->DDR, bits)		//set bits as input
#define GIO_OUT(port, bits)	IO_OUT(port->DDR, bits)		//ddr |= (bits)		//set bits as output

#define NOP()				asm("nop")			//nop
#define NOP2()				{NOP(); NOP();}
#define NOP4()				{NOP2(); NOP2();}
#define NOP8()				{NOP4(); NOP4();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP24()				{NOP16(); NOP8();}
#define NOP32()				{NOP16(); NOP16();}
#define NOP40()				{NOP32(); NOP8();}
#define NOP64()				{NOP32(); NOP32();}

#if defined(__ICCAVR__) 						//for ewavr
//#if defined(__EWAVR__)							//alternatively
    #define ei()  			__enable_interrupt()
	#define di()			__disable_interrupt()
#endif

#if defined(__GNUC__)							//for gcc avr
	#include <avr/interrupt.h>					//sei/cli defined in interrupt.h
	#define ei()			sei()				//enable interrupt
	#define di()			cli()				//disable interrupt
#endif

#ifndef F_CPU
	#define F_CPU			1000000ul			//cpu runs at 1Mhz
#endif

//void (*mcu_reset)(void) = 0x0000; 			//jump to 0x0000 -> software reset
void mcu_init(void);

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

//arduino related macros
//arduino pin functions
#define AIO_SET(pin)		digitalWrite(pin, HIGH)
#define AIO_CLR(pin)		digitalWrite(pin, LOW)
#define AIO_FLP(pin)		digitalWrite(pin, !digitalRead(pin))

#define AIO_OUT(pin)		pinMode(pin, OUTPUT)
#define AIO_IN(pin)			pinMode(pin, INPUT)

//gpio definitions
typedef struct {
	volatile unsigned char PIN;	//input data register
	volatile unsigned char DDR;	//data direction register
	volatile unsigned char PORT;	//output data register
} GPIO_TypeDef;				//gpio data registers

#define GPIOA				((GPIO_TypeDef *) &PINA)
#define GPIOB				((GPIO_TypeDef *) &PINB)
#define GPIOC				((GPIO_TypeDef *) &PINC)
#define GPIOD				((GPIO_TypeDef *) &PIND)
#define GPIOE				((GPIO_TypeDef *) &PINE)
#define GPIOF				((GPIO_TypeDef *) &PINF)
#define GPIOG				((GPIO_TypeDef *) &PING)
#define GPIOH				((GPIO_TypeDef *) &PINH)

#endif //gpio_h_
