#ifndef DS12887_H_INCLUDED
#define DS12887_H_INCLUDED

/*
 */

//hardware configuration
//intel timing: MOT to GND or unconnected.
#define RTC_PORT        PORTD
#define RTC_DDR         DDRD
#define RTC_AS          (1<<0)                          //Address strobe. on falling edge
#define RTC_RW          (1<<1)                          //read/write pin. 0=write, 1=read. data latched on the rising edge
#define RTC_DS          (1<<2)                          //data strobe.
#define RTC_CS          (1<<3)                          //chip select, active low
#define RTC_IRQ         (1<<4)                          //interrupt request

#define RTC_ADDR_PORT   PORTF
#define RTC_ADDR_PORTIN PINF
#define RTC_ADDR_DDR    DDRF
#define RTC_ADDR        0xff
//end hardware configuration

void rtc_init(void);
void rtc_write(unsigned char addr, unsigned char dat);
unsigned char rtc_read(unsigned char addr);


#endif // DS12887_H_INCLUDED
