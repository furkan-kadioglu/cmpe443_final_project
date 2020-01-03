#include "TEST.h"

void init() {
	MOTOR_Init();
	TIMER_Init();
	Signal_Init();
	ADC_Init();
	ADC_Start();
	Motor_Speed_Sensor_Init();

	Serial_Init();
	HM10_Init();

	Ultrasonic_Init();
	Ultrasonic_Start_Trigger_Timer();
}

void update() {


	__WFI();
	if(serialNewDataAvailable){

		serialNewDataAvailable = 0;
		if(serialBuffer[serialReceiverCurrentIndex-1] == '\n'){

			if(!strcmp(serialBuffer, "FORWARD\r\n")){
				Request("FORWARD\r\n");
				
				ACTION = FORWARD_ACTION;
				if(!photon_detected)
					FORWARD();
			}

			if(!strcmp(serialBuffer, "BACK\r\n")){
				Request("BACK\r\n");
				
				ACTION = BACK_ACTION;
				if(!photon_detected)
					BACK();
			}

			if(!strcmp(serialBuffer, "STOP\r\n")){
			
				Request("STOP\r\n");
			
				ACTION = STOP_ACTION;
				if(!photon_detected)
					STOP();
				
			}

			if(!strcmp(serialBuffer, "RIGHT\r\n")){
				Request("RIGHT\r\n");
				NUMBER_OF_TURN = 0;
				
				ACTION = RIGHT_ACTION;
				if(!photon_detected)
					RIGHT();
			}

			if(!strcmp(serialBuffer, "LEFT\r\n")){
				Request("LEFT\r\n");
				NUMBER_OF_TURN = 0;
				
				ACTION = LEFT_ACTION;
				if(!photon_detected)
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
			
			if(!strcmp(serialBuffer, "START\r\n") && MODE == AUTO){
				Request("START\r\n");
				previousDistance = 0;
				START();
			}
			

			Clear_serialBuffer();
		}
	}
	if(race_start){
		
		if(ultrasonicAvailable){
			
			ultrasonicAvailable = 0;
		
			MOTOR_DRIVER_IN1_PORT->SET |= MOTOR_DRIVER_IN1_MASK;
			MOTOR_DRIVER_IN2_PORT->CLR |= MOTOR_DRIVER_IN2_MASK;
			MOTOR_DRIVER_IN3_PORT->SET |= MOTOR_DRIVER_IN3_MASK;
			MOTOR_DRIVER_IN4_PORT->CLR |= MOTOR_DRIVER_IN4_MASK;
	
			// Direct Mode
			if(ultrasonicSensorDistance2 < 250000) // Observe 25cm 
			{
				MOTOR_DRIVER_IN1_PORT->CLR |= MOTOR_DRIVER_IN1_MASK;
				MOTOR_DRIVER_IN2_PORT->SET |= MOTOR_DRIVER_IN2_MASK;
				SET_MOTOR_POWER(60, 60);
				
				AUTO_RIGHT_SIGNAL();
			}
				
			else
			{
				
				if(ultrasonicSensorDistance < 500000)
				{
					if(!previousDistance)
						previousDistance = ultrasonicSensorDistance;
					
					ultrasonicSensorDistance = 0.8 * previousDistance + 0.2 * ultrasonicSensorDistance;
				}
					
				
				// 24 --- 26
				if(SPECIFIED_DISTANCE-10000 < (int32_t)ultrasonicSensorDistance &&\
					 SPECIFIED_DISTANCE+10000 > (int32_t)ultrasonicSensorDistance )
				{
					SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, MOTOR_POWER_IN_PERCENT);
					Finish_Signal();
				}
				
					
				// 0 --- 24
				else if(SPECIFIED_DISTANCE > ultrasonicSensorDistance )
				{
					SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, REACTION(ultrasonicSensorDistance/10000));
					AUTO_RIGHT_SIGNAL();
				}
								
				
				// 26 --- 50
				else if(2*SPECIFIED_DISTANCE > ultrasonicSensorDistance )
				{
					SET_MOTOR_POWER(REACTION((2*SPECIFIED_DISTANCE - ultrasonicSensorDistance)/10000), MOTOR_POWER_IN_PERCENT);
					AUTO_LEFT_SIGNAL();
				}
				
				
				// Farazi mode 50+
				else
				{
					SET_MOTOR_POWER(15, 100);
					AUTO_LEFT_SIGNAL();
				}
					
				
				// Farazi don't overturn filter
				if(ultrasonicSensorDistance < 500000)
					previousDistance = ultrasonicSensorDistance;
			
				/*
				else 
					previousDistance = 0.9 * previousDistance + 0.1 * 500000; 
				*/
			
			}
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
			
			if(LDR1_Last_Light_Level > light_threshold || LDR2_Last_Light_Level > light_threshold){
				
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
				if(LDR1_Last_Light_Level > light_threshold || LDR2_Last_Light_Level > light_threshold){
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
