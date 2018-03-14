#include "fifo.h"						//we use fifo

//hardware configuration
//end hardware configuration

//global defines

//initialize buffer
FIFOSIZE_T fifo_init(FIFO_TypeDef *fifo, uint8_t *buffer, FIFOSIZE_T size) {
	fifo->start = 0;
	fifo->end = 0;
	fifo->buffer = buffer;
	fifo->size = size;
	return size;
}

//reset fifo -> all data is lost and fifo becomes empty
FIFOSIZE_T fifo_reset(FIFO_TypeDef *fifo) {
	fifo->start = fifo->end = 0;
	return fifo->size;
}
	
//advance the end
FIFOSIZE_T fifo_adv(FIFO_TypeDef *fifo, FIFOSIZE_T index) {
	if (++index == fifo->size) 	index = 0;
	return index;
}

//write data to fifo
uint8_t fifo_put(FIFO_TypeDef *fifo, uint8_t dat) {
	fifo->buffer[fifo->end]=dat;			//put data to fifo
	fifo->end = fifo_adv(fifo, fifo->end);	//advance end point
	return dat;
}

//get data from fifo
uint8_t fifo_get(FIFO_TypeDef *fifo) {
	uint8_t dat = fifo->buffer[fifo->start];	//read the starting data point
	fifo->start = fifo_adv(fifo, fifo->start);	//advance the startning point
	return dat;
}

//if fifo is full
uint8_t fifo_full(FIFO_TypeDef *fifo) {
	return fifo_adv(fifo, fifo->end) == fifo->start;
}

//if fifo is empty
uint8_t fifo_empty(FIFO_TypeDef *fifo) {
	return fifo->start == fifo->end;
}
