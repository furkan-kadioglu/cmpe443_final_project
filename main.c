#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"
#include "Joystick.h"
#include "Ultrasonic.h"
#include "Led.h"
#include "Signal.h"
#include "Command.h"


void init() {
	Joystick_Init();
	MOTOR_Init();
	Ultrasonic_Init();
	Ultrasonic_Start_Trigger_Timer();
	LED_Init();
	Signal_Init();

}

void update() {
	
	if(Joystick_Center_Pressed()){
		STOP();
	}
	if(Joystick_Up_Pressed()){
		FORWARD();
	}
	if(Joystick_Down_Pressed()){
		BACK();
	}
	if(Joystick_Right_Pressed()){
		RIGHT();
	}
	if(Joystick_Left_Pressed()){
		LEFT();
	}
}
 
int main() {
    init();
 
    while(1) {
        update();
    }
}
