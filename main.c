#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"
#include "Joystick.h"
#include "Ultrasonic.h"
#include "Led.h"
#include "Signal.h"

uint32_t i;

void init() {
	Joystick_Init();
	MOTOR_Init();
	
	// They should be called at AUTO MODE and START
	//Ultrasonic_Init();
	//Ultrasonic_Start_Trigger_Timer();
	
	LED_Init();
	Signal_Init();

}

void update() {
	
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
	
	
	
	
}
 
int main() {
    init();
 
    while(1) {
        update();
    }
}
