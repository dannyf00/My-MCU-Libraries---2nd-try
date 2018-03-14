#include "fifo.h"						//we use fifo

//hardware configuration
//end hardware configuration

//global defines

//initialize buffer
FIFO_CNT fifo_init(FIFO_TypeDef *fifo, uint8_t *buffer, FIFO_CNT size) {
	fifo->begin = 0;
	fifo->end = 0;
	fifo->buffer = buffer;
	fifo->size = size;
	return size;
}

//reset fifo -> all data is lost and fifo becomes empty
FIFO_CNT fifo_reset(FIFO_TypeDef *fifo) {
	fifo->begin = fifo->end = 0;
	return fifo->size;
}
	
//advance the end
FIFO_CNT fifo_adv(FIFO_TypeDef *fifo, FIFO_CNT index) {
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
	uint8_t dat = fifo->buffer[fifo->begin];	//read the begining data point
	fifo->begin = fifo_adv(fifo, fifo->begin);	//advance the beginning point
	return dat;
}

//if fifo is full
uint8_t fifo_full(FIFO_TypeDef *fifo) {
	return fifo_adv(fifo, fifo->end) == fifo->begin;
}

//if fifo is empty
uint8_t fifo_empty(FIFO_TypeDef *fifo) {
	return fifo->begin == fifo->end;
}
