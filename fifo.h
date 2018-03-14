#ifndef _FIFO_H
#define _FIFO_H

#include <stdint.h>

//hardware configuration
#define FIFOSIZE_T			uint8_t		//for buffers with less than 256 elements. otherwise, use uint16/32_t
//#define FIFOCELL_T		uint8_t		//individual element of fifo
//end hardware configuration

//global defines
typedef struct {
	FIFOSIZE_T start;					//startning of buffer
	FIFOSIZE_T end;						//end point of buffer
	uint8_t  *buffer;					//buffer / FIFOCELL_T
	FIFOSIZE_T size;					//size of buffer
} FIFO_TypeDef;

//initialize buffer
FIFOSIZE_T fifo_init(FIFO_TypeDef *fifo, uint8_t *buffer, FIFOSIZE_T size);

//reset fifo -> all data is lost and fifo becomes empty
FIFOSIZE_T fifo_reset(FIFO_TypeDef *fifo);
	
//advance the end
FIFOSIZE_T fifo_adv(FIFO_TypeDef *fifo, FIFOSIZE_T index);

//write data to fifo
uint8_t fifo_put(FIFO_TypeDef *fifo, uint8_t dat);

//get data from fifo
uint8_t fifo_get(FIFO_TypeDef *fifo);

//if fifo is full
uint8_t fifo_full(FIFO_TypeDef *fifo);

//if fifo is empty
uint8_t fifo_empty(FIFO_TypeDef *fifo);
#endif
