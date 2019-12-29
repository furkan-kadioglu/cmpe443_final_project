#ifndef EXTERNAL_H
#define EXTERNAL_H

#include "LPC407x_8x_177x_8x.h"

typedef struct
{
	volatile	uint32_t EXTINT;
						uint32_t RESERVED0[1];
	volatile	uint32_t EXTMODE;
	volatile	uint32_t EXTPOLAR;
} EXT_TypeDef;

//0x00000000 is a dummy value, write the correct address
#define IOCON_PUSH_BUTTON_ADDRESS	0x4002C128
#define IOCON_PUSH_BUTTON	*((volatile uint32_t*)(IOCON_PUSH_BUTTON_ADDRESS))

//0x00000000 is a dummy value, write the correct address
#define EXT_ADDRESS	0x400FC140
#define EXT	((EXT_TypeDef*) EXT_ADDRESS)

#define ENCODER_PIN 6
#define NECESSARY_NUMBER_OF_TURN 2
static uint32_t NUMBER_OF_MOTOR_TURN = 0;


void External_Init(void);

#endif
