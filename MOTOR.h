#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "PWM.h"

#define IOCON_RIGHT_MOTORS_ADDRESS	0x4002C0AC
#define IOCON_RIGHT_MOTORS	*((volatile uint32_t*)(IOCON_RIGHT_MOTORS_ADDRESS))
	
#define IOCON_LEFT_MOTORS_ADDRESS	0x4002C09C
#define IOCON_LEFT_MOTORS	*((volatile uint32_t*)(IOCON_LEFT_MOTORS_ADDRESS))
	
void MOTOR_Init(void);
void SET_MOTOR_POWER(uint32_t left, uint32_t right);
