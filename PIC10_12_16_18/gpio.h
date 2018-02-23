#ifndef __GPIO_H
#define __GPIO_H

//#include <htc.h>                                  //we use htc
#include <xc.h>                                     //we use xc8 compiler

//hardware configuration
//use LATx instead of PORTx registers
//#define LAT_USED                                  //uncomment to use LATx registers
//end hardware configuration

//reset the mcu
void mcu_init(void);

//port manipulation macros for PIC.

#define IO_SET(port, bits)	port |= (bits)			//set bits on port
#define IO_CLR(port, bits)	port &=~(bits)			//clear bits on port
#define IO_FLP(port, bits)	port ^= (bits)			//flip bits on port

#define IO_GET(port, bits)	((port) & (bits))		//return bits on port

#define IO_OUT(ddr, bits)	ddr &=~(bits)			//set bits as output
#define IO_IN(ddr, bits)	ddr |= (bits)			//set bits as input

#ifndef NOP
	#define NOP()			asm("nop")				//nop()
#endif
#define NOP2()				{NOP(); NOP();}
#define NOP4()				{NOP2(); NOP2();}
#define NOP8()				{NOP4(); NOP4();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP24()				{NOP16(); NOP8();}
#define NOP32()				{NOP16(); NOP16();}
#define NOP40()				{NOP32(); NOP8();}
#define NOP64()				{NOP32(); NOP32();}

#define sleep()				asm("sleep")			//put the mcu into sleep

#define F_CPU				(16000000ul/4)			//cpu runs at 1Mhz -> Fxtal = 4Mhz

//data types
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;

//void (*mcu_reset)(void) = 0x0000; 				//jump to 0x0000 -> software reset

#ifndef ei
	#define ei()			{GIE=1;}				//enable interrupt
#endif

#ifndef di
	#define di()			{GIE=0;}				//disable interrupt
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

//bits definitions
//8-bit unions
typedef union {
    struct {
	unsigned char B0:1;
	unsigned char B1:1;
	unsigned char B2:1;
	unsigned char B3:1;
	unsigned char B4:1;
	unsigned char B5:1;
	unsigned char B6:1;
	unsigned char B7:1;
    };
    struct {
	unsigned char PIN0:1;
	unsigned char PIN1:1;
	unsigned char PIN2:1;
	unsigned char PIN3:1;
	unsigned char PIN4:1;
	unsigned char PIN5:1;
	unsigned char PIN6:1;
	unsigned char PIN7:1;
    };
} BIT8_TypeDef;

//16-bit unions
typedef union {
    struct {
	unsigned char B0:1;
	unsigned char B1:1;
	unsigned char B2:1;
	unsigned char B3:1;
	unsigned char B4:1;
	unsigned char B5:1;
	unsigned char B6:1;
	unsigned char B7:1;
	unsigned char B8:1;
	unsigned char B9:1;
	unsigned char B10:1;
	unsigned char B11:1;
	unsigned char B12:1;
	unsigned char B13:1;
	unsigned char B14:1;
	unsigned char B15:1;
    };
    struct {
	unsigned char PIN0:1;
	unsigned char PIN1:1;
	unsigned char PIN2:1;
	unsigned char PIN3:1;
	unsigned char PIN4:1;
	unsigned char PIN5:1;
	unsigned char PIN6:1;
	unsigned char PIN7:1;
	unsigned char PIN8:1;
	unsigned char PIN9:1;
	unsigned char PIN10:1;
	unsigned char PIN11:1;
	unsigned char PIN12:1;
	unsigned char PIN13:1;
	unsigned char PIN14:1;
	unsigned char PIN15:1;
    };
} BIT16_TypeDef;

//32-bit unions
typedef union {
    struct {
	unsigned char B0:1;
	unsigned char B1:1;
	unsigned char B2:1;
	unsigned char B3:1;
	unsigned char B4:1;
	unsigned char B5:1;
	unsigned char B6:1;
	unsigned char B7:1;
	unsigned char B8:1;
	unsigned char B9:1;
	unsigned char B10:1;
	unsigned char B11:1;
	unsigned char B12:1;
	unsigned char B13:1;
	unsigned char B14:1;
	unsigned char B15:1;
	unsigned char B16:1;
	unsigned char B17:1;
	unsigned char B18:1;
	unsigned char B19:1;
	unsigned char B20:1;
	unsigned char B21:1;
	unsigned char B22:1;
	unsigned char B23:1;
	unsigned char B24:1;
	unsigned char B25:1;
	unsigned char B26:1;
	unsigned char B27:1;
	unsigned char B28:1;
	unsigned char B29:1;
	unsigned char B30:1;
	unsigned char B31:1;
    };
    struct {
	unsigned char PIN0:1;
	unsigned char PIN1:1;
	unsigned char PIN2:1;
	unsigned char PIN3:1;
	unsigned char PIN4:1;
	unsigned char PIN5:1;
	unsigned char PIN6:1;
	unsigned char PIN7:1;
	unsigned char PIN8:1;
	unsigned char PIN9:1;
	unsigned char PIN10:1;
	unsigned char PIN11:1;
	unsigned char PIN12:1;
	unsigned char PIN13:1;
	unsigned char PIN14:1;
	unsigned char PIN15:1;
	unsigned char PIN16:1;
	unsigned char PIN17:1;
	unsigned char PIN18:1;
	unsigned char PIN19:1;
	unsigned char PIN20:1;
	unsigned char PIN21:1;
	unsigned char PIN22:1;
	unsigned char PIN23:1;
	unsigned char PIN24:1;
	unsigned char PIN25:1;
	unsigned char PIN26:1;
	unsigned char PIN27:1;
	unsigned char PIN28:1;
	unsigned char PIN29:1;
	unsigned char PIN30:1;
	unsigned char PIN31:1;
    };
} BIT32_TypeDef;

#if defined(LAT_USED)
#define GPIOA			((BIT8_TypeDef *) &LATA)
#define GPIOB			((BIT8_TypeDef *) &LATB)
#define GPIOC			((BIT8_TypeDef *) &LATC)
#define GPIOD			((BIT8_TypeDef *) &LATD)
#define GPIOE			((BIT8_TypeDef *) &LATE)
#define GPIOF			((BIT8_TypeDef *) &LATF)
#define GPIOG			((BIT8_TypeDef *) &LATG)
#define GPIOH			((BIT8_TypeDef *) &LATH)
#else
#define GPIOA			((BIT8_TypeDef *) &PORTA)
#define GPIOB			((BIT8_TypeDef *) &PORTB)
#define GPIOC			((BIT8_TypeDef *) &PORTC)
#define GPIOD			((BIT8_TypeDef *) &PORTD)
#define GPIOE			((BIT8_TypeDef *) &PORTE)
#define GPIOF			((BIT8_TypeDef *) &PORTF)
#define GPIOG			((BIT8_TypeDef *) &PORTG)
#define GPIOH			((BIT8_TypeDef *) &PORTH)
#endif


#endif //config_h_
