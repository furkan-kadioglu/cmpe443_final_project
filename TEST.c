#include "TEST.h"


// LAB_9 Demo
void Ultrasonic_Test(){
	__WFI();
	if(ultrasonicAvailable){
		ultrasonicAvailable = 0;
		LED1_Off();
		LED2_Off();
		LED3_Off();
		LED4_Off();
			
		
		if(ultrasonicSensorDistance < 300000)	LED1_On();
		
		if(ultrasonicSensorDistance < 200000)	LED2_On();
		
		if(ultrasonicSensorDistance < 120000)	LED3_On();
		
		if(ultrasonicSensorDistance < 70000)	LED4_On();
		
	}
}

// LAB_10 Demo
void Potentiometer_Test(){
	__WFI();
	LED1_On();
	LED2_On();
	LED3_Off();
	LED4_Off();
	if(Potentiometer_Last > 0xC00)	LED2_Off();
	
	if(Potentiometer_Last > 0xD00)	LED1_Off();
	
	if(Potentiometer_Last < 0xA00)	LED3_On();
	
	if(Potentiometer_Last < 0x800)	LED4_On();
	
}

// LAB_10 Demo
void LDR_Test(uint32_t LDR_value){
	__WFI();
	LED1_On();
	LED2_On();
	LED3_Off();
	LED4_Off();
	
	if(LDR_value > 0xC00)	LED2_Off();

	if(LDR_value > 0xD00)	LED1_Off();
	
	if(LDR_value < 0xA00)	LED3_On();
	
	if(LDR_value < 0x800)	LED4_On();
	
}

// COMMANDS & SIGNAL TEST
void Command_Test(){
	if(Joystick_Center_Pressed()) STOP();
	
	if(Joystick_Down_Pressed()) 	BACK();
	
	if(Joystick_Up_Pressed())			FORWARD();
	
	if(Joystick_Right_Pressed())	RIGHT();
	
	if(Joystick_Left_Pressed())		LEFT();
}
