//initialize the timer
//prescaler not used - for compatability reasons only
//8-bit period
void tmr0_init(unsigned char prescaler, unsigned char period);

//set up the isr handler
void tmr0_act(void (*isr_ptr)(void));	//set up the isr pointer
