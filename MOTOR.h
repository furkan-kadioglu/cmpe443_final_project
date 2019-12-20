#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "PWM.h"
#include "GPIO.h"
#include "Signal.h"

#define IOCON_RIGHT_MOTORS_ADDRESS	0x4002C0AC
#define IOCON_RIGHT_MOTORS	*((volatile uint32_t*)(IOCON_RIGHT_MOTORS_ADDRESS))
	
#define IOCON_LEFT_MOTORS_ADDRESS	0x4002C09C
#define IOCON_LEFT_MOTORS	*((volatile uint32_t*)(IOCON_LEFT_MOTORS_ADDRESS))
	

#define MOTOR_DRIVER_IN1_PORT PORT1
#define MOTOR_DRIVER_IN2_PORT PORT1
#define MOTOR_DRIVER_IN3_PORT PORT1
#define MOTOR_DRIVER_IN4_PORT PORT0

#define MOTOR_DRIVER_IN1_MASK (1 << 24)
#define MOTOR_DRIVER_IN2_MASK (1 << 23)
#define MOTOR_DRIVER_IN3_MASK (1 << 20)
#define MOTOR_DRIVER_IN4_MASK (1 << 21)

#define MAX_MOTOR_DUTY_CYCLE 90
static uint32_t MOTOR_POWER_IN_PERCENT = 50;

#define NUMBER_OF_CYCLE_PER_DEGREE 140
static uint32_t DEGREE_OF_TURN = 1;
static uint32_t NUMBER_OF_TURN = 0;	

#define AUTO_DUTY_CYCLE 50

void MOTOR_Init(void);
void SET_MOTOR_POWER(uint32_t left, uint32_t right);
