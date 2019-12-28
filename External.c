#include "External.h"
#include "Command.h"


void External_Init() {
	//Change the functionality of the push button as EINT0
	IOCON_PUSH_BUTTON &= ~(3 << 1);
	IOCON_PUSH_BUTTON |= 1;

	//Change the External interrupt mode as Edge Sensitive
	EXT->EXTMODE |= 1;

	//Change polarity of the External Interrupt as Low-active
	EXT->EXTPOLAR |= 1;
}

void EINT0_IRQHandler() {
	//Clear interrupt for EINT0
	EXT->EXTINT |= 1;

	NUMBER_OF_MOTOR_TURN ++;

	if (NUMBER_OF_MOTOR_TURN >= ENCODER_PIN) {
		NUMBER_OF_TURN ++;
		NUMBER_OF_MOTOR_TURN = 0;
		
		if (NUMBER_OF_TURN >= NECESSARY_NUMBER_OF_TURN) {
			STOP();
			NUMBER_OF_TURN = 0; 
		}
	}
}
