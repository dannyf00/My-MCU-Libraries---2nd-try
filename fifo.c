/* Circular buffer example, keeps one slot open */

#include "fifo.h"					//we use fifo / circular buffer

/* Opaque buffer element type.  This would be defined by the application. */

void cb_init(CircularBuffer *cb, unsigned short size, void *array) {
    cb->size  = size /*+ 1*/; /* include empty elem */
    cb->start = 0;
    cb->end   = 0;
    cb->elems = (ElemType *)array;
}

unsigned char cb_isfull(CircularBuffer *cb) {
    return (cb->end + 1) % cb->size == cb->start; }

unsigned char cb_isempty(CircularBuffer *cb) {
    return cb->end == cb->start; }

/* Write an element, overwriting oldest element if buffer is full. App can
   choose to avoid the overwrite by checking cbIsFull(). */
void cb_write(CircularBuffer *cb, ElemType elem) {
    cb->elems[cb->end] = elem;
    cb->end = (cb->end + 1) % cb->size;
    if (cb->end == cb->start)
        //cb->start = (cb->start + 1) % cb->size; /* full, overwrite */
        {
        	cb->start+=1; if (cb->start==cb->size) cb->start=0;
        }
}

/* Read oldest element. App must ensure !cbIsEmpty() first. */
ElemType cb_read(CircularBuffer *cb) {
    ElemType tmp = cb->elems[cb->start];
    //cb->start = (cb->start + 1) % cb->size;
    cb->start+=1; if (cb->start==cb->size) cb->start = 0;
    return tmp;
}

