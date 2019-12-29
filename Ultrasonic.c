#include "Ultrasonic.h"

#define REACTION 30

uint32_t ultrasonicSensorRisingCaptureTime;
uint32_t ultrasonicSensorFallingCaptureTime;

uint32_t ultrasonicSensorDistance = 0;
uint32_t previousDistance = 0;
uint32_t distance2 = 0;

uint8_t ultrasonicSensorTriggerStart = 0;
uint8_t ultrasonicSensorCaptureRisingEdge = 0;
uint8_t  ultrasonicAvailable = 0;


uint32_t level1 = 20000;
uint32_t level2 = 30000;

void Ultrasonic_Init() {
	IOCON_TRIGGER |= 0x03;
	IOCON_ECHO |= 0x03;
	
	Ultrasonic_Trigger_Timer_Init();
	Ultrasonic_Capture_Timer_Init();
	
}

void Ultrasonic_Trigger_Timer_Init() {
	//Turn on Timer2.
	PCONP |= (1<<22);
	
	//Change the mode of Timer2 to Timer Mode.
	TIMER2->CTCR &= ~3;
	
	TIMER2->TCR &= ~(1 << 0);
	
	TIMER2->TCR |= (1 << 1);
	
	//Change PR Register value for 1 microsecond incrementing
	TIMER2->PR = 59;
	
	//Write the Correct Configuration for EMR (LOW output value of Trigger Pin when match occurs and Initial value is LOW)
	TIMER2->EMR &= ~(1<<3| 1<<11);
	TIMER2->EMR |= (1<<10);
	
	NVIC_EnableIRQ(TIMER2_IRQn);
	
	NVIC_SetPriority(TIMER2_IRQn,5);
	
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
}

void Ultrasonic_Capture_Timer_Init() {
	//Turn on Timer3
	PCONP |= (1<<23);
	
	//Change the mode of Timer3 to Timer Mode
	TIMER3->CTCR &= ~3;
	
	TIMER3->TCR &= ~(1 << 0);
	
	TIMER3->TCR |= (1 << 1);
	
	//Change PR Register value for 1 microsecond incrementing
	TIMER3->PR = 59;
	
	//Change CCR value for getting Interrupt when Rising Edge Occur for CAP 1
	TIMER3->CCR |= (1<<3|1<<5);
	
	TIMER3->TCR &= ~(1 << 1);
	
	TIMER3->TCR |= (1 << 0);

	NVIC_EnableIRQ(TIMER3_IRQn);
}

void Ultrasonic_Start_Trigger_Timer() {
	//Change output value of Trigger Pin as HIGH
	TIMER2->EMR |= 8;
	
	//Give correct value to corresponding MR Register for 10 microsecond
	TIMER2->MR3 = TIMER2->TC + 10; 
	
	//Enable interrupt for MR3 register, if MR3 register matches the TC.
	TIMER2->MCR |= (1<<9);
	
	//Remove the reset on counters of Timer2.
	TIMER2->TCR &= ~2;
	
	//Enable Timer Counter and Prescale Counter for counting.
	TIMER2->TCR |=  1;
}

void TIMER2_IRQHandler() {
	//Write HIGH bit value to IR Register for Corresponding Interrupt
	TIMER2->IR |= (1<<3);
	
	if(ultrasonicSensorTriggerStart == 0) {
		//Change MR3 Register Value for Suggested Waiting
		TIMER2->MR3 = 60000 + TIMER2->TC;
		
		ultrasonicSensorTriggerStart = 1;
	}
	else {
		TIMER2->EMR |= (1 << 3);
		TIMER2->MR3 = 10 + TIMER2->TC;
		
		ultrasonicSensorTriggerStart = 0;
	}
}

void TIMER3_IRQHandler() {
	TIMER3->IR = 1 << 5;
	
	if(ultrasonicSensorCaptureRisingEdge == 1) {
		ultrasonicSensorRisingCaptureTime = TIMER3->CR1;
		
		LPC_TIM3->CCR = (1 << 4) | (1 << 5);
		ultrasonicSensorCaptureRisingEdge = 0;
	}
	else {
		ultrasonicAvailable = 1;
		ultrasonicSensorDistance = (170 * (TIMER3->CR1 - ultrasonicSensorRisingCaptureTime)) ;
		
		
		
		if(race_start){
			
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
					
		LPC_TIM3->CCR = (1 << 3) | (1 << 5);
		ultrasonicSensorCaptureRisingEdge = 1;
	}
}

