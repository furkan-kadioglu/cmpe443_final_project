#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "GPIO.h"

#define RIGHT_SIGNAL_PORT 	PORT1
#define LEFT_SIGNAL_PORT 		PORT0
#define FORWARD_SIGNAL_PORT PORT1
#define BACK_SIGNAL_PORT 		PORT2

#define RIGHT_SIGNAL_MASK 	((uint32_t)1 << 31)
#define LEFT_SIGNAL_MASK 		(1 << 13)
#define FORWARD_SIGNAL_MASK (1 << 13)
#define BACK_SIGNAL_MASK		(1 << 19)

void Signal_Init(void);
void Start_Signal(GPIO_TypeDef* PORT, uint32_t MASK);
void Finish_Signal(void);
