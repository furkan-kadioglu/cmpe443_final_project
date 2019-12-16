#include "TIMER.h"
#include "SystemStructures.h"

void TIMER_Init(){
	//Turn on Timer1.
	PCONP |= (1<<2);
	
	//Change the mode of Timer1 to Timer Mode.
	TIMER1->CTCR &= ~3;
	
	TIMER1->MCR |= (1 << 4);
	
	TIMER1->TCR &= ~(1 << 0);
	
	TIMER1->TCR |= (1 << 1);
	
	//Change PR Register value for 1 microsecond incrementing
	TIMER1->PR = 59;
	
	TIMER1->MR1 = 100000;
	TIMER1->EMR |= (3 << 6); 
	
	TIMER1->TCR &= ~2;
	TIMER1->TCR |= 1;
}
