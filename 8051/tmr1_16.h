//initialize the timer
//prescaler not used - for compatability reasons only
//16-bit period
void tmr1_init(unsigned char prescaler, unsigned short period);

//set up the isr handler
void tmr1_act(void (*isr_ptr)(void));	//set up the isr pointer
