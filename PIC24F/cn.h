//change notification, using isr
#ifndef CN_H_INCLUDED
#define CN_H_INCLUDED

//#include <pic24.h>						//we use pic24f
//#include <stdio.h>						//we use sprintf
#include "gpio.h"

//hardware configuration
//define CNIEx to enable the corresponding cn pins
//#define CNIE0				//enable cn0 interrupt
//#define CNIE1				//enable cn1 interrupt
//#define CNIE2				//enable cn2 interrupt
//#define CNIE3				//enable cn3 interrupt
//#define CNIE4				//enable cn4 interrupt
//#define CNIE5				//enable cn5 interrupt
//#define CNIE6				//enable cn6 interrupt
//#define CNIE7				//enable cn7 interrupt
//#define CNIE8				//enable cn8 interrupt
//#define CNIE9				//enable cn9 interrupt
//#define CNIE10				//enable cn10 interrupt
//#define CNIE11				//enable cn11interrupt
//#define CNIE12				//enable cn12interrupt
//#define CNIE13				//enable cn13interrupt
//#define CNIE14				//enable cn14interrupt
//#define CNIE15				//enable cn15interrupt
//#define CNIE16				//enable cn16interrupt
//#define CNIE17				//enable cn17interrupt
//#define CNIE18				//enable cn18interrupt
//#define CNIE19				//enable cn19interrupt
//#define CNIE20				//enable cn20 interrupt
#define CNIE21				//enable cn21 interrupt
#define CNIE22				//enable cn22 interrupt
//#define CNIE23				//enable cn23 interrupt
//#define CNIE24				//enable cn24 interrupt
//#define CNIE25				//enable cn25 interrupt
//#define CNIE26				//enable cn26 interrupt
//#define CNIE27				//enable cn27 interrupt
//#define CNIE28				//enable cn28 interrupt
//#define CNIE29				//enable cn29 interrupt
//#define CNIE30				//enable cn30interrupt
//#define CNIE31				//enable cn31interrupt

//end of hardware configuration

//initialize the timer1 (16bit)
void cn_init(void);

//activate the isr handler
void cn_act(void (*isr_ptr)(void));

#endif // CN_H_INCLUDED
