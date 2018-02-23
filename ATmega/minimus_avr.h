//header file for minimus avr (at90usb162)

//key minimus avr v1.0 specification
//LED_A/LED_BLUE on PD5
//LED_B/LED_RED on PD6
//HWB button on PD7
//crystal: 16Mhz
//CLKDIV set at 1:8x
#define LED_PORT		PORTD
#define LED_DDR			DDRD
#define LED_A			(1<<5)				//pd5 for the blue led
#define LED_BLUE		LED_A
#define LED_RED			LED_B
#define LED_B			(1<<6)				//pd6 for the red led
#define HWB			(1<<7)				//pd7 for the hwb button

#ifdef F_CPU
	#undefine F_CPU
#endif
#define F_CPU			2000000ul			//cpu runs at 2Mhz on the minimus avr
