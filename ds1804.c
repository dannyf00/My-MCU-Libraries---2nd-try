#include <regx51.h>
#include "gpio.h"
#include "ds1804.h"					//we use ds1804

void ds1804_init(void) {
}

void ds1804_inc(unsigned char steps) {
	IO_SET(DS1804_PORT, DS1804_UD);	//inc's falling edge causes wiper to increment
	while (steps--) {
		IO_SET(DS1804_PORT, DS1804_INC);	//inc high
		IO_CLR(DS1804_PORT, DS1804_INC);	//inc low - complete the falling edge
	}
}

void ds1804_dec(unsigned char steps) {
	IO_CLR(DS1804_PORT, DS1804_UD);	//inc's falling edge causes wiper to decrement
	while (steps--) {
		IO_SET(DS1804_PORT, DS1804_INC);	//inc high
		IO_CLR(DS1804_PORT, DS1804_INC);	//inc low - complete the falling edge
	}
}

