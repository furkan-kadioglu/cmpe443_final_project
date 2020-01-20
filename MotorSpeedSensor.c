#include "MotorSpeedSensor.h"
#include "Command.h"

uint32_t NUMBER_OF_TURN = 0;

void Motor_Speed_Sensor_Init(void){
	IOCON_CAPTURE |= 0x3;
	
	PWM0->CCR |= (1<<0|1<<2);
	
}

void PWM0_IRQHandler(){
	PWM0->IR |= (1<<4);
	
	NUMBER_OF_TURN ++;

	if (NUMBER_OF_TURN >= NECESSARY_NUMBER_OF_TURN) {
		STOP();
		NUMBER_OF_TURN = 0;
	}
}
