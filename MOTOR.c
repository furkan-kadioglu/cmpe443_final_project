#include "MOTOR.h"

void MOTOR_Init() {
	//Change the function of the pin in here:
	IOCON_RIGHT_MOTORS &= ~4;
	IOCON_RIGHT_MOTORS |= 3;
	IOCON_LEFT_MOTORS &= ~4;
	IOCON_LEFT_MOTORS |= 3;
	
	
	PCONP |= (1 << 5);
	
	//Enable PWM output for corresponding pin.
	PWM_MOTOR->PCR |= (3 << 13 );
	
	PWM_MOTOR->TCR = 1 << 1;
	
	PWM_MOTOR->PR = 9;
	
	//Configure MR0 register for a period of 20 ms
	PWM_MOTOR->MR0 = 120000;
	
	PWM_MOTOR->MCR = 1 << 1;;
	
	PWM_MOTOR->LER |= 1 << 0;
	
	PWM_MOTOR->TCR = (1 << 0 | 1 << 3);
	
	SET_MOTOR_POWER(0, 0);
}

void SET_MOTOR_POWER(uint32_t left, uint32_t right){
	if(left > 100) {
		left = 100;
	}
	if(right > 100) {
		right = 100;
	}
	
	//Write a formula to calculate the match register of the PWM pin.
	PWM_MOTOR->MR6 = PWM_MOTOR->MR0 / 100 * right;
	PWM_MOTOR->MR5 = PWM_MOTOR->MR0 / 100 * left;
	
	//Enable PWM Match Register Latch.
	PWM_MOTOR->LER |= (3 << 5);
}
