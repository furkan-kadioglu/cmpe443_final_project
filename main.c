#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"
#include "MOTOR.h"
#include "Joystick.h"
#include "Ultrasonic.h"



void init() {
	MOTOR_Init();
	Ultrasonic_Init();
	Ultrasonic_Start_Trigger_Timer();
	

}

void update() {

	
}
 
int main() {
    init();
 
    while(1) {
        update();
    }
}
