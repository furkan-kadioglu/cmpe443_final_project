#include "TEST.h"

void init() {
	Joystick_Init(); //Actually, should be turned off at DEMO
	
	MOTOR_Init();
	TIMER_Init();
	LED_Init(); //Actually, should be turned off at DEMO
	Signal_Init();
	ADC_Init();
	ADC_Start();
	External_Init();
	
	Serial_Init();
	HM10_Init();
	
	//Ultrasonic_Init();
	// Trigger should be started at AUTO mode for the sake of power consumption
	//Ultrasonic_Start_Trigger_Timer(); 
}

void update() {
	

	__WFI();
	if(serialNewDataAvailable){
		
		serialNewDataAvailable = 0;
		if(serialBuffer[serialReceiverCurrentIndex-1] == '\n'){
			
			if(!strcmp(serialBuffer, "FORWARD\r\n")){
				Request("FORWARD\r\n");
				MOVEMENT_DIR = MOVING_FORWARD;
				FORWARD();
			}
			
			if(!strcmp(serialBuffer, "BACK\r\n")){
				Request("BACK\r\n");
				MOVEMENT_DIR = MOVING_BACKWARD;
				BACK();
			}				
			
			if(!strcmp(serialBuffer, "STOP\r\n")){
				Request("STOP\r\n");
				MOVEMENT_DIR = STOPPED;
				STOP();		
			}
			
			if(!strcmp(serialBuffer, "RIGHT\r\n")){
				Request("RIGHT\r\n");
				MOVEMENT_DIR = TURNING_RIGHT;
				RIGHT(90);
			}				
			
			if(!strcmp(serialBuffer, "LEFT\r\n")){
				Request("LEFT\r\n");
				MOVEMENT_DIR = TURNING_LEFT;
				LEFT(90);
			}
			
			if(!strcmp(serialBuffer, "AUTO\r\n")){ 
				Request("AUTO\r\n");
				AUTONOMOUS();
			}
			
			if(!strcmp(serialBuffer, "TEST\r\n")){
				Request("TEST\r\n");
				TESTING();
			}
			
			if(!strcmp(serialBuffer, "STATUS\r\n")){
				Request("STATUS\r\n");
				STATUS();
			}
			
			Clear_serialBuffer();
		}
	}
	if(ADC_Available){
		// Potentiometer - Motor Speed
		MOTOR_POWER_IN_PERCENT = (Potentiometer_Last*100) / 0xFFF;
		SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, MOTOR_POWER_IN_PERCENT);
		
		// LDR - Start/Stop
		if(MODE == TEST){
			if(MOVEMENT_DIR != STOPPED){
				if(isStoppedForLight && LDR1_Last < 300 && LDR2_Last < 300){
					isStoppedForLight = 0;
					if(MOVEMENT_DIR == MOVING_FORWARD) {
						FORWARD();
					}else if(MOVEMENT_DIR == MOVING_BACKWARD) {
						BACK();
					}else if(MOVEMENT_DIR == TURNING_RIGHT){
						RIGHT(5);
					}else if(MOVEMENT_DIR == TURNING_LEFT){
						LEFT(5);
					}
				}
				if(!isStoppedForLight && (LDR1_Last > 300 || LDR2_Last > 300)){
					isStoppedForLight = 1;
					STOP();
				}
 			}
		}else{
			if(MOVEMENT_DIR != STOPPED){
				if(LDR1_Last > 300 || LDR2_Last > 300){
					FINISH();
					MOVEMENT_DIR = STOPPED;
				}
			}
		}
	}
	
	
}
 
int main() {
    init();
 
    while(1) {
        update();
    }
}
