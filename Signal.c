#include "Signal.h"
#include "Timer.h"

uint8_t TURN_ON;
uint32_t TURNING_MASK;
GPIO_TypeDef* TURNING_PORT;

void Signal_Init(){
	//Turn on Timer1.
	PCONP |= (1<<2);
	
	//Change the mode of Timer1 to Timer Mode.
	TIMER1->CTCR &= ~3;
	
	TIMER1->MCR |= 3;
	
	TIMER1->TCR &= ~(1 << 0);
	
	TIMER1->TCR |= (1 << 1);
	
	//Change PR Register value for 1 microsecond incrementing
	TIMER1->PR = 59;
	
	//2 blinks in a second
	TIMER1->MR0 = 500000;
	
	NVIC_SetPriority(TIMER1_IRQn,5);
	
	RIGHT_SIGNAL_PORT->DIR |= RIGHT_SIGNAL_MASK;
	LEFT_SIGNAL_PORT->DIR |= LEFT_SIGNAL_MASK;
	FORWARD_SIGNAL_PORT->DIR |= FORWARD_SIGNAL_MASK;
	BACK_SIGNAL_PORT->DIR |= BACK_SIGNAL_MASK;
}

void Start_Signal(GPIO_TypeDef* PORT, uint32_t MASK){
	TIMER1->TCR |= 2;
	
	TURNING_PORT = PORT;
	TURNING_MASK = MASK;
	
	TURNING_PORT->SET |= TURNING_MASK;
	TURN_ON = 1;
	
	NVIC_EnableIRQ(TIMER1_IRQn);
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	
	
	TIMER1->TCR &= ~2;
	TIMER1->TCR |=  1;
	
}
void Finish_Signal(){
	
	RIGHT_SIGNAL_PORT->CLR |= TURNING_MASK;
	LEFT_SIGNAL_PORT->CLR |= TURNING_MASK;
	
	NVIC_DisableIRQ(TIMER1_IRQn);
	TIMER1->TCR &= ~1;
}

void TIMER1_IRQHandler() {
	TIMER1->IR |= 1;
	
	if(TURN_ON){
		TURNING_PORT->CLR |= TURNING_MASK;
	}
	else {
		TURNING_PORT->SET |= TURNING_MASK;
	}
}
