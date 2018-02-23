#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

/* Circular buffer example, keeps one slot open */

#include <stdio.h>
#include "fifo.h"					//we use fifo / circular buffer

/* Opaque buffer element type.  This would be defined by the application. */
typedef unsigned short ElemType;

/* Circular buffer object */
typedef struct {
    unsigned short         size;   /* maximum number of elements           */
    unsigned short         start;  /* index of oldest element              */
    unsigned short         end;    /* index at which to write new element  */
    ElemType   *elems;  /* vector of elements                   */
} CircularBuffer;

//initialize the fifo
void cb_init(CircularBuffer *cb, unsigned short size, void *array);

//1 if cb is full
unsigned char cb_isfull(CircularBuffer *cb);

unsigned char cb_isempty(CircularBuffer *cb);

/* Write an element, overwriting oldest element if buffer is full. App can
   choose to avoid the overwrite by checking cbIsFull(). */
void cb_write(CircularBuffer *cb, ElemType elem);

/* Read oldest element. App must ensure !cbIsEmpty() first. */
ElemType cb_read(CircularBuffer *cb);

#endif // FIFO_H_INCLUDED
