#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "GPIO.h"

#define IOCON_RIGHT_SIGNAL_ADDRESS 0x4002C098
#define IOCON_LEFT_SIGNAL_ADDRESS 0x4002C094
#define IOCON_FORWARD_SIGNAL_ADDRESS 0x4002C08C
#define IOCON_BACK_SIGNAL_ADDRESS 0x4002C088
#define IOCON_RIGHT_SIGNAL *((volatile uint32_t *) IOCON_RIGHT_SIGNAL_ADDRESS)
#define IOCON_LEFT_SIGNAL *((volatile uint32_t *) IOCON_LEFT_SIGNAL_ADDRESS)
#define IOCON_FORWARD_SIGNAL *((volatile uint32_t *) IOCON_FORWARD_SIGNAL_ADDRESS)
#define IOCON_BACK_SIGNAL *((volatile uint32_t *) IOCON_BACK_SIGNAL_ADDRESS)

#define RIGHT_SIGNAL_PORT 	PORT1
#define LEFT_SIGNAL_PORT 		PORT1
#define FORWARD_SIGNAL_PORT PORT1
#define BACK_SIGNAL_PORT 		PORT1

#define RIGHT_SIGNAL_MASK 	((uint32_t)1 << 6)
#define LEFT_SIGNAL_MASK 		(1 << 5)
#define FORWARD_SIGNAL_MASK (1 << 3)
#define BACK_SIGNAL_MASK		(1 << 2)

void Signal_Init(void);
void Start_Signal(GPIO_TypeDef* PORT, uint32_t MASK);
void Finish_Signal(void);
