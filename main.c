#include "TEST.h"
#define light_threshold 450

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
				START();
				Ultrasonic_Start_Trigger_Timer();
			}

			Clear_serialBuffer();
		}
	}
	if(race_start){
		
		if(ultrasonicAvailable){
			ultrasonicAvailable = 0;
			
			// Noise Elimination - Exponential Weighted Average
			if(!previousDistance)
				previousDistance = ultrasonicSensorDistance;
			ultrasonicSensorDistance = 0.9 * previousDistance + 0.1 * ultrasonicSensorDistance;
			
			/* DISCRETE // 1-sensor // Constant specfied range // OPTION --1--
			if(ultrasonicSensorDistance > SPECIFIED_DISTANCE + level2)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE - REACTION, AUTO_DUTY_CYCLE);
			
			else if(ultrasonicSensorDistance > SPECIFIED_DISTANCE + level1)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE - REACTION/2, AUTO_DUTY_CYCLE);
			
			if(ultrasonicSensorDistance < SPECIFIED_DISTANCE - level2)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE, AUTO_DUTY_CYCLE - REACTION);
			
			else if(ultrasonicSensorDistance < SPECIFIED_DISTANCE - level1)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE, AUTO_DUTY_CYCLE - REACTION/2);
			
			*/
			
			/* DISCRETE // 1-sensor // Dynamic specfied range // OPTION --2--  
			if(ultrasonicSensorDistance > previousDistance + level2)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE - REACTION, AUTO_DUTY_CYCLE);
			
			else if(ultrasonicSensorDistance > previousDistance + level1)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE - REACTION/2, AUTO_DUTY_CYCLE);
			
			if(ultrasonicSensorDistance < previousDistance - level2)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE, AUTO_DUTY_CYCLE - REACTION);
			
			else if(ultrasonicSensorDistance < previousDistance - level1)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE, AUTO_DUTY_CYCLE - REACTION/2);
			*/
			
			/* CONTINOUS // 1-sensor // Constant specfied range // OPTION --3-- 
			float cosTheta = (SPECIFIED_DISTANCE - ultrasonicSensorDistance) / 10.0;
			if(cosTheta > 0)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE, AUTO_DUTY_CYCLE * (1 - cosTheta));
			else
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE * (1 + cosTheta), AUTO_DUTY_CYCLE);
			*/
			 
			/* CONTINOUS // 1-sensor // Dynamic specfied range // OPTION --4-- 
			float cosTheta = (previousDistance - ultrasonicSensorDistance) / 10.0;
			if(cosTheta > 0)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE, AUTO_DUTY_CYCLE * (1 - cosTheta));
			else
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE * (1 + cosTheta), AUTO_DUTY_CYCLE);
			 */
			 
			/* CONTINOUS // 2-sensor  // OPTION --5-- 
			float cosTheta = ultrasonicSensorDistance / pow(pow(ultrasonicSensorDistance,2) + pow(distance2,2), 0.5);
			if(cosTheta > 0)
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE, AUTO_DUTY_CYCLE * (1 - cosTheta));
			else
				SET_MOTOR_POWER(AUTO_DUTY_CYCLE * (1 + cosTheta), AUTO_DUTY_CYCLE);
			 */
			 
			previousDistance = ultrasonicSensorDistance;
		}
	}

	if(ADC_Available){
		
		ADC_Available = 0;
		
		// Potentiometer - Motor Speed
		if(MODE == TEST){
			
			MOTOR_POWER_IN_PERCENT = (Potentiometer_Last*100) / 0xFFF;
			
			if(MOTOR_ON)
				SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, MOTOR_POWER_IN_PERCENT);		
		}

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
