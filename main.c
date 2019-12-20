#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"
#include "Joystick.h"
#include "Ultrasonic.h"
#include "Led.h"
#include "Signal.h"
#include "ADC.h"
#include "External.h"
#include "HM10.h"


void init() {
	Joystick_Init();
	MOTOR_Init();
	TIMER_Init();
	LED_Init();
	Signal_Init();
	ADC_Init();
	ADC_Start();
	External_Init();
	Serial_Init();
		
	HM10_Init();
	// Serial Test 1
	//Ultrasonic_Init();
	//Ultrasonic_Start_Trigger_Timer();
}

void update() {
	/*AUTO MODE TEST CASE
	if(Joystick_Center_Pressed()){
		
		FINISH();
		PCONP &= ~(1 << 22);
			

	}
	if(Joystick_Up_Pressed()){
		
			// "AUTO" 
		AUTONOMOUS();
		Ultrasonic_Init();
		
		// "START"
		FORWARD();
		Ultrasonic_Start_Trigger_Timer();
		
		
	}
	*/
	
	/* ADC TEST CASE												DONE
	__WFI();
	LED1_On();
	LED2_On();
	LED3_Off();
	LED4_Off();
	if(LDR1_Last > 0xC00){
		LED2_Off();
	}
	if(LDR1_Last > 0xD00){
		LED1_Off();
	}
	if(LDR1_Last < 0xA00){
		LED3_On();
	}
	if(LDR1_Last < 0x800){
		LED4_On();
	}
	*/
	
	/* ADC TEST CASE 2  										DONE
	__WFI();
	LED1_On();
	LED2_On();
	LED3_Off();
	LED4_Off();
	if(Potentiometer_Last > 0xC00){
		LED2_Off();
	}
	if(Potentiometer_Last > 0xD00){
		LED1_Off();
	}
	if(Potentiometer_Last < 0xA00){
		LED3_On();
	}
	if(Potentiometer_Last < 0x800){
		LED4_On();
	}
	*/
	
	/* COMMANDS & SIGNAL TEST        				DONE
	if(Joystick_Center_Pressed()){
		STOP();
	}
	if(Joystick_Down_Pressed()){
		BACK();
	}
	if(Joystick_Up_Pressed()){
		FORWARD();
	}
	if(Joystick_Right_Pressed()){
		RIGHT(90);
	}
	if(Joystick_Left_Pressed()){
		LEFT(90);
	}
	*/
	
	/* Serial Test 2
	__WFI(); 
	if(serialNewDataAvailable){
		
		serialNewDataAvailable = 0;
		serialTransmitData = serialBuffer;
		Serial_WriteData(*serialTransmitData++);
		
	}
	*/
	
	
	/* Serial Test 3*/
	__WFI();
	if(serialNewDataAvailable){
		if(!strcmp(serialBuffer, "FORWARD\r\n")){
			FORWARD();
			Clear_serialBuffer();
		}
		if(!strcmp(serialBuffer, "BACK\r\n")){
			BACK();
			Clear_serialBuffer();
		}
		if(!strcmp(serialBuffer, "STOP\r\n")){
			STOP();
			Clear_serialBuffer();
		}
		if(!strcmp(serialBuffer, "RIGHT\r\n")){
			RIGHT(90);
			Clear_serialBuffer();
		}
		if(!strcmp(serialBuffer, "LEFT\r\n")){
			LEFT(90);
			Clear_serialBuffer();
		}
	}
	
	
	
	/* Ultrasonic Test
	__WFI();
	if(ultrasonicAvailable){
		ultrasonicAvailable = 0;
		LED1_Off();
		LED2_Off();
		LED3_Off();
		LED4_Off();
			
		
		if(ultrasonicSensorDistance < 300000){
			LED1_On();
		}
		if(ultrasonicSensorDistance < 200000){
			LED2_On();
		}
		if(ultrasonicSensorDistance < 120000){
			LED3_On();
		}
		if(ultrasonicSensorDistance < 70000){
			LED4_On();
		}
	}
	*/
	
}
 
int main() {
    init();
 
    while(1) {
        update();
    }
}
