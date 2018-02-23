//header file for tmr0

//hardware configuration
//end hardware configuration

#define TMR1_ISR_CH		5			//tmr1 isr channel = 5

//tmr match-control register
#define TxMCR_ISRonMR0	(1<<0)		//interrupt on mr0
#define TxMCR_ResetonMR0	(1<<1)		//reset on mr0
#define TxMCR_StoponMR0	(1<<2)		//stop on MR0
#define TxMCR_MaskMR0	(TxMCR_ISRonMR0 | TxMCR_ResetonMR0 | TxMCR_StoponMR0)	//mr0 mask

#define TxMCR_ISRonMR1	(1<<3)		//interrupt on mr1
#define TxMCR_ResetonMR1	(1<<4)		//reset on mr1
#define TxMCR_StoponMR1	(1<<5)		//stop on MR1
#define TxMCR_MaskMR1	(TxMCR_ISRonMR1 | TxMCR_ResetonMR1 | TxMCR_StoponMR1)	//mr1 mask

#define TxMCR_ISRonMR2	(1<<6)		//interrupt on mr2
#define TxMCR_ResetonMR2	(1<<7)		//reset on mr2
#define TxMCR_StoponMR2	(1<<8)		//stop on MR2
#define TxMCR_MaskMR2	(TxMCR_ISRonMR2 | TxMCR_ResetonMR2 | TxMCR_StoponMR2)	//mr2 mask

#define TxMCR_ISRonMR3	(1<<9)		//interrupt on mr3
#define TxMCR_ResetonMR3	(1<<10)		//reset on mr3
#define TxMCR_StoponMR3	(1<<11)		//stop on MR3
#define TxMCR_MaskMR3	(TxMCR_ISRonMR3 | TxMCR_ResetonMR3 | TxMCR_StoponMR3)	//mr3 mask

//tmr interrupt flag
#define TxIR_ISRonMR0	(1<<0)		//interrupt on mr0
#define TxIR_ISRonMR1	(1<<1)		//interrupt on mr1
#define TxIR_ISRonMR2	(1<<2)		//interrupt on mr2
#define TxIR_ISRonMR3	(1<<3)		//interrupt on mr3
#define TxIR_ISRonCR0	(1<<4)		//interrupt on cr0
#define TxIR_ISRonCR1	(1<<5)		//interrupt on cr1
#define TxIR_ISRonCR2	(1<<6)		//interrupt on cr2
#define TxIR_ISRonCR3	(1<<7)		//interrupt on cr3

//prescaler definitions
#define TMR_PS_1x		0			//tmr prescaler
#define TMR_PS_2x		1			//tmr prescaler
#define TMR_PS_5x		4			//tmr prescaler
#define TMR_PS_10x		9			//tmr prescaler
#define TMR_PS_20x		19			//tmr prescaler
#define TMR_PS_50x		49			//tmr prescaler
#define TMR_PS_100x		99			//tmr prescaler
#define TMR_PS_200x		199			//tmr prescaler
#define TMR_PS_500x		499			//tmr prescaler

//period definitions
#define TMR_ms			(F_CPU / 1000 / 2)	//1ms
#define TMR_1ms			(TMR_ms * 1 - 1)	//1ms
#define TMR_2ms			(TMR_ms * 2 - 1)	//2ms
#define TMR_5ms			(TMR_ms * 5 - 1)	//5ms
#define TMR_10ms		(TMR_ms * 10 - 1)	//10ms
#define TMR_20ms		(TMR_ms * 20 - 1)	//20ms
#define TMR_50ms		(TMR_ms * 50 - 1)	//50ms
#define TMR_100ms		(TMR_ms * 100 - 1)	//100ms
#define TMR_200ms		(TMR_ms * 200 - 1)	//200ms
#define TMR_500ms		(TMR_ms * 500 - 1)	//500ms
#define TMR_1000ms		(TMR_ms * 1000 - 1)	//1000ms

void tmr1_init(unsigned long prescaler, unsigned long period);

void tmr1_act(void (*func_ptr)(void));
