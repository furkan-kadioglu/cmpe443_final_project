#include "Signal.h"
#include "Timer.h"

uint8_t TURN_ON = 0;
uint32_t TURNING_MASK;
GPIO_TypeDef* TURNING_PORT;

static uint32_t milisecond_counter = 0;

void Signal_Init(){
	IOCON_RIGHT_SIGNAL &= ~7;
	IOCON_LEFT_SIGNAL &= ~7;
	IOCON_FORWARD_SIGNAL &= ~7;
	IOCON_BACK_SIGNAL &= ~7;

	NVIC_SetPriority(TIMER1_IRQn,5);
	
	RIGHT_SIGNAL_PORT->DIR 		|= RIGHT_SIGNAL_MASK;
	LEFT_SIGNAL_PORT->DIR 		|= LEFT_SIGNAL_MASK;
	FORWARD_SIGNAL_PORT->DIR 	|= FORWARD_SIGNAL_MASK;
	BACK_SIGNAL_PORT->DIR 		|= BACK_SIGNAL_MASK;
	
	RIGHT_SIGNAL_PORT->CLR 		|= RIGHT_SIGNAL_MASK;
	LEFT_SIGNAL_PORT->CLR 		|= LEFT_SIGNAL_MASK;
	FORWARD_SIGNAL_PORT->CLR 	|= FORWARD_SIGNAL_MASK;
	BACK_SIGNAL_PORT->CLR 		|= BACK_SIGNAL_MASK;
}

void Start_Signal(GPIO_TypeDef* PORT, uint32_t MASK){
	TIMER1->TCR |= 2;
	TIMER1->TCR &= ~1;
	
	TURNING_PORT = PORT;
	TURNING_MASK = MASK;
	
	NVIC_EnableIRQ(TIMER1_IRQn);
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	TIMER1->MCR |= 8;
	
	TIMER1->TCR &= ~2;
	TIMER1->TCR |=  1;
	
	TURNING_PORT->SET |= TURNING_MASK;
	TURN_ON = 1;
	
}
void Finish_Signal(){
	
	RIGHT_SIGNAL_PORT->CLR 	|= TURNING_MASK;
	LEFT_SIGNAL_PORT->CLR 	|= TURNING_MASK;
	
	NVIC_DisableIRQ(TIMER1_IRQn);
	TIMER1->MCR &= ~8;
	TURN_ON = 0;
}

void TIMER1_IRQHandler() {
	TIMER1->IR |= 2;
	
	milisecond_counter ++;
	if(milisecond_counter == 3){
		
		if(TURN_ON){
			TURNING_PORT->CLR |= TURNING_MASK;
			TURN_ON = 0;
		}
		else {
			TURNING_PORT->SET |= TURNING_MASK;
			TURN_ON = 1;
		}
		milisecond_counter = 0;
	}
	
}
