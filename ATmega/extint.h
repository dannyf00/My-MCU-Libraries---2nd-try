#ifndef INT_H_INCLUDED
#define INT_H_INCLUDED

/*
 */

//hardware configuration
//#define INT_0PORT		PORTD
//#define INT_0PORT_IN	PIND
//#define INT_0DDR		DDRD
//#define INT_0			(1<<0)
//end hardware configuration

#define INT_TRIG_LOW	0x00		//int triggered by low level
#define INT_TRIG_EDGE	0x01		//int triggered by edge
#define INT_TRIG_FALL	0x02		//int triggered by falling edge
#define INT_TRIG_RISE	0x03		//int triggered by rising edge


//----------------------for int0------------------
//int0 initialized
void int0_init(unsigned char int_trigger);

//install usr isr
void int0_act(void (*isr_ptr)(void));
//-----------------end int0------------------------

//----------------------for int1------------------
//int1 initialized
void int1_init(unsigned char int_trigger);

//install usr isr
void int1_act(void (*isr_ptr)(void));
//-----------------end int1------------------------

//----------------------for int1------------------
//int1 initialized
void int1_init(unsigned char int_trigger);

//install usr isr
void int1_act(void (*isr_ptr)(void));
//-----------------end int1------------------------

//----------------------for int2------------------
//int2 initialized
void int2_init(unsigned char int_trigger);

//install usr isr
void int2_act(void (*isr_ptr)(void));
//-----------------end int2------------------------

//----------------------for int3------------------
//int3 initialized
void int3_init(unsigned char int_trigger);

//install usr isr
void int3_act(void (*isr_ptr)(void));
//-----------------end int3------------------------

//----------------------for int4------------------
//int4 initialized
void int4_init(unsigned char int_trigger);

//install usr isr
void int4_act(void (*isr_ptr)(void));
//-----------------end int4------------------------

//----------------------for int5------------------
//int5 initialized
void int5_init(unsigned char int_trigger);

//install usr isr
void int5_act(void (*isr_ptr)(void));
//-----------------end int5------------------------

//----------------------for int6------------------
//int6 initialized
void int6_init(unsigned char int_trigger);

//install usr isr
void int6_act(void (*isr_ptr)(void));
//-----------------end int6------------------------

//----------------------for int7------------------
//int7 initialized
void int7_init(unsigned char int_trigger);

//install usr isr
void int7_act(void (*isr_ptr)(void));
//-----------------end int7------------------------

#endif
