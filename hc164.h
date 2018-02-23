#ifndef __HC164_H
#define __HC164_H

//hardware configuration
#define HC164_PORT			P2
#define HC164_DDR			P2
#define HC164_SCK			(1<<0)
#define HC164_SDO			(1<<1)
//end hardware configuration

void hc164_init(void);

void hc164_write(unsigned char byte_t);

#endif
