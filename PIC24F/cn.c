//#include <pic24.h>						//we use pic24f
//#include <stdio.h>						//we use sprintf
//#include "gpio.h"
#include "cn.h"							//we use change notification

//hardware configuration
//#define CNIE1							//uncomment to enable cn1
//#define CNIE2							//uncomment to enable cn2
//define more if needed. Also check cn_init() to enable them
//end of hardware configuration

//empty handler
static void empty_handler(void) {
	//default tmr handler
}

//global variables
void (* _cn_isr_ptr)(void)=empty_handler;			//cn_ptr pointing to empty_handler by default

//cn isr
void _ISR _CNInterrupt(void) {
	_CNIF = 0;						//clear the flag
	_cn_isr_ptr();						//execute the handler
}

//initialize the timer1 (16bit)
void cn_init(void) {
	_CNIF = 0;						//clear the flag
#if defined(CNIE0)
	_CN0IE = 1;						//enable cn on the particular pin
	_CN0PUE = 1;						//enable weak pull-up
#endif
#if defined(CNIE1)
	_CN1IE = 1;							//enable cn on the particular pin
	_CN1PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE2)
	_CN2IE = 1;							//enable cn on the particular pin
	_CN2PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE3)
	_CN3IE = 1;							//enable cn on the particular pin
	_CN3PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE4)
	_CN4IE = 1;							//enable cn on the particular pin
	_CN4PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE5)
	_CN5IE = 1;							//enable cn on the particular pin
	_CN5PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE6)
	_CN6IE = 1;							//enable cn on the particular pin
	_CN6PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE7)
	_CN7IE = 1;							//enable cn on the particular pin
	_CN7PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE8)
	//_CN8IE = 1;							//enable cn on the particular pin
	//_CN8PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE9)
	//_CN9IE = 1;							//enable cn on the particular pin
	//_CN9PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE10)
	//_CN10IE = 1;							//enable cn on the particular pin
	//_CN10PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE11)
	_CN11IE = 1;							//enable cn on the particular pin
	_CN11PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE12)
	_CN12IE = 1;							//enable cn on the particular pin
	_CN12PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE13)
	_CN13IE = 1;							//enable cn on the particular pin
	_CN13PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE14)
	_CN14IE = 1;							//enable cn on the particular pin
	_CN14PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE15)
	_CN15IE = 1;							//enable cn on the particular pin
	_CN15PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE16)
	_CN16IE = 1;							//enable cn on the particular pin
	_CN16PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE17)
	//_CN17IE = 1;							//enable cn on the particular pin
	//_CN17PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE18)
	//_CN18IE = 1;							//enable cn on the particular pin
	//_CN18PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE19)
	//_CN19IE = 1;							//enable cn on the particular pin
	//_CN19PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE20)
	//_CN20IE = 1;							//enable cn on the particular pin
	//_CN20PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE21)
	_CN21IE = 1;							//enable cn on the particular pin
	_CN21PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE22)
	_CN22IE = 1;							//enable cn on the particular pin
	_CN22PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE23)
	_CN23IE = 1;							//enable cn on the particular pin
	_CN23PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE24)
	_CN24IE = 1;							//enable cn on the particular pin
	_CN24PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE25)
	//_CN25IE = 1;							//enable cn on the particular pin
	//_CN25PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE26)
	//_CN26IE = 1;							//enable cn on the particular pin
	//_CN26PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE27)
	_CN27IE = 1;							//enable cn on the particular pin
	_CN27PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE28)
	//_CN28IE = 1;							//enable cn on the particular pin
	//_CN28PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE29)
	_CN29IE = 1;							//enable cn on the particular pin
	_CN29PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE30)
	_CN30IE = 1;							//enable cn on the particular pin
	_CN30PUE = 1;							//enable weak pull-up
#endif
#if defined(CNIE31)
	//_CN31IE = 1;							//enable cn on the particular pin
	//_CN31PUE = 1;							//enable weak pull-up
#endif

	//repeat if necessary

	//install the default handler
	_cn_isr_ptr = empty_handler;

	//enable cnie
	_CNIE = 1;

}

//activate the isr handler
void cn_act(void (*isr_ptr)(void)) {
	_cn_isr_ptr=isr_ptr;			//activate the isr handler
}
