#include "External.h"
#include "MOTOR.h" 

void External_Init() {
	//Change the functionality of the push button as EINT0
	IOCON_PUSH_BUTTON &= ~(3 << 1);
	IOCON_PUSH_BUTTON |= 1;
	
	//Change the External interrupt mode as Edge Sensitive
	EXT->EXTMODE |= 1;
	
	//Change polarity of the External Interrupt as Low-active
	EXT->EXTPOLAR |= 1;
	
	//Enable interrupt for EINT0_IRQn
	NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_ClearPendingIRQ(EINT0_IRQn);
}

void EINT0_IRQHandler() {
	//Clear interrupt for EINT0
	EXT->EXTINT |= 1;
	
	NUMBER_OF_MOTOR_TURN ++;
	if(NUMBER_OF_MOTOR_TURN == 0){
		START_TC = PWM_MOTOR->TC;
	}
	
	if (NUMBER_OF_MOTOR_TURN == ENCODER_PIN){
		NUMBER_OF_MOTOR_TURN = 0;
		TURN_MICROSECOND = (PWM_MOTOR->TC - START_TC) / 6;
	}
}