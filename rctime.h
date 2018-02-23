#ifndef RCTIME_H_INCLUDED
#define RCTIME_H_INCLUDED

//hardware configuration
#define RC_PORT				LATB
#define RC_PORT_IN			PORTB
#define RC_DDR				TRISB
#define RC_PIN				(1<<7)

//end hardware configuration
//initialize the module
void rctime_init(unsigned char pin);

//measure the time
unsigned short rctime_read(unsigned char pin);

#endif // RCTIME_H_INCLUDED
