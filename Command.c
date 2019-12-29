#include "Command.h"

uint32_t NUMBER_OF_TURN = 0;
uint32_t MODE = TEST;
uint32_t ACTION = STOP_ACTION;

uint8_t photon_detected = 0;
uint8_t race_start = 0; 

void Clear_Action(){
	// Reset 
	MOTOR_ON = 0;
	NUMBER_OF_TURN = 0;
	
	// Turn off interrupt
	NVIC_DisableIRQ(PWM0_IRQn);
	
	// Turn off signals
	BACK_SIGNAL_PORT->CLR |= BACK_SIGNAL_MASK;
	FORWARD_SIGNAL_PORT->CLR |= FORWARD_SIGNAL_MASK;
	Finish_Signal();
}


void FORWARD(){
	
	Clear_Action();
	
	// Set Motor
	MOTOR_DRIVER_IN1_PORT->SET |= MOTOR_DRIVER_IN1_MASK;
	MOTOR_DRIVER_IN2_PORT->CLR |= MOTOR_DRIVER_IN2_MASK;
	MOTOR_DRIVER_IN3_PORT->SET |= MOTOR_DRIVER_IN3_MASK;
	MOTOR_DRIVER_IN4_PORT->CLR |= MOTOR_DRIVER_IN4_MASK;
	MOTOR_ON = 1;
	SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, MOTOR_POWER_IN_PERCENT);

	// Set Signal
	FORWARD_SIGNAL_PORT->SET |= FORWARD_SIGNAL_MASK;

}

void BACK (){

	Clear_Action();

	// Set Motor
	MOTOR_DRIVER_IN1_PORT->CLR |= MOTOR_DRIVER_IN1_MASK;
	MOTOR_DRIVER_IN2_PORT->SET |= MOTOR_DRIVER_IN2_MASK;
	MOTOR_DRIVER_IN3_PORT->CLR |= MOTOR_DRIVER_IN3_MASK;
	MOTOR_DRIVER_IN4_PORT->SET |= MOTOR_DRIVER_IN4_MASK;
	MOTOR_ON = 1;
	SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, MOTOR_POWER_IN_PERCENT);

	// Set Signal
	BACK_SIGNAL_PORT->SET |= BACK_SIGNAL_MASK;

}

void STOP(){

	Clear_Action();
	SET_MOTOR_POWER(0, 0);
	race_start = 0;
	
}

void RIGHT(){
	
	// Set Interrupt for 90 degrees
	NVIC_EnableIRQ(PWM0_IRQn);
	NVIC_ClearPendingIRQ(PWM0_IRQn);

	// Set Motor
	MOTOR_DRIVER_IN1_PORT->CLR |= MOTOR_DRIVER_IN1_MASK;
	MOTOR_DRIVER_IN2_PORT->SET |= MOTOR_DRIVER_IN2_MASK;
	MOTOR_DRIVER_IN3_PORT->SET |= MOTOR_DRIVER_IN3_MASK;
	MOTOR_DRIVER_IN4_PORT->CLR |= MOTOR_DRIVER_IN4_MASK;
	MOTOR_ON = 1;
	SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, MOTOR_POWER_IN_PERCENT);

	// Set Signal
	Start_Signal(RIGHT_SIGNAL_PORT, RIGHT_SIGNAL_MASK);

	
	

}

void LEFT(){
	
	// Set Interrupt for 90 degrees
	NVIC_EnableIRQ(PWM0_IRQn);
	NVIC_ClearPendingIRQ(PWM0_IRQn);

	// Set Motor
	MOTOR_DRIVER_IN1_PORT->SET |= MOTOR_DRIVER_IN1_MASK;
	MOTOR_DRIVER_IN2_PORT->CLR |= MOTOR_DRIVER_IN2_MASK;
	MOTOR_DRIVER_IN3_PORT->CLR |= MOTOR_DRIVER_IN3_MASK;
	MOTOR_DRIVER_IN4_PORT->SET |= MOTOR_DRIVER_IN4_MASK;
	MOTOR_ON = 1;
	SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, MOTOR_POWER_IN_PERCENT);

	// Set Signal
	Start_Signal(LEFT_SIGNAL_PORT, LEFT_SIGNAL_MASK);


}

void START(void){
	race_start = 1;
	FORWARD(); // Optimize it!! for race
	
}

void AUTONOMOUS (void){
	MODE = AUTO;
}
void TESTING (void){
	MODE = TEST;
}

void STATUS (void) {
	sprintf(serialBuffer,
	"STATUS\r\n{\"distance\":%d,\"light_level_left\":%d,\"light_level_right\":%d,\"op_mode\":\"%s\"}\r\n",
	ultrasonicSensorDistance/1000, LDR1_Last_Light_Level, LDR2_Last_Light_Level, stringFromMode(MODE));
	Response();
}

void FINISH(void){
	STOP();
	Request("FINISH\r\n");
}
