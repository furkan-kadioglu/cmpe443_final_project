#include "Signal.h"
#include "Timer.h"

void Signal_Init(){
	//Turn on Timer1.
	PCONP |= (1<<2);
	
	//Change the mode of Timer1 to Timer Mode.
	TIMER1->CTCR &= ~3;
	
	TIMER1->TCR &= ~(1 << 0);
	
	TIMER1->TCR |= (1 << 1);
	
	//Change PR Register value for 1 microsecond incrementing
	TIMER1->PR = 59;
	
	NVIC_EnableIRQ(TIMER1_IRQn);
	
	NVIC_SetPriority(TIMER1_IRQn,5);
	
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	
	RIGHT_SIGNAL_PORT->DIR |= RIGHT_SIGNAL_MASK;
	LEFT_SIGNAL_PORT->DIR |= LEFT_SIGNAL_MASK;
	FORWARD_SIGNAL_PORT->DIR |= FORWARD_SIGNAL_MASK;
	BACK_SIGNAL_PORT->DIR |= BACK_SIGNAL_MASK;
}

void SET_Signal(GPIO_TypeDef* PORT,uint32_t MASK, uint8_t on){
	if(on){
		PORT->SET |= MASK;
	}
	else{
		PORT->CLR |= MASK;
	}
}

void TIMER1_IRQHandler() {
}
