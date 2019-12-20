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
			
			if(!strcmp(serialBuffer, "FORWARD\r\n")) FORWARD();
			
			if(!strcmp(serialBuffer, "BACK\r\n")) BACK();		
			
			if(!strcmp(serialBuffer, "STOP\r\n")) STOP();		
			
			if(!strcmp(serialBuffer, "RIGHT\r\n")) RIGHT(90);			
			
			if(!strcmp(serialBuffer, "LEFT\r\n")) LEFT(90);
			
			Clear_serialBuffer();
		}
	}
	
	
}
 
int main() {
    init();
 
    while(1) {
        update();
    }
}
