#include "TEST.h"


void init() {
	
	MOTOR_Init();
	TIMER_Init();
	Signal_Init();
	ADC_Init();
	ADC_Start();
	External_Init();

	Serial_Init();
	HM10_Init();

	Ultrasonic_Init();
	// Trigger should be started at AUTO mode for the sake of power consumption
	Ultrasonic_Start_Trigger_Timer();
}

void update() {


	__WFI();
	if(serialNewDataAvailable){

		serialNewDataAvailable = 0;
		if(serialBuffer[serialReceiverCurrentIndex-1] == '\n'){

			if(!strcmp(serialBuffer, "FORWARD\r\n")){
				Request("FORWARD\r\n");
				FORWARD();
			}

			if(!strcmp(serialBuffer, "BACK\r\n")){
				Request("BACK\r\n");
				BACK();
			}

			if(!strcmp(serialBuffer, "STOP\r\n")){
				Request("STOP\r\n");
				STOP();
			}

			if(!strcmp(serialBuffer, "RIGHT\r\n")){
				Request("RIGHT\r\n");
				NUMBER_OF_TURN = 0;
				RIGHT();
			}

			if(!strcmp(serialBuffer, "LEFT\r\n")){
				Request("LEFT\r\n");
				NUMBER_OF_TURN = 0;
				LEFT();
			}

			if(!strcmp(serialBuffer, "AUTO\r\n")){
				Request("AUTO\r\nAUTONOMOUS\r\n");
				AUTONOMOUS();
			}

			if(!strcmp(serialBuffer, "TEST\r\n")){
				Request("TEST\r\nTESTING\r\n");
				TESTING();
			}

			if(!strcmp(serialBuffer, "STATUS\r\n")){
				STATUS();
			}
			
			if(!strcmp(serialBuffer, "START\r\n")){
				Request("START\r\n");
				START();
			}

			Clear_serialBuffer();
		}
	}

	if(ADC_Available){
		
		ADC_Available = 0;
		// Potentiometer - Motor Speed
		MOTOR_POWER_IN_PERCENT = (Potentiometer_Last*100) / 0xFFF;
		
		if(MOTOR_ON)
			SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, MOTOR_POWER_IN_PERCENT);
		

		// LDR - Start/Stop
		LDR1_Last_Light_Level = Get_LDR_Light_Level(LDR1_Last);
		LDR2_Last_Light_Level = Get_LDR_Light_Level(LDR2_Last);
		
		if(MODE == TEST){
			
			if(LDR1_Last_Light_Level > 500 || LDR2_Last_Light_Level > 500){
				
				MOTOR_ON = 0;
				SET_MOTOR_POWER(0, 0);
				
				// Turn off signals
				BACK_SIGNAL_PORT->CLR |= BACK_SIGNAL_MASK;
				FORWARD_SIGNAL_PORT->CLR |= FORWARD_SIGNAL_MASK;
				Finish_Signal();
				
				photon_detected = 1;
			}
			
			else{
				if(photon_detected){
					photon_detected = 0;
					if(ACTION == FORWARD_ACTION) FORWARD();
					if(ACTION == BACK_ACTION) 	 BACK();
					if(ACTION == RIGHT_ACTION)   RIGHT();
					if(ACTION == LEFT_ACTION) 	 LEFT();
					if(ACTION == STOP_ACTION) 	 STOP();
				}
				
			}
		}
		
		else{
			if(race_start){		
				if(LDR1_Last_Light_Level > 500 || LDR2_Last_Light_Level > 500){
					race_start = 0;
					STOP();
					FINISH();
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
