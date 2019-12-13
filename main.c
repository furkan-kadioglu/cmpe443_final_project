#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"
#include "MOTOR.h"
#include "Joystick.h"
#include "Ultrasonic.h"
#include "Led.h"
#include "Signal.h"



void init() {
	Joystick_Init();
	MOTOR_Init();
	Ultrasonic_Init();
	Ultrasonic_Start_Trigger_Timer();
	LED_Init();
	Signal_Init();

}

void update() {

	
}
 
int main() {
    init();
 
    while(1) {
        update();
    }
}
