#ifndef SHIFTR_H_INCLUDED
#define SHIFTR_H_INCLUDED

//shift register drivers for hc595 / hc164

//hardware configuration
#define SR_PORT			PORTE
#define SR_DDR			DDRE
#define SR_SCK			(1<<5)			//serial clock
#define SR_MOSI			(1<<6)			//serial data out
//comment out the following line for hc164
#define SR_LAT			(1<<7)			//serial latch. data latches out on the rising edge.
//end hardware configuration

//reset the shift register pins
void sr_init(void);

//send a byte
void sr_write(unsigned char dat);

#endif // SHIFTR_H_INCLUDED
