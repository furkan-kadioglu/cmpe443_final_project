#include "MOTOR.h"
#include "GPIO.h"

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
	
	PWM_MOTOR->MCR |= 2;
	
	PWM_MOTOR->LER |= 1 << 0;
	
	PWM_MOTOR->TCR = (1 << 0 | 1 << 3);
	
	SET_MOTOR_POWER(0, 0);
	
	MOTOR_DRIVER_IN1_PORT->DIR |= MOTOR_DRIVER_IN1_MASK;
	MOTOR_DRIVER_IN2_PORT->DIR |= MOTOR_DRIVER_IN2_MASK;
	MOTOR_DRIVER_IN3_PORT->DIR |= MOTOR_DRIVER_IN3_MASK;
	MOTOR_DRIVER_IN4_PORT->DIR |= MOTOR_DRIVER_IN4_MASK;
	
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

void PWM0_IRQHandler(){
	
	PWM_MOTOR->IR |= 1;
	NUMBER_OF_TURN += 1;
	
	if(NUMBER_OF_TURN >= NUMBER_OF_CYCLE_PER_DEGREE * DEGREE_OF_TURN){
		// Turn off interrupt
		PWM_MOTOR->MCR &= ~1;
		NVIC_DisableIRQ(PWM0_IRQn);
		
		SET_MOTOR_POWER(0, 0);
		
		Finish_Signal();
		NUMBER_OF_TURN = 0;
	}
}
