#include "TEST.h"
#define DIVIDER 1.2

enum AUTO_TURNING_MODES {R, L, S};
uint8_t AUTO_TURNING_MODE = S;

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
				Ultrasonic_Start_Trigger_Timer();
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
				AUTO_TURNING_MODE = S;
				START();
			}

			Clear_serialBuffer();
		}
	}
	if(race_start){
		
		if(ultrasonicAvailable){
			ultrasonicAvailable = 0;
			
			// Noise Elimination - Exponential Weighted Average
			/*
			if(!previousDistance)
				previousDistance = ultrasonicSensorDistance;
			ultrasonicSensorDistance = 0.9 * previousDistance + 0.1 * ultrasonicSensorDistance;
			*/
			 
			/* CONTINOUS // 1-sensor  */
			
			// Duvar devirmesin diye ikinci sensor 
			if(ultrasonicSensorDistance2 < 250000)
			{
				SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, REACTION(ultrasonicSensorDistance2/10000));
				AUTO_TURNING_MODE = R;
			}
			
			// 24 --- 26
			else if(SPECIFIED_DISTANCE-10000 < (int32_t)ultrasonicSensorDistance \
				&& SPECIFIED_DISTANCE+10000 > (int32_t)ultrasonicSensorDistance)
			{	
				SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, MOTOR_POWER_IN_PERCENT);
				AUTO_TURNING_MODE = S;
			}
				
			// 0 --- 24
			else if(SPECIFIED_DISTANCE > (int32_t)ultrasonicSensorDistance )
			{
				SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, REACTION(ultrasonicSensorDistance/10000));
				AUTO_TURNING_MODE = R;
			}
			
			// 26 --- 50
			else if(2*SPECIFIED_DISTANCE > (int32_t)ultrasonicSensorDistance)
			{	
				SET_MOTOR_POWER(REACTION((2*SPECIFIED_DISTANCE - ultrasonicSensorDistance)/10000), MOTOR_POWER_IN_PERCENT);
				AUTO_TURNING_MODE = L;
			}
			
			// Farazi mode  50+
			else
			{	
					if(AUTO_TURNING_MODE == L)
						SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, MOTOR_POWER_IN_PERCENT /4);
					
					else
						SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT /4, MOTOR_POWER_IN_PERCENT);
			}
			
			 
			/* CONTINOUS // 2-sensor 
			//if(!previousDistance2)
			//	previousDistance2 = ultrasonicSensorDistance2;
			//ultrasonicSensorDistance2 = 0.9 * previousDistance2 + 0.1 * ultrasonicSensorDistance2;
			
			if(ultrasonicSensorDistance2 < 1000000){
				cosTheta = ultrasonicSensorDistance / pow(pow(ultrasonicSensorDistance,2) + pow(ultrasonicSensorDistance2,2), 0.5);
				SET_MOTOR_POWER(MOTOR_POWER_IN_PERCENT, (40 / (90.001 - (acos(cosTheta)*180/PI))));
			}
			else
				SET_MOTOR_POWER(REACTION(50 - (ultrasonicSensorDistance/10000)), MOTOR_POWER_IN_PERCENT);
		
			previousDistance2 = ultrasonicSensorDistance2;
			previousDistance = ultrasonicSensorDistance;
			*/ 
			
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
