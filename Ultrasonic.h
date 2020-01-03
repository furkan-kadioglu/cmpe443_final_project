#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Timer.h"
#include <math.h>

// Autonomus variables
// F1 hard
//#define REACTION(x) (-1166.666667 +203.164141 * pow(x, 1) -11.754079 * pow(x, 2) +0.226301 * pow(x, 3) )

// F2 hard
//#define REACTION(x) (2769.696970 -650.293318 * pow(x, 1) +57.019231 * pow(x, 2) -2.212510 * pow(x, 3) +0.032051 * pow(x, 4) )

// F3 hard
//#define REACTION(x) (-1456.969697 +252.382479 * pow(x, 1) -14.475524 * pow(x, 2) +0.274864 * pow(x, 3) )

// F4 hard
//#define REACTION(x) (-732.636364 +136.716200 * pow(x, 1) -8.433566 * pow(x, 2) +0.171911 * pow(x, 3) )

// F5 hard
//#define REACTION(x) (-408.545455 +85.375291 * pow(x, 1) -5.775058 * pow(x, 2) +0.127040 * pow(x, 3) )

// F6
//#define REACTION(x) (397.272727 -48.275058 * pow(x, 1) +1.456876 * pow(x, 2) )

// F7
//#define REACTION(x) (-6680.303030 +1443.035354 * pow(x, 1) -114.976107 * pow(x, 2) +3.991453 * pow(x, 3) -0.050699 * pow(x, 4) )

// F8 hard
#define REACTION(x) (221.818182 -30.389277 * pow(x, 1) +1.025641 * pow(x, 2) )

//F9
//#define REACTION(x) (-7516.000000 +1645.078671 * pow(x, 1) -133.082459 * pow(x, 2) +4.701049 * pow(x, 3) -0.060897 * pow(x, 4) )

// F10
//#define REACTION(x) (112.363636 -18.119814 * pow(x, 1) +0.701632 * pow(x, 2) )

// F11
//#define REACTION(x) (-173847.074088 +55875.595836 * pow(x, 1) -7440.255326 * pow(x, 2) +525.236313 * pow(x, 3) -20.725644 * pow(x, 4) +0.433270 * pow(x, 5) -0.003747 * pow(x, 6) )

// F12
//#define REACTION(x) (-3354.254731 +758.466494 * pow(x, 1) -62.914941 * pow(x, 2) +2.275595 * pow(x, 3) -0.030062 * pow(x, 4) )

// F13
//#define REACTION(x) (-1.521515 +1.250860 * pow(x, 1) -0.108126 * pow(x, 2) -0.009067 * pow(x, 3) +0.000728 * pow(x, 4) )

// F14
//#define REACTION(x) (2.464277 -5.304008 * pow(x, 1) +1.870985 * pow(x, 2) -0.225949 * pow(x, 3) +0.010574 * pow(x, 4) -0.000158 * pow(x, 5) )

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
