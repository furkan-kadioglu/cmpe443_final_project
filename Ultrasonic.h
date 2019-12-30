#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Timer.h"
#include <math.h>

// Autonomus variables
#define REACTION(x) (x*x)


extern uint32_t previousDistance;
extern uint32_t ultrasonicSensorDistance2; // continous 2-sensor
extern uint32_t previousDistance2;


//Write IOCON Register Address of Trigger Pin.
#define IOCON_TRIGGER_ADDRESS	0x4002C024
#define IOCON_TRIGGER	*((volatile uint32_t*)(IOCON_TRIGGER_ADDRESS))

//Write IOCON Register Address of Echo Pin.
#define IOCON_ECHO_ADDRESS	0x4002C060
#define IOCON_ECHO	*((volatile uint32_t*)(IOCON_ECHO_ADDRESS))
	
//Write IOCON Register Address of Echo Pin.
#define IOCON_ECHO_ADDRESS2	0x4002C010
#define IOCON_ECHO2	*((volatile uint32_t*)(IOCON_ECHO_ADDRESS2))

#define SPECIFIED_DISTANCE 250000
extern uint8_t race_start;

extern uint32_t ultrasonicSensorRisingCaptureTime;
extern uint32_t ultrasonicSensorFallingCaptureTime;
extern uint32_t ultrasonicSensorDistance;

extern uint8_t ultrasonicSensorTriggerStart;
extern uint8_t ultrasonicSensorCaptureRisingEdge;
extern uint8_t  ultrasonicAvailable;

void Ultrasonic_Init(void);
void Ultrasonic_Trigger_Timer_Init(void);
void Ultrasonic_Capture_Timer_Init(void);

void Ultrasonic_Start_Trigger_Timer(void);

#endif
