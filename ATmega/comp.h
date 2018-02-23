#ifndef COMP_H_INCLUDED
#define COMP_H_INCLUDED

//header file for attiny2313 analog comparator


//hardware configuration
//end hardware configuration

//reset the comparator
void comp_init(void);

//install usr isr
void comp_act(void (*isr_ptr)(void));

#endif // COMP_H_INCLUDED
