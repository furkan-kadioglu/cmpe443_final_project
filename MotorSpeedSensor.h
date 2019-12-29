#include "LPC407x_8x_177x_8x.h"


#define IOCON_CAPTURE_ADDRESS	0x4002C0B0
#define IOCON_CAPTURE	*((volatile uint32_t*)(IOCON_CAPTURE_ADDRESS))


#define NECESSARY_NUMBER_OF_TURN 6

void Motor_Speed_Sensor_Init(void);
