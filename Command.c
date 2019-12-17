#include "Command.h"

void FORWARD(){
	
	// Set Motor
	MOTOR_DRIVER_IN1_PORT->SET |= MOTOR_DRIVER_IN1_MASK;
	MOTOR_DRIVER_IN2_PORT->CLR |= MOTOR_DRIVER_IN2_MASK;
	MOTOR_DRIVER_IN3_PORT->SET |= MOTOR_DRIVER_IN3_MASK;
	MOTOR_DRIVER_IN4_PORT->CLR |= MOTOR_DRIVER_IN4_MASK;
	SET_MOTOR_POWER(MAX_MOTOR_DUTY_CYCLE * MOTOR_POWER_IN_PERCENT, MAX_MOTOR_DUTY_CYCLE * MOTOR_POWER_IN_PERCENT);
	
	// Set Signal 
	BACK_SIGNAL_PORT->CLR |= BACK_SIGNAL_MASK;
	FORWARD_SIGNAL_PORT->SET |= FORWARD_SIGNAL_MASK;
	
}

void BACK (){
	// Set Motor
	MOTOR_DRIVER_IN1_PORT->CLR |= MOTOR_DRIVER_IN1_MASK;
	MOTOR_DRIVER_IN2_PORT->SET |= MOTOR_DRIVER_IN2_MASK;
	MOTOR_DRIVER_IN3_PORT->CLR |= MOTOR_DRIVER_IN3_MASK;
	MOTOR_DRIVER_IN4_PORT->SET |= MOTOR_DRIVER_IN4_MASK;
	SET_MOTOR_POWER(MAX_MOTOR_DUTY_CYCLE * MOTOR_POWER_IN_PERCENT, MAX_MOTOR_DUTY_CYCLE * MOTOR_POWER_IN_PERCENT);
	
	// Set Signal 
	BACK_SIGNAL_PORT->SET |= BACK_SIGNAL_MASK;
	FORWARD_SIGNAL_PORT->CLR |= FORWARD_SIGNAL_MASK;
}

void STOP(){
	SET_MOTOR_POWER(0, 0);
	BACK_SIGNAL_PORT->CLR |= BACK_SIGNAL_MASK;
	FORWARD_SIGNAL_PORT->CLR |= FORWARD_SIGNAL_MASK;
}

void RIGHT(uint32_t DEGREE){
	
	// Set Interrupt for 90 degrees
	NVIC_EnableIRQ(PWM0_IRQn);
	NVIC_ClearPendingIRQ(PWM0_IRQn);
	PWM_MOTOR->MCR |= 1;
	DEGREE_OF_TURN = DEGREE;
	
	// Set Motor
	MOTOR_DRIVER_IN1_PORT->CLR |= MOTOR_DRIVER_IN1_MASK;
	MOTOR_DRIVER_IN2_PORT->SET |= MOTOR_DRIVER_IN2_MASK;
	MOTOR_DRIVER_IN3_PORT->SET |= MOTOR_DRIVER_IN3_MASK;
	MOTOR_DRIVER_IN4_PORT->CLR |= MOTOR_DRIVER_IN4_MASK;
	SET_MOTOR_POWER(MAX_MOTOR_DUTY_CYCLE * MOTOR_POWER_IN_PERCENT, MAX_MOTOR_DUTY_CYCLE * MOTOR_POWER_IN_PERCENT);
	
	// Set Signal 
	BACK_SIGNAL_PORT->CLR |= BACK_SIGNAL_MASK;
	FORWARD_SIGNAL_PORT->CLR |= FORWARD_SIGNAL_MASK;
	Start_Signal(RIGHT_SIGNAL_PORT, RIGHT_SIGNAL_MASK);
	
}

void LEFT(uint32_t DEGREE){
	
	// Set Interrupt for 90 degrees
	NVIC_EnableIRQ(PWM0_IRQn);
	NVIC_ClearPendingIRQ(PWM0_IRQn);
	PWM_MOTOR->MCR |= 1;
	DEGREE_OF_TURN = DEGREE;
	
	// Set Motor
	MOTOR_DRIVER_IN1_PORT->SET |= MOTOR_DRIVER_IN1_MASK;
	MOTOR_DRIVER_IN2_PORT->CLR |= MOTOR_DRIVER_IN2_MASK;
	MOTOR_DRIVER_IN3_PORT->CLR |= MOTOR_DRIVER_IN3_MASK;
	MOTOR_DRIVER_IN4_PORT->SET |= MOTOR_DRIVER_IN4_MASK;
	SET_MOTOR_POWER(MAX_MOTOR_DUTY_CYCLE * MOTOR_POWER_IN_PERCENT, MAX_MOTOR_DUTY_CYCLE * MOTOR_POWER_IN_PERCENT);
	
	// Set Signal 
	BACK_SIGNAL_PORT->CLR |= BACK_SIGNAL_MASK;
	FORWARD_SIGNAL_PORT->CLR |= FORWARD_SIGNAL_MASK;
	Start_Signal(LEFT_SIGNAL_PORT, LEFT_SIGNAL_MASK);
	
}

void AUTONOMOUS (void){
	MODE = AUTO;
}
void TESTING (void){
	MODE = TEST;
}

void FINISH(){
}