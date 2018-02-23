/*
 */

#include <avr/io.h>
#include "gpio.h"
#include "ds12887.h"									//we use ds12887

//hardware configuration
//end hardware configuration

#define Pwex()          NOP8()                          //Pwel and Pweh specification (150ns minimum)

//reset the module
void rtc_init(void) {
#if defined(RTC_IRQ)
    IO_IN(RTC_PORT, RTC_IRQ);                   //irq as input
#endif

    //set up the output pins
    IO_CLR(RTC_PORT, RTC_AS | RTC_RW | RTC_DS);         //as/rw/ds idle low
    IO_SET(RTC_PORT, RTC_CS);                   //cs idles high
    IO_OUT(RTC_DDR, RTC_AS | RTC_RW | RTC_DS | RTC_CS); //as input

    //set up the address lines
    IO_IN(RTC_ADDR_DDR, RTC_ADDR);              //initialized to input

    rtc_write(0x0a, 0x20);						//turn on the rtc
}

//write a byte
void rtc_write(unsigned char addr, unsigned char dat) {
    IO_CLR(RTC_PORT, RTC_CS);   //select the chip
    IO_SET(RTC_PORT, RTC_RW | RTC_DS);  //ds/rw/as high
    IO_SET(RTC_PORT, RTC_AS);                   //as high
    RTC_ADDR_PORT = addr;                               //output the address
    IO_OUT(RTC_ADDR_DDR, RTC_ADDR);             //addr as output
    IO_CLR(RTC_PORT, RTC_AS);                   //latch the address
    Pwex();                                                             //Pwel 150ns
    IO_CLR(RTC_PORT, RTC_RW);                   //enter write mode
    RTC_ADDR_PORT = dat;                                //write the data
    Pwex();                                                             //Pwel 150ns
    IO_SET(RTC_PORT, RTC_RW);                   //write the data
    IO_SET(RTC_PORT, RTC_AS);                   //latch the whole thing
    IO_SET(RTC_PORT, RTC_CS);                   //unselect the chip
    IO_IN(RTC_ADDR_DDR, RTC_ADDR);              //adc pins default to input
    //IO_CLR(RTC_PORT, RTC_AS | RTC_RW | RTC_DS);       //as / rw / ds idle low
}

//read a byte
unsigned char rtc_read(unsigned char addr) {
    unsigned char tmp;
    IO_CLR(RTC_PORT, RTC_CS);   //select the chip
    IO_SET(RTC_PORT, RTC_RW | RTC_DS);  //read from the chip
    IO_SET(RTC_PORT, RTC_AS);
    RTC_ADDR_PORT = addr;                               //output the address
    IO_OUT(RTC_ADDR_DDR, RTC_ADDR);             //addr as output
    IO_CLR(RTC_PORT, RTC_AS);                   //addr strobe
    IO_IN(RTC_ADDR_DDR, RTC_ADDR);              //adc pins default to input
    Pwex();                                                             //Pwel 150ns
    IO_CLR(RTC_PORT, RTC_DS);                   //enter read mode
    tmp = RTC_ADDR_PORTIN;                              //read the data
    Pwex();                                                             //Pwel 150ns
    IO_SET(RTC_PORT, RTC_DS);                   //addr strobe
    IO_SET(RTC_PORT, RTC_AS);                   //addr strobe
    IO_SET(RTC_PORT, RTC_CS);                   //unselect the chip
    //IO_CLR(RTC_PORT, RTC_AS | RTC_DS | RTC_RW);       //as/ds/rw idles low for read
    return tmp;
}

